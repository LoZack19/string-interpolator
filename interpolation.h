#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <stddef.h>

struct point {
    int x_coord;
    int y_coord;
};

struct point_set {
    struct point**  set;
    size_t          size;
};

struct point* init_point(int x, int y);

void free_point(struct point** p);

struct point_set* init_point_set(int reg, size_t points_num, ...);

void free_point_set(struct point_set** points);


double lagrange_basis(struct point_set* points, size_t j, double x);

double lagrange_interpolation(struct point_set* points, double x);

#endif