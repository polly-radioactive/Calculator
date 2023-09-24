#include "s21_calc.h"

int isfull(N *stack) {
  if (stack->top == MAX - 1) {
    error(overflow);
    return 1;
  } else {
    return 0;
  }
}

void error(int err) {
  char *m;
  switch (err) {
    case div_zero:
      m = "Divide by zero";
      break;
    case overflow:
      m = "Overflow";
      break;
    case brackets_error:
      m = "Mismatched parentheses";
      break;
    case input_missing:
      m = "Function input missing";
      break;
    case math_error:
      m = "Invalid math operation";
    case invalid:
      m = "Invalid syntax";
    case input_error:
      m = "Input Error";
  }
  printf("\tError: %s\n", m);
}

int find_error(N *stack) {
  int result = SUCCESS;
  int count_r = 0, count_l = 0;
  for (int i = 0; i <= stack->top; i++) {
    if (stack->type[i] == right_bracket) {
      count_r++;
    }
    if (stack->type[i] == left_bracket) {
      count_l++;
    }
    if (stack->type[i + 1] == left_bracket && stack->type[i] == right_bracket) {
      result = FAILURE;
      error(input_missing);
    }
    if ((stack->type[i] == plus || stack->type[i] == minus ||
         stack->type[i] == division || stack->type[i] == mult ||
         stack->type[i] == pow_l) &&
        (stack->type[i + 1] == plus || stack->type[i + 1] == minus ||
         stack->type[i + 1] == division || stack->type[i + 1] == mult ||
         stack->type[i + 1] == pow_l)) {
      result = FAILURE;
      error(invalid);
    }
    if (stack->type[0] == plus || stack->type[0] == minus ||
        stack->type[0] == division || stack->type[0] == mult ||
        stack->type[0] == pow_l || stack->type[0] == mod) {
      result = FAILURE;
      error(input_error);
    }
  }
  if (count_l != count_r) {
    result = FAILURE;
    error(brackets_error);
  }
  return result;
}
