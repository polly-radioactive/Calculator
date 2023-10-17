#include "s21_test_calc.h"

START_TEST(parser_1) {
  N stack;
  stack.top = -1;
  char *str = " 1 + 2 * 5 / 10 ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  clean_stack(stack);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(parser_2) {
  N stack;
  stack.top = -1;
  char *str = " 2 * 5 /  ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  clean_stack(stack);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(parser_3) {
  N stack;
  stack.top = -1;
  char *str = " ( 5 - 3  ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  clean_stack(stack);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(parser_4) {
  N stack;
  stack.top = -1;
  char *str = "  5 - 3 ) ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  clean_stack(stack);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(parser_5) {
  N stack;
  stack.top = -1;
  char *str = " - 3 ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  clean_stack(stack);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(parser_6) {
  N stack;
  stack.top = -1;
  char *str = " + 3 * cos ( x ) ^ 6 - sin ( 5.7 ) + sqrt ( 4 * ln  ( 34.9 ) ) ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  clean_stack(stack);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(parser_7) {
  N stack;
  stack.top = -1;
  char *str =
      " 3mod7 * asin( x ) + acos( 56 ) - log( 34 ) - atan( x )  / tan( 9 ) ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  clean_stack(stack);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(parser_8) {
  N stack;
  stack.top = -1;
  char *str = " 3*() ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  clean_stack(stack);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(parser_9) {
  N stack;
  stack.top = -1;
  char *str = " 3*(6*+8) ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  clean_stack(stack);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(parser_10) {
  N stack;
  stack.top = MAX - 1;
  int res = isfull(&stack);
  clean_stack(stack);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(parser_11) {
  N stack;
  stack.top = -1;
  char *str = " (1+2)5 ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  stack=clean_stack(stack);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(parser_12) {
  N stack;
  stack.top = -1;
  char *str = " 5(1+2) ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  stack=clean_stack(stack);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(parser_13) {
  N stack;
  stack.top = -1;
  char *str = " (+5)+(+5) ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  stack=clean_stack(stack);
  ck_assert_int_eq(res, 0);
}
END_TEST

// START_TEST(calc_1) {
//   char *str = " 1 + 2 * 5 / 10 ";
//   double res = main_calc(str);
//   ck_assert_float_eq(res, 2);
// }
// END_TEST

// START_TEST(calc_2) {
//   char *str = " (1 + 2) * 5 / 10 ";
//   double res = main_calc(str);
//   ck_assert_float_eq(res, 1.5);
// }
// END_TEST

// START_TEST(calc_3) {
//   char *str = " sin (1 + 2) * cos( 5 )  ^ 2 ";
//   double res = main_calc(str);
//   ck_assert_float_eq(res, 0.01135511355);
// }
// END_TEST

// START_TEST(calc_4) {
//   char *str = " 3 mod 5 * tan ( 23 + ln ( 56 )) ";
//   double res = main_calc(str);
//   ck_assert_float_eq(res, -8.9980929390);
// }
// END_TEST

// START_TEST(calc_5) {
//   char *str = " asin(0.45) - acos(0.56) ";
//   double res = main_calc(str);
//   ck_assert_float_eq(res, -0.5096451877);
// }
// END_TEST

// START_TEST(calc_6) {
//   char *str = " 34.67 * atan (0.23) *( sqrt(9) + log (0.5)) ";
//   double res = main_calc(str);
//   ck_assert_float_eq(res, 21.1539628410);
// }
// END_TEST

// START_TEST(calc_7) {
//   N stack;
//   stack.top = -1;
//   char *str = " 56 / 0 ";
//   parser(str, &stack);
//   stack = inverse(&stack);
//   stack = convert_to_reverse_polish_notation(&stack,0);
//   N final ;
//   final.top = -1;
//   int res = calc_reverse_polish_notation(&stack, &final);
//   stack=clean_stack(stack);
//   final=clean_stack(final);
//   ck_assert_int_eq(res, 2);
// }
// END_TEST

// START_TEST(calc_8) {
//   N stack;
//   stack.top = -1;
//   char *str = " 35mod0 ";
//   parser(str, &stack);
//   stack = inverse(&stack);
//   stack = convert_to_reverse_polish_notation(&stack,0);
//   N final;
//   final.top = -1;
//   int res = calc_reverse_polish_notation(&stack, &final);
//   stack=clean_stack(stack);
//   final=clean_stack(final);
//   ck_assert_int_eq(res, 2);
// }
// END_TEST

// START_TEST(calc_9) {
//   N stack ;
//   stack.top = -1;
//   char *str = " sqrt(-57) ";
//   parser(str, &stack);
//   stack = inverse(&stack);
//   stack = convert_to_reverse_polish_notation(&stack,0);
//   N final ;
//   final.top = -1;
//   int res = calc_reverse_polish_notation(&stack, &final);
//   stack=clean_stack(stack);
//   final=clean_stack(final);
//   ck_assert_int_eq(res, 2);
// }
// END_TEST


// START_TEST(calc_10) {
//   char *str = " -1*7 ";
//   double res = main_calc(str);
//   ck_assert_float_eq(res, -7);
// }
// END_TEST

// START_TEST(calc_11) {
//   N stack;
//   stack.top = -1;
//   char *str = " x*2 ";
//   parser(str, &stack);
//   stack = inverse(&stack);
//   double x =10;
//   stack = convert_to_reverse_polish_notation(&stack, x);
//   N final;
//   final.top = -1;
//   calc_reverse_polish_notation(&stack, &final);
//   double res=final.value[final.top];
//   stack=clean_stack(stack);
//   final=clean_stack(final);
//   ck_assert_float_eq(res, 20);
// }
// END_TEST

Suite *suite_parser(void) {
  Suite *s = suite_create("Checking s21_check_parser...");
  TCase *tcase = tcase_create("parser");
  tcase_add_test(tcase, parser_1);
  tcase_add_test(tcase, parser_2);
  tcase_add_test(tcase, parser_3);
  tcase_add_test(tcase, parser_4);
  tcase_add_test(tcase, parser_5);
  tcase_add_test(tcase, parser_6);
  tcase_add_test(tcase, parser_7);
  tcase_add_test(tcase, parser_8);
  tcase_add_test(tcase, parser_9);
  tcase_add_test(tcase, parser_10);
  tcase_add_test(tcase, parser_11);
  tcase_add_test(tcase, parser_12);
  tcase_add_test(tcase, parser_13);
  suite_add_tcase(s, tcase);
  return s;
}

// Suite *suite_calc(void) {
//   Suite *s = suite_create("Checking s21_check_calc...");
//   TCase *tcase = tcase_create("calc");
//   tcase_add_test(tcase, calc_1);
//   tcase_add_test(tcase, calc_2);
//   tcase_add_test(tcase, calc_3);
//   tcase_add_test(tcase, calc_4);
//   tcase_add_test(tcase, calc_5);
//   tcase_add_test(tcase, calc_6);
//   tcase_add_test(tcase, calc_7);
//   tcase_add_test(tcase, calc_8);
//   tcase_add_test(tcase, calc_9);
//   tcase_add_test(tcase, calc_10);
//   tcase_add_test(tcase, calc_11);
//   suite_add_tcase(s, tcase);
//   return s;
// }

int main(void) {
  int total = 1;
  Suite *test_cases[1];
  test_cases[0] = suite_parser();
  // test_cases[1] = suite_calc();

  for (int i = 0; i < total; i++) {
    SRunner *runner = srunner_create(test_cases[i]);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    srunner_free(runner);
  }
}