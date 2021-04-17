#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include "interpolation.h"

#define SETTINGS_FILE   "./settings.txt"
#define DAT_FILE        "file.dat"
#define INTERVAL        4

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static char __get_ext__(char* string, int min)
{
    char _ext = 0;
    size_t length = strlen(string);

    if (min)
        _ext = CHAR_MAX;

    for (size_t i = 0; i < length; i++) {
        if (min)
            _ext = MIN(_ext, string[i]);
        else
            _ext = MAX(_ext, string[i]);
    }

    return _ext;
}

#define getmin(string)  __get_ext__((string), 1)
#define getmax(string)  __get_ext__((string), 0)

int main(int argc, char* argv[])
{
    FILE* settings;
    int fifo_fd, status = -1;
    size_t len;
    char min, max;
    struct point_set* points;

    if (argc < 2 && (!argv[1] || !(argv[1][0])))
        goto exit;

    len = strlen(argv[1]);
    min = getmin(argv[1]);
    max = getmax(argv[1]);

    settings = fopen(SETTINGS_FILE, "w");
    fprintf(settings, "set xrange [%d:%lu]\n"
                      "set yrange [%d:%d]\n"
                      "set size ratio 1\n"
                      "plot \"" DAT_FILE "\" with lines", 1, len, min - INTERVAL, max + INTERVAL);
    fclose(settings);

    if (!~mkfifo(DAT_FILE, 0644)) {
        perror("Failed to create fifo");
        goto exit_clean_settings;
    }

    points = sinit_point_set(argv[1]);
    if (!points) {
        goto exit_clean_fifo;
    }

    fifo_fd = open(DAT_FILE, O_WRONLY);
    if (!~fifo_fd) {
        perror("Failed to open fifo");
        goto exit_clean_fifo;
    }
    if (!~dup2(fifo_fd, STDOUT_FILENO)) {
        perror("Failed to redirect stdout");
        close(fifo_fd);
        goto exit_clean_fifo;
    }
    close(fifo_fd);
    
    for (double i = 0; i < len; i += 0.01) {
        printf("%f\t%f\n", i, lagrange_interpolation(points, i));
    }
    status = 0;

exit_clean_fifo:
    remove(DAT_FILE);
    free_point_set(&points);
exit_clean_settings:
    remove(SETTINGS_FILE);
exit:
    return status;
}