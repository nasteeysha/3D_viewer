#include "s21_objloader.h"

/// @brief Формирует данные для 3D модели по .obj файлу
/// @param filename название .obj файла с путем
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
/// @param arr_size указатель на счетчик координат
/// @param index_stack указатель на стэк полигонов
/// @param poligon_counter указатель на счетчик полигонов
/// @param edges указатель на счетчик ребер
/// @return 1, если формат файла не подходит и 0 в ином случае
int load_array(char *filename, double **vertices_coordinates, int *arr_size,
               node **index_stack, int *poligon_counter) {
  int res = 0;
  double minmax[6] = {0, 0, 0, 0, 0, 0};
  free_model_data(vertices_coordinates, arr_size, index_stack, poligon_counter);
  if (filename[0] != '\0') {
    res = parser(filename, vertices_coordinates, arr_size, index_stack,
                 poligon_counter);
  } else {
    res = 1;
  }
  if (res == 0 && *poligon_counter > 0 &&
      check_polygon_vertex(*index_stack, *arr_size) == 0) {
    find_minmax(minmax, *vertices_coordinates, *arr_size);
    centralize_object(minmax, *vertices_coordinates, *arr_size);
    normalize_object(minmax, *vertices_coordinates, *arr_size);
  } else {
    free_model_data(vertices_coordinates, arr_size, index_stack,
                    poligon_counter);
    res = 1;
  }
  return res;
}

/// @brief Очищает все входные данные и зануляет их
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
/// @param arr_size указатель на счетчик координат
/// @param index_stack указатель на стэк полигонов
/// @param poligon_counter указатель на счетчик полигонов
/// @param edges указатель на счетчик ребер
void free_model_data(double **vertices_coordinates, int *arr_size,
                     node **index_stack, int *poligon_counter) {
  free((*vertices_coordinates));
  (*vertices_coordinates) = NULL;
  destroy(*index_stack);
  *index_stack = NULL;
  *arr_size = 0;
  *poligon_counter = 0;
}
