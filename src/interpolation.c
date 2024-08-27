#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <include/interpolation.h>

/* initialize `point` structure */
struct point* init_point(int x, int y)
{
    struct point* p = malloc(sizeof(struct point));
    if (!p)
        return NULL;
    
    p->x_coord = x;
    p->y_coord = y;
    return p;
}

/* free `point` structure */
void free_point(struct point** p)
{
    if (!p || !(*p))
        return;
    
    free(*p);
}

/* initialize set of points
 *  @1 > regular intervals on x axis
 *  @2 > number of points
 *  @3 > list of points (va_list) [use init_point_set to specify the list]
 *  @  < return set of points
 */
struct point_set* vinit_point_set(const int reg, size_t points_num, va_list list)
{
    struct point_set* points = malloc(sizeof(struct point_set));
    if (!points)
        return NULL;
    
    points->set = malloc((points_num + 1) * sizeof(struct point*));
    if (!points->set) {
        free(points);
        return NULL;
    }
    points->set[0] = calloc(1, sizeof(struct point));
    if (!points->set[0]) {
        free(points->set);
        free(points);
        return NULL;
    }
    points->size = 1;

    for (size_t i = 1; i <= points_num; ++i) {
        points->set[i] = init_point((reg) ? i : va_arg(list, int), va_arg(list, int));
        if (!points->set[i]) {
            points->size = i;
            free_point_set(&points);
            return NULL;
        }
    }

    points->size = points_num + 1;

    return points;
}

/* initialize set of points
 *  @1 > regular intervals on x axis
 *  @2 > number of points
 *  @3 > list (x, y, x, y ... if not reg) (y, y, y ... if reg)
 *  @  < return set of points
 */
struct point_set* linit_point_set(int reg, size_t points_num, ...)
{
    va_list list;

    va_start(list, points_num);
    return vinit_point_set(reg, points_num, list);
    va_end(list);
}

struct point_set* init_point_set(size_t length, int nums[])
{
    struct point_set* points;

    if(!nums)
        return NULL;
    
    points = malloc(sizeof(struct point_set));
    if (!points)
        return NULL;
    
    points->set = malloc((length + 1) * sizeof(struct point*));
    if (!points->set) {
        free(points);
        return NULL;
    }

    points->set[0] = init_point(0, 0);

    for (size_t i = 1; i <= length; ++i) {
        points->set[i] = init_point(i, nums[i-1]);
        if (!points->set[i]) {
            points->size = i;
            free_point_set(&points);
            return NULL;
        }
    }
    points->size = length + 1;
    
    return points;
}

struct point_set* sinit_point_set(char* string)
{
    int* array;
    size_t len;
    struct point_set* points;

    if(!string || !(*string))
        return NULL;
    
    len = strlen(string);
    array = malloc(len * sizeof(int));
    if (!array)
        return NULL;
    
    for (size_t i = 0; i < len; ++i) {
        array[i] = (int)string[i];
    }

    points = init_point_set(len, array);

    free(array);
    return points;
}

void free_point_set(struct point_set** points)
{
    if (!points || !(*points))
        return;
    
    for (size_t i = 0; i < (*points)->size; ++i) {
        free_point(&((*points)->set[i]));
    }
    free((*points)->set);
    free(*points);

    return;
}

/* ----------------------------- */

/* Calculate the basis polinomial of the lagrange interpolation
 * @1 > array of points
 * @2 > current point
 * @3 > evaluated in x
 * @  < result of the basis polinomial
 */
double lagrange_basis(struct point_set* points, size_t j, double x)
{
    double temp = 0, res = 1;

    if (!points || !points->set || j > points->size)
        return 0;

    for (size_t i = 0; i < points->size; ++i) {
        if (i == j)
            continue;
        
        temp = points->set[j]->x_coord - points->set[i]->x_coord;
        if (temp)
            temp = (x - points->set[i]->x_coord) / temp;
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
double lagrange_interpolation(struct point_set* points, double x)
{
    double res = 1;

    if (points == NULL || points->set == NULL)
        return 0;

    for (size_t i = 0; i < points->size; ++i) {
        double temp = lagrange_basis(points, i, x);
        if (temp)
            temp = points->set[i]->y_coord * temp;
        else
            return 0;
        res += temp;
    }

    return res - 1;
}