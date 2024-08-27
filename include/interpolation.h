#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#define OWN(X) (X)
#define BORROW(X) (X)
#define DISOWN(X) (X)
#define OWNED(X) (X)
#define BORROWED(X) (X)

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

struct point {
    int x;
    int y;
};

struct point* point_create(int x, int y);
void point_free(struct point* p);
void point_display(struct point *p, FILE *outfile);

struct points {
    struct point *OWNED(*list);
    size_t capacity;
    size_t length;
};

struct points *points_create(size_t initial_capacity);
void points_free(struct points* ps);

struct points* points_init(const bool reg, const size_t points_num, const int list[]);
struct points* points_linit(const bool reg, const size_t points_num, ...);
struct points* points_sinit(char* string);

/* Stack behavior */
int points_is_full(struct points *ps);
int points_is_empty(struct points *ps);
int points_logresize(struct points *ps);
int points_push(struct points *ps, struct point *p);
struct point *points_pop(struct points *ps);

double lagrange_basis(struct points* points, size_t j, double x);
double lagrange_interpolation(struct points* points, double x);

#endif