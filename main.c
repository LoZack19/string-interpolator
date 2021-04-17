#include <stdio.h>
#include "interpolation.h"

int main()
{
    struct point_set* points;

    points = sinit_point_set("Hello World!");
    if (!points)
        return 0;

    for (double i = 0; i < 10; i += 0.01) {
        printf("%f\t%f\n", i, lagrange_interpolation(points, i));
    }

    free_point_set(&points);
    return 0;
}