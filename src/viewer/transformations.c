#include "transformations.h"

/// @brief Масштабирует объект
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
/// @param arr_size кол-во координат
/// @param number коэф-нт масштабирования
void zoom_object(double *vertices_coordinates, int arr_size, double number) {
  for (int i = 0; i < arr_size; i++) {
    vertices_coordinates[i] *= number;
  }
}

/// @brief Меняет положение объекта
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
/// @param arr_size кол-во координат
/// @param number величина сдвига
/// @param axis_type ось сдвига
/// @param center изменение положения центра относительно 0
void move_object(double *vertices_coordinates, int arr_size, double number,
                 int axis_type, double *center) {
  center[axis_type] += number;
  for (int i = axis_type; i < arr_size; i += 3) {
    vertices_coordinates[i] = vertices_coordinates[i] + number;
  }
}

/// @brief Вращает объект относительно точки нуля перспективы
/// @param vertices_coordinates указатель на массив координат по три на вершину
/// (x, y, z, x, ...)
/// @param arr_size кол-во координат
/// @param angle угол поворота
/// @param axis ось поворота
/// @param center изменение положения центра относительно 0 перспективы
void rotate_object(double *vertices_coordinates, int arr_size, double angle,
                   int axis, double *center) {
  angle = angle / 180 * PI;
  if (axis == X_AXIS) {
    for (int i = 0; i < arr_size; i += 3) {
      double tmp_y = vertices_coordinates[i + Y_AXIS] - center[Y_AXIS];
      double tmp_z = vertices_coordinates[i + Z_AXIS] - center[Z_AXIS];
      vertices_coordinates[i + Y_AXIS] =
          cos(angle) * tmp_y - sin(angle) * tmp_z + center[Y_AXIS];
      vertices_coordinates[i + Z_AXIS] =
          sin(angle) * tmp_y + cos(angle) * tmp_z + center[Z_AXIS];
    }
  } else if (axis == Y_AXIS) {
    for (int i = 0; i < arr_size; i += 3) {
      double tmp_x = vertices_coordinates[i + X_AXIS] - center[X_AXIS];
      double tmp_z = vertices_coordinates[i + Z_AXIS] - center[Z_AXIS];
      vertices_coordinates[i + X_AXIS] =
          cos(angle) * tmp_x + sin(angle) * tmp_z + center[X_AXIS];
      vertices_coordinates[i + Z_AXIS] =
          -sin(angle) * tmp_x + cos(angle) * tmp_z + center[Z_AXIS];
    }
  } else if (axis == Z_AXIS) {
    for (int i = 0; i < arr_size; i += 3) {
      double tmp_x = vertices_coordinates[i + X_AXIS] - center[X_AXIS];
      double tmp_y = vertices_coordinates[i + Y_AXIS] - center[Y_AXIS];
      vertices_coordinates[i + X_AXIS] =
          cos(angle) * tmp_x - sin(angle) * tmp_y + center[X_AXIS];
      vertices_coordinates[i + Y_AXIS] =
          sin(angle) * tmp_x + cos(angle) * tmp_y + center[Y_AXIS];
    }
  }
}
