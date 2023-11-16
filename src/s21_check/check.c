#include "s21_check.h"

void do_suite(Suite *suite, int *res) {
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  *res += srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int res = 0;
  do_suite(s21_load_suite(), &res);
  do_suite(s21_transformations_suite(), &res);
  if (res) {
    printf("\e[0;31m\tTEST RESULT: FAILURE\e[0m\n");
  } else {
    printf("\e[0;32m\tTEST RESULT: SUCCESS\e[0m\n");
  }
  return 0;
}
