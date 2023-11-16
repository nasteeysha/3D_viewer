#ifndef SRC_S21_CHECK_H_
#define SRC_S21_CHECK_H_

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void do_suite(Suite *suite, int *res);

Suite *s21_load_suite();
Suite *s21_transformations_suite();

#endif  // SRC_S21_CHECK_H_