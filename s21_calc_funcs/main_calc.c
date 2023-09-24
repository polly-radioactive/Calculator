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
  return res;
}

N clean_stack(N stack){
  while (stack.top!=-1)
  {
    stack.value[stack.top]=0;
    stack.type[stack.top]=0;
    stack.priority[stack.top]=0;
    stack.top--;
  }
  return stack;
}

int main(){
    N stack;
  stack.top = -1;
  char *str = " 1 + 2 * 5 / 10 ";
  parser(str, &stack);
  stack = inverse(&stack);
  int res = find_error(&stack);
  printf("res: %d\n", res);
  print_stack_type(&stack);
  stack=clean_stack(stack);
  print_stack_type(&stack);
}