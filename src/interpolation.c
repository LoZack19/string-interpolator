#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <include/interpolation.h>

struct point* point_create(int x, int y)
{
    struct point* p = malloc(sizeof(*p));
    if (p == NULL) {
        return NULL;
    }
    
    p->x = x;
    p->y = y;
    return p;
}

void point_free(struct point* p)
{
    free(p);
}

void point_display(struct point *p, FILE *outfile)
{
    fprintf(outfile, "{%d, %d}", p->x, p->y);
}

struct points *points_create(size_t initial_capacity)
{
    struct points *ps;

    ps = malloc(sizeof(*ps));
    if (ps == NULL) {
        return NULL;
    }

    ps->list = malloc(initial_capacity * sizeof(*ps->list));
    if (ps->list == NULL) {
        free(ps);
        return NULL;
    }

    ps->capacity = initial_capacity;
    ps->length = 0;

    return ps;
}

void points_free(struct points* ps)
{
    for (size_t i = 0; i < ps->length; i++) {
        free(ps->list[i]);
    }
    free(ps->list);
    free(ps);
}

int points_is_full(struct points *ps)
{
    return ps->length >= ps->capacity;
}

int points_is_empty(struct points *ps)
{
    return ps->length <= 0;
}

int points_logresize(struct points *ps)
{ 
    const size_t FACTOR = 2;

    struct point **new_list = realloc(ps, ps->capacity * FACTOR * sizeof(*new_list));
    if (new_list == NULL) {
        return EXIT_FAILURE;
    }

    ps->list = new_list;
    ps->capacity *= FACTOR;
    return EXIT_SUCCESS;
}

int points_push(struct points *ps, struct point *p)
{
    int err;
    
    if (points_is_full(ps)) {
        err = points_logresize(ps);
        if (err != EXIT_SUCCESS) {
            return err;
        }
    }

    ps->list[ps->length] = OWN(p);
    ps->length += 1;

    return EXIT_SUCCESS;
}

struct point *points_pop(struct points *ps)
{
    if (points_is_empty(ps)) {
        return NULL;
    }

    ps->length -= 1;
    return DISOWN(ps->list[ps->length]);
}

/* initialize set of points
 *  @1 > if true x = [0, 1, ...] else x has to be specified in the va_list
 *  @2 > number of points
 *  @3 > list of points (va_list) [use init_points to specify the list]
 *  @  < return set of points
 */
struct points* points_vinit(const bool reg, const size_t points_num, va_list list)
{
    int err;

    struct points *ps = points_create(points_num);
    if (ps == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < points_num; i++) {
        struct point *p = point_create((reg) ? i : va_arg(list, int), va_arg(list, int));
        if (p == NULL) {
            points_free(ps);
            return NULL;
        }

        err = points_push(ps, p);
        if (err != EXIT_SUCCESS) {
            point_free(p);
            points_free(ps);
            return NULL;
        }
    }

    return ps;
}

/* initialize set of points
 *  @1 > regular intervals on x axis
 *  @2 > number of points
 *  @3 > list (x, y, x, y ... if not reg) (y, y, y ... if reg)
 *  @  < return set of points
 */
struct points* points_linit(const bool reg, const size_t points_num, ...)
{
    va_list list;

    va_start(list, points_num);
    return points_vinit(reg, points_num, list);
    va_end(list);
}

struct points* points_init(const bool reg, const size_t points_num, const int list[])
{
    int err;

    struct points *ps = points_create(points_num);
    if (ps == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < points_num; i++) {
        struct point *p = point_create((reg) ? (int)i : list[i], list[i+1]);
        if (p == NULL) {
            points_free(ps);
            return NULL;
        }

        err = points_push(ps, p);
        if (err != EXIT_SUCCESS) {
            point_free(p);
            points_free(ps);
            return NULL;
        }
    }

    return ps;
}

struct points* points_sinit(char* string)
{
    int err;

    struct points *ps = points_create(1);
    if (ps == NULL) {
        return NULL;
    }

    for (size_t i = 0; string[i] != '\0'; i++) {
        struct point *p = point_create(i, string[i]);
        if (p == NULL) {
            points_free(ps);
            return NULL;
        }

        err = points_push(ps, p);
        if (err != EXIT_SUCCESS) {
            point_free(p);
            points_free(ps);
            return NULL;
        }
    }

    return ps;
}

/* ----------------------------- */

/* Calculate the basis polinomial of the lagrange interpolation
 * @1 > array of points
 * @2 > current point
 * @3 > evaluated in x
 * @  < result of the basis polinomial
 */
double lagrange_basis(struct points* points, size_t j, double x)
{
    double res = 1;

    if (points == NULL || points->list == NULL || j > points->length)
        return 0.0;

    for (size_t i = 0; i < points->length; ++i) {
        if (i == j)
            continue;
        
        double temp = points->list[j]->x - points->list[i]->x;
        if (temp)
            temp = (x - points->list[i]->x) / temp;
        else
            return 0;
        res *= temp;
    }

    return res;
}

/* Calculate the result of the lagrange interpolation for x
 * @1 > array of points
 * @2 > evaluated in x
 * @  < result of the interpolation polinomial in x
 */
double lagrange_interpolation(struct points* points, double x)
{
    double res = 1;

    if (points == NULL || points->list == NULL)
        return 0.0;

    for (size_t i = 0; i < points->length; ++i) {
        double temp = lagrange_basis(points, i, x);
        if (temp)
            temp = points->list[i]->y * temp;
        else
            return 0.0;
        res += temp;
    }

    return res - 1;
}