#include "s21_calc.h"

double main_calc(char *str) {
  double res = 0;
  N stack;
  stack.top = -1;
  parser(str, &stack);
  stack = inverse(&stack);
  stack = convert_to_reverse_polish_notation(&stack, 0);
  N final;
  final.top = -1;
  calc_reverse_polish_notation(&stack, &final);
  res = final.value[final.top];
  clean_stack(stack);
  clean_stack(final);
  return res;
}

N clean_stack(N stack) {
  while (stack.top != -1) {
    stack.value[stack.top] = 0;
    stack.type[stack.top] = 0;
    stack.priority[stack.top] = 0;
    stack.top--;
  }
  return stack;
}

int main() {
  double x_v = 0;
  char *str = "34.67 * atan (0.23) *( sqrt(9) + log (0.5))";
  double result = 0;
  N stack;
  stack.top = -1;
  parser(str, &stack);
  stack = inverse(&stack);
  int flag = find_error(&stack);
  if (flag == SUCCESS) {
    stack = convert_to_reverse_polish_notation(&stack, x_v);
    N final;
    final.top = -1;
    flag = calc_reverse_polish_notation(&stack, &final);
    if (flag == SUCCESS) {
      result = final.value[final.top];
      printf("result: %f \n", result);
    } else {
      printf("Error\n");
    }
    clean_stack(final);
  } else {
    printf("Error\n");
  }
  clean_stack(stack);
}