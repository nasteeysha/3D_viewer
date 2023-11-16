#ifdef __cplusplus
extern "C" {
#endif
#ifndef VIEWER_TRANSFORMATIONS_H_
#define VIEWER_TRANSFORMATIONS_H_

#include <math.h>

#include "stack.h"

#define PI 3.141
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

void zoom_object(double *vertices_coordinates, int arr_size, double number);
void move_object(double *vertices_coordinates, int arr_size, double number,
                 int axis_type, double *center);
void rotate_object(double *vertices_coordinates, int arr_size, double angle,
                   int axis, double *center);

#endif  // VIEWER_TRANSFORMATIONS_H_
#ifdef __cplusplus
}
#endif
