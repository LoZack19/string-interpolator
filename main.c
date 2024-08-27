#include <include/interpolation.h>
#include <stdio.h>

int main() {
    struct points* points = points_linit(true, 8, 0, 3, 1, 1, 2, 4, 3, 9);

    // for (size_t i = 0; i < points->length; i++) {
    //     fprintf(stdout, "%ld: ", i);
    //     point_display(points->list[i], stdout);
    //     fputs("\n", stdout);
    // }

    fprintf(stdout, "x, y\n");
    for (double x = 0.0; x < 8.0; x += 0.01) {
        double y = lagrange_interpolation(points, x);
        fprintf(stdout, "%.4f, %.4f\n", x, y);
    }

    points_free(points);
}