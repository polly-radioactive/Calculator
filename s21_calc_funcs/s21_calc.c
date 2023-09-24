#include "s21_calc.h"

int calc_reverse_polish_notation(N* stack, N* final) {
  int result = SUCCESS;
  *stack = inverse(stack);
  int item;
  while (stack->top >= 0) {
    item = stack->type[stack->top];
    if (item == number) {
      push_number(final, stack->value[stack->top]);
    } else {
      result = item_f(item, result, final);
    }
    pop_type(stack);
  }
  return result;
}

int item_f(int item, int result, N* final) {
  switch (item) {
    case plus:
      push_number(final, pop_value(final) + pop_value(final));
      break;
    case minus:
      push_number(final, -(pop_value(final) - pop_value(final)));
      break;
    case mult:
      push_number(final, pop_value(final) * pop_value(final));
      break;
    case division:
      result = division_f(final, result);
      break;
    case pow_l:
      pow_f(final);
      break;
    case mod:
      result = mod_f(final, result);
      break;
    case sqrt_l:
      result = sqrt_f(final, result);
      break;
    case ln:
      result = ln_f(final, result);
      break;
    case log_l:
      result = log_f(final, result);
      break;
    case cos_l:
      push_number(final, cos(pop_value(final)));
      break;
    case sin_l:
      push_number(final, sin(pop_value(final)));
      break;
    case tan_l:
      push_number(final, tan(pop_value(final)));
      break;
    case acos_l:
      push_number(final, acos(pop_value(final)));
      break;
    case asin_l:
      push_number(final, asin(pop_value(final)));
      break;
    case atan_l:
      push_number(final, atan(pop_value(final)));
      break;
  }
  return result;
}

int division_f(N* final, int result) {
  double op1 = pop_value(final);
  double op2 = pop_value(final);
  if (op1 == 0) {
    error(div_zero);
    result = FAILURE;
  } else {
    push_number(final, op2 / op1);
  }
  return result;
}

void pow_f(N* final) {
  double op1 = pop_value(final);
  double op2 = pop_value(final);
  push_number(final, pow(op2, op1));
}

int mod_f(N* final, int result) {
  int n;
  double op1 = pop_value(final);
  double op2 = pop_value(final);
  if (op1 == 0) {
    error(div_zero);
    result = FAILURE;
  } else {
    push_number(final, 0);
    n = op2 / op1;
    push_number(final, op2 - n * op1);
  }
  return result;
}

int sqrt_f(N* final, int result) {
  double op1 = pop_value(final);
  if (op1 >= 0) {
    push_number(final, sqrt(op1));
  } else {
    error(math_error);
    result = FAILURE;
  }
  return result;
}

int ln_f(N* final, int result) {
  double op1 = pop_value(final);
  if (log(op1) != NAN || log(op1) != INFINITY) {
    push_number(final, log(op1));
  } else {
    error(math_error);
    result = FAILURE;
  }
  return result;
}

int log_f(N* final, int result) {
  double op1 = pop_value(final);
  if (log10(op1) != NAN || log10(op1) != INFINITY) {
    push_number(final, log10(op1));
  } else {
    error(math_error);
    result = FAILURE;
  }
  return result;
}