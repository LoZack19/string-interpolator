# Interpolation Library

This C library provides functionality for point-based interpolation, specifically implementing Lagrange interpolation.

## Features

- Point and point set management
- Lagrange interpolation calculation

## Structures

### Point
Represents a single point with x and y coordinates.

### Point Set
A collection of points used for interpolation.

## Functions

### Point Management
- `init_point`: Initialize a new point
- `free_point`: Free memory allocated for a point

### Point Set Management
- `vinit_point_set`: Initialize a set of points using va_list
- `linit_point_set`: Initialize a set of points with a variable number of arguments
- `init_point_set`: Initialize a set of points from an array of numbers
- `sinit_point_set`: Initialize a set of points from a string
- `free_point_set`: Free memory allocated for a point set

### Interpolation
- `lagrange_basis`: Calculate the basis polynomial of the Lagrange interpolation
- `lagrange_interpolation`: Calculate the result of the Lagrange interpolation for a given x

## Usage

1. Include the header file in your C program:
   ```c
   #include "interpolation.h"
   ```

2. Create points or point sets using the provided initialization functions.

3. Use the Lagrange interpolation functions to perform calculations.

4. Free allocated memory using the provided free functions when done.

## Example

```c
#include "interpolation.h"
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
```

## Note

This library uses dynamic memory allocation. Always check the return values of initialization functions and free the allocated memory when it's no longer needed to prevent memory leaks.
