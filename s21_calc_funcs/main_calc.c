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
  stack = clean_stack(stack);
  final = clean_stack(final);
  return res;
}

N clean_stack(N stack) {
  if (stack.top <= -1) {
    stack.top = -1;
  } else {
    while (stack.top != -1) {
      stack.value[stack.top] = 0;
      stack.type[stack.top] = 0;
      stack.priority[stack.top] = 0;
      stack.top--;
    }
  }
  return stack;
}

// int main() {
//   double x_v = 0;
//   char *str = " (1 + 2) * 5 / 10 ";
//   double result = 0;
//   N stack;
//   stack.top = -1;
//   parser(str, &stack);
//   // printf("After parser\n");
//   // print_stack_value(&stack);
//   // print_stack_type(&stack);
//   stack = inverse(&stack);
//   // printf("After inverse\n");
//   // print_stack_value(&stack);
//   // print_stack_type(&stack);
//   int flag = find_error(&stack);
//   if (flag == SUCCESS) {
//     stack = convert_to_reverse_polish_notation(&stack, x_v);
//     // printf("After convert\n");
//     // print_stack_value(&stack);
//     // print_stack_type(&stack);
//     N final;
//     final.top = -1;
//     flag = calc_reverse_polish_notation(&stack, &final);
//     // printf("After calc\n");
//     // print_stack_value(&stack);
//     // print_stack_type(&stack);
//     // printf("Final\n");
//     // print_stack_value(&final);
//     // print_stack_type(&final);
//     if (flag == SUCCESS) {
//       result = final.value[final.top];
//       printf("result: %f \n", result);
//     } else {
//       printf("Error\n");
//     }
//     final = clean_stack(final);
//   } else {
//     printf("Error\n");
//   }
//   stack = clean_stack(stack);
// }