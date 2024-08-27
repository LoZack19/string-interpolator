#include <include/interpolation.h>
#include <stdio.h>

int main() {
    struct point_set* points = linit_point_set(0, 3, 1, 1, 2, 4, 3, 9);
    if (points) {
        double result = lagrange_interpolation(points, 2.5);
        printf("Interpolated value at x=2.5: %f\n", result);
        free_point_set(&points);
    }
    return 0;
}