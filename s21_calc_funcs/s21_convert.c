#include "s21_calc.h"

N convert_to_reverse_polish_notation(N *stack, double x_value) {
  if (find_error(stack) == SUCCESS) {
    N ready;
    ready.top = -1;
    N support;
    support.top = -1;
    if (stack->type[stack->top] == minus || stack->type[stack->top] == plus) {
      push_number(&ready, 0);
    }
    while (stack->top >= 0) {
      if (stack->type[stack->top] == number) {
        push_number(&ready, stack->value[stack->top]);
        pop_type(stack);
      } else if (stack->type[stack->top] == x) {
        push_number(&ready, x_value);
        pop_type(stack);
      } else {
        if (stack->priority[stack->top] > support.priority[support.top]) {
          push_char(&support, stack->type[stack->top],
                    stack->priority[stack->top]);
          pop_type(stack);
        } else if (stack->priority[stack->top] <=
                       support.priority[support.top] &&
                   stack->type[stack->top] != left_bracket &&
                   stack->type[stack->top] != right_bracket) {
          while (stack->priority[stack->top] <= support.priority[support.top]) {
            push_char(&ready, support.type[support.top],
                      support.priority[support.top]);
            pop_type(&support);
          }

          if (stack->priority[stack->top] > support.priority[support.top] &&
              stack->type[stack->top] != left_bracket &&
              stack->type[stack->top] != right_bracket) {
            push_char(&support, stack->type[stack->top],
                      stack->priority[stack->top]);
            pop_type(stack);
          }
        }

        if (stack->type[stack->top] == left_bracket) {
          push_char(&support, stack->type[stack->top],
                    stack->priority[stack->top]);
          pop_type(stack);
        }
        if (stack->type[stack->top] == right_bracket) {
          while (support.type[support.top] != left_bracket) {
            push_char(&ready, support.type[support.top],
                      support.priority[support.top]);
            pop_type(&support);
          }
          pop_type(&support);
          pop_type(stack);
        }
      }
    }
    while (support.top >= 0) {
      push_char(&ready, support.type[support.top],
                support.priority[support.top]);
      pop_type(&support);
    }
    return ready;
  }
}