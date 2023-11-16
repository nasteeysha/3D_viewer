#include "../viewer/transformations.h"
#include "s21_check.h"

START_TEST(zoom_check) {
  double vertex_array[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                           1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};
  int vertices_coordinates_true = 24;
  double vertex_array_true[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                                1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};

  zoom_object(vertex_array, vertices_coordinates_true, 0.5);
  for (int i = 0; i < 24; i++)
    ck_assert_double_eq_tol(vertex_array[i], vertex_array_true[i] * 0.5, 0.01);
}
END_TEST

START_TEST(move_x) {
  double center[3] = {0, 0, 0};
  double vertex_array[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                           1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};
  int vertices_coordinates_true = 24;
  double vertex_array_true[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                                1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};

  move_object(vertex_array, vertices_coordinates_true, -0.5, X_AXIS, center);
  for (int i = X_AXIS; i < 24; i += 3)
    ck_assert_double_eq_tol(vertex_array[i], vertex_array_true[i] - 0.5, 0.01);
  double center_true[3] = {-0.5, 0, 0};
  for (int i = 0; i < 3; i++)
    ck_assert_double_eq_tol(center[i], center_true[i], 0.01);
}
END_TEST

START_TEST(move_y) {
  double center[3] = {0, 0, 0};
  double vertex_array[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                           1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};
  int vertices_coordinates_true = 24;
  double vertex_array_true[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                                1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};

  move_object(vertex_array, vertices_coordinates_true, 0.9, Y_AXIS, center);
  for (int i = Y_AXIS; i < 24; i += 3)
    ck_assert_double_eq_tol(vertex_array[i], vertex_array_true[i] + 0.9, 0.01);
  double center_true[3] = {0, 0.9, 0};
  for (int i = 0; i < 3; i++)
    ck_assert_double_eq_tol(center[i], center_true[i], 0.01);
}
END_TEST

START_TEST(move_z) {
  double center[3] = {0, 0, 0};
  double vertex_array[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                           1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};
  int vertices_coordinates_true = 24;
  double vertex_array_true[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                                1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};

  move_object(vertex_array, vertices_coordinates_true, 0.2, Z_AXIS, center);
  for (int i = Z_AXIS; i < 24; i += 3)
    ck_assert_double_eq_tol(vertex_array[i], vertex_array_true[i] + 0.2, 0.01);
  double center_true[3] = {0, 0, 0.2};
  for (int i = 0; i < 3; i++)
    ck_assert_double_eq_tol(center[i], center_true[i], 0.01);
}
END_TEST

START_TEST(rotate_x) {
  double center[3] = {0, 0, 0};
  double vertex_array[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                           1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};
  int vertices_coordinates_true = 24;
  double vertex_array_true[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                                1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};

  rotate_object(vertex_array, vertices_coordinates_true, 0, X_AXIS, center);
  for (int i = 0; i < 24; i++)
    ck_assert_double_eq_tol(vertex_array[i], vertex_array_true[i], 0.01);
}
END_TEST

START_TEST(rotate_y) {
  double center[3] = {0, 0, 0};
  double vertex_array[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                           1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};
  int vertices_coordinates_true = 24;
  double vertex_array_true[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                                1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};

  rotate_object(vertex_array, vertices_coordinates_true, 360, Y_AXIS, center);
  for (int i = 0; i < 24; i++)
    ck_assert_double_eq_tol(vertex_array[i], vertex_array_true[i], 0.01);
}
END_TEST

START_TEST(rotate_z) {
  double center[3] = {0, 0, 0};
  double vertex_array[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                           1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};
  int vertices_coordinates_true = 24;
  double vertex_array_true[] = {1,  1, -1, 1,  1, 1, 1,  -1, -1, 1,  -1, 1,
                                -1, 1, -1, -1, 1, 1, -1, -1, -1, -1, -1, 1};

  rotate_object(vertex_array, vertices_coordinates_true, 180, Z_AXIS, center);
  for (int i = 0; i < 24; i++)
    ck_assert_double_eq_tol(vertex_array[i], vertex_array_true[i], 0.01);
}
END_TEST

Suite* s21_transformations_suite() {
  Suite* suite = suite_create("transformations");
  TCase* tcase_core = tcase_create("transformations");

  tcase_add_test(tcase_core, zoom_check);
  tcase_add_test(tcase_core, move_x);
  tcase_add_test(tcase_core, move_y);
  tcase_add_test(tcase_core, move_z);
  tcase_add_test(tcase_core, rotate_x);
  tcase_add_test(tcase_core, rotate_y);
  tcase_add_test(tcase_core, rotate_z);
  suite_add_tcase(suite, tcase_core);

  return suite;
}