#include "../viewer/s21_objloader.h"
#include "s21_check.h"

START_TEST(test_0) {
  double* vertex_array = NULL;
  int vertices_coordinates = 0;
  node* index_stack = NULL;
  int poligon_counter = 0;
  char filename[] = "obj/cube.obj";

  double vertex_array_true[] = {-1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1,
                                1,  -1, -1, 1,  -1, 1, 1,  1, -1, 1,  1, 1};
  int vertices_coordinates_true = 24;
  int poligon_counter_true = 11;
  int index_array[11][9] = {
      {8, 7, 3, 3, 1, 1, 5, 5, 7}, {6, 0, 5, 5, 1, 1, 0}, {6, 0, 4, 4, 5, 5, 0},
      {6, 4, 7, 7, 5, 5, 4},       {6, 4, 6, 6, 7, 7, 4}, {6, 2, 3, 3, 7, 7, 2},
      {6, 2, 7, 7, 6, 6, 2},       {6, 0, 1, 1, 3, 3, 0}, {6, 0, 3, 3, 2, 2, 0},
      {6, 0, 2, 2, 6, 6, 0},       {6, 0, 6, 6, 4, 4, 0}};
  node* index_stack_check = NULL;

  int res =
      load_array(filename, &vertex_array, &vertices_coordinates, &index_stack,
                 &poligon_counter);  // выполнение команды
  ck_assert_int_eq(res, 0);          // проверка выполнения

  for (int i = 0; i < 24; i++) {
    ck_assert_double_eq_tol(vertex_array[i], vertex_array_true[i],
                            0.01);  // проверка координат
  }
  ck_assert_int_eq(poligon_counter,
                   poligon_counter_true);  // проверка кол-ва полигонов
  ck_assert_int_eq(vertices_coordinates,
                   vertices_coordinates_true);  // счетчика координат
  index_stack_check = index_stack;
  for (int i = 0; i < 11; i++) {
    ck_assert_int_eq(
        index_stack_check->size_of_array,
        index_array[i][0]);  // проверка совпадения размеров полигонов
    for (int j = 1; j <= index_array[i][0]; j++) {
      ck_assert_double_eq_tol(index_stack_check->index_array[j - 1],
                              index_array[i][j],
                              0.01);  // проверка совпадения вершин полигонов
    }
    index_stack_check = index_stack_check->next_node;
  }
  free_model_data(&vertex_array, &vertices_coordinates, &index_stack,
                  &poligon_counter);
}
END_TEST

Suite* s21_load_suite() {
  Suite* suite = suite_create("load");
  TCase* tcase_core = tcase_create("load");

  tcase_add_test(tcase_core, test_0);
  suite_add_tcase(suite, tcase_core);

  return suite;
}