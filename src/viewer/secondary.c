#include "s21_objloader.h"

/// @brief Проверяет стэк полигонов на формирование из несуществующих вершин
/// @param index_stack указатель на стэк полигонов
/// @param arr_size кол-во координат
/// @return 1, если найден некорректный полигон, и 0 в ином случае
int check_polygon_vertex(node *index_stack, int arr_size) {
  node *tmp = index_stack;
  int res = 0;
  while (tmp != NULL && res == 0) {
    for (int i = 0; i < tmp->size_of_array && res == 0; i++) {
      if (tmp->index_array[i] >= arr_size / 3) res = 1;
    }
    tmp = tmp->next_node;
  }
  return res;
}

/// @brief Находит минимальные и максимальные значения координат
/// @param minmax указатель на массив минимальным и максимальных занчений
/// координат
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
/// @param arr_size кол-во координат
void find_minmax(double *minmax, double *vertices_coordinates, int arr_size) {
  init_minmax(minmax, vertices_coordinates);
  for (int j = 0; j < 3; j++) {
    for (int i = j; i < arr_size; i += 3) {
      if (vertices_coordinates[i] < minmax[j * 2])
        minmax[j * 2] = vertices_coordinates[i];
      if (vertices_coordinates[i] > minmax[j * 2 + 1])
        minmax[j * 2 + 1] = vertices_coordinates[i];
    }
  }
}

/// @brief устанавливает занчения минимальных и максимальных координат, равными
/// первым трем
/// @param minmax указатель на массив минимальным и максимальных занчений
/// координат
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
void init_minmax(double *minmax, double *vertices_coordinates) {
  minmax[MIN_X] = vertices_coordinates[X_POINT];
  minmax[MAX_X] = vertices_coordinates[X_POINT];
  minmax[MIN_Y] = vertices_coordinates[Y_POINT];
  minmax[MAX_Y] = vertices_coordinates[Y_POINT];
  minmax[MIN_Z] = vertices_coordinates[Z_POINT];
  minmax[MAX_Z] = vertices_coordinates[Z_POINT];
}

/// @brief выравнивает центр объекта к нулю
/// @param minmax указатель на массив минимальным и максимальных занчений
/// координат
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
/// @param arr_size кол-во координат
void centralize_object(double *minmax, double *vertices_coordinates,
                       int arr_size) {
  double centerX = minmax[MIN_X] + (minmax[MAX_X] - minmax[MIN_X]) / 2;
  double centerY = minmax[MIN_Y] + (minmax[MAX_Y] - minmax[MIN_Y]) / 2;
  double centerZ = minmax[MIN_Z] + (minmax[MAX_Z] - minmax[MIN_Z]) / 2;
  for (int i = 0; i < arr_size; i += 3) {
    vertices_coordinates[i] -= centerX;  // X
    vertices_coordinates[i + Y_POINT] -= centerY;
    vertices_coordinates[i + Z_POINT] -= centerZ;
  }
}

/// @brief Приводит координаты в диапазон от -1 до 1
/// @param minmax указатель на массив минимальным и максимальных занчений
/// координат
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
/// @param arr_size кол-во координат
void normalize_object(double *minmax, double *vertices_coordinates,
                      int arr_size) {
  double getX = minmax[MAX_X] - minmax[MIN_X];
  double getY = minmax[MAX_Y] - minmax[MIN_Y];
  double getZ = minmax[MAX_Z] - minmax[MIN_Z];
  double dmax = (fmax(fmax(getX, getY), getZ)) / 2;
  for (int i = 0; i < arr_size; i++) {
    vertices_coordinates[i] /= dmax;
  }
}
