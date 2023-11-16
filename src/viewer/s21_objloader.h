#ifdef __cplusplus
extern "C" {
#endif
#ifndef VIEWER_S21_OBJLOADER_H_
#define VIEWER_S21_OBJLOADER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define MIN_X 0
#define MAX_X 1
#define MIN_Y 2
#define MAX_Y 3
#define MIN_Z 4
#define MAX_Z 5
#define X_POINT 0
#define Y_POINT 1
#define Z_POINT 2

int load_array(char *filename, double **vertices_coordinates, int *arr_size,
               node **index_stack, int *poligon_counter);
void free_model_data(double **vertices_coordinates, int *arr_size,
                     node **index_stack, int *poligon_counter);
// s21_objloader.c

int parser(char *filename, double **vertices_coordinates, int *arr_size,
           node **index_stack, int *poligon_counter);
int take_line(char **str, FILE *file);
void handle_string(char *str, double **vertices_coordinates, int *arr_size,
                   node **index_stack, int *poligon_counter);
int take_number(char *str, int *letter_pos, int *number);
void handle_f(char *str, node **index_stack, int *poligon_counter);
void set_number(int *array, int size_array, int number);
void handle_v(char *str, double *vertices_coordinates, int arr_size);
int take_double_number(char *str, int *letter_pos, double *number);
// parser.c

int check_polygon_vertex(node *index_stack, int arr_size);
void init_minmax(double *minmax, double *vertices_coordinates);
void find_minmax(double *minmax, double *vertices_coordinates, int arr_size);
void centralize_object(double *minmax, double *vertices_coordinates,
                       int arr_size);
void normalize_object(double *minmax, double *vertices_coordinates,
                      int arr_size);
// secondary.c

#endif  // VIEWER_S21_OBJLOADER_H_
#ifdef __cplusplus
}
#endif
