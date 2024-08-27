#include <include/interpolation.h>
#include <stdio.h>

int main() {
    struct points* points = points_linit(true, 8, 0, 3, 1, 1, 2, 4, 3, 9);

    fprintf(stdout, "x, y\n");
    for (double x = 0.0; x <= 7.0; x += 0.01) {
        double y = lagrange_interpolation(points, x);
        fprintf(stdout, "%.4f, %.4f\n", x, y);
    }

    points_free(points);
}