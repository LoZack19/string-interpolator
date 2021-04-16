#include <stdio.h>
#include "interpolation.h"

int main()
{
    struct point_set* points;
    FILE* plot = fopen("file.dat", "w");
    if (!plot)
        return 0;

    points = init_point_set(1, 5,
                            3, 5, 2, 7, 9);
    if (!points)
        return 0;

    for (double i = 0; i < 10; i += 0.01) {
        fprintf(plot, "%f\t%f\n", i, lagrange_interpolation(points, i));
    }

    free_point_set(&points);
    fclose(plot);
    return 0;
}