# Lagrange Interpolation Library

This library provides basic functionality for creating, managing, and manipulating sets of 2D points, as well as performing Lagrange interpolation based on these points.

## Features

- **Point Management**:
  - Create and free individual points.
  - Create and manage dynamic arrays of points.
  - Push and pop points from the dynamic array with automatic resizing.
  
- **Lagrange Interpolation**:
  - Calculate the Lagrange basis polynomial.
  - Perform Lagrange interpolation for a given `x` value.

## Getting Started

### Prerequisites

- C Compiler (GCC, Clang, etc.)
- Standard C library (`stdlib.h`, `string.h`, `stdarg.h`, `stdio.h`)

### Compilation

Include the necessary headers and compile your C program with the provided source files.

```c
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "interpolation.h"
```

### Example Usage

#### Creating and Managing Points

```c
struct point* p = point_create(2, 3);
if (p != NULL) {
    point_display(p, stdout);  // Output: {2, 3}
    point_free(p);
}

struct points* ps = points_create(10);
if (ps != NULL) {
    points_push(ps, point_create(1, 2));
    points_push(ps, point_create(2, 4));
    struct point* last_point = points_pop(ps);
    point_display(last_point, stdout); // Output: {2, 4}
    point_free(last_point);
    points_free(ps);
}
```

#### Performing Lagrange Interpolation

```c
struct points* ps = points_create(3);
points_push(ps, point_create(0, 1));
points_push(ps, point_create(1, 3));
points_push(ps, point_create(2, 2));

double result = lagrange_interpolation(ps, 1.5);
printf("Lagrange interpolation at x = 1.5: %f\n", result);

points_free(ps);
```

### Functions

#### Point Management

- **`struct point* point_create(int x, int y);`**  
  Creates a new point with coordinates `(x, y)`.

- **`void point_free(struct point* p);`**  
  Frees the memory allocated for a point.

- **`void point_display(struct point *p, FILE *outfile);`**  
  Displays the coordinates of a point in the format `{x, y}`.

#### Points Array Management

- **`struct points* points_create(size_t initial_capacity);`**  
  Creates a dynamic array of points with an initial capacity.

- **`void points_free(struct points* ps);`**  
  Frees the memory allocated for the points array and all its points.

- **`int points_push(struct points *ps, struct point *p);`**  
  Adds a new point to the array, resizing if necessary.

- **`struct point* points_pop(struct points *ps);`**  
  Removes and returns the last point from the array.

#### Lagrange Interpolation

- **`double lagrange_basis(struct points* points, size_t j, double x);`**  
  Computes the Lagrange basis polynomial for a given `x`.

- **`double lagrange_interpolation(struct points* points, double x);`**  
  Performs Lagrange interpolation to compute the value at `x`.

### Error Handling

- Functions that return pointers (`struct point*`, `struct points*`) will return `NULL` on failure.
- Functions that return integers (`int`) will return `EXIT_SUCCESS` (0) on success and `EXIT_FAILURE` (1) on failure.


### Contributing

Contributions are welcome! Please fork the repository and create a pull request for any enhancements, bug fixes, or additional features.

### Contact

For any questions or issues, please open an issue on the GitHub repository or contact the maintainer.

---

This library aims to provide a simple and efficient way to perform Lagrange interpolation in C. Feel free to extend its functionality or adapt it to your specific needs.