#include "s21_calc.h"

void push_number(N *stack, double item) {
  if (isfull(stack) == 1) {
    error(overflow);
  } else {
    stack->top++;
    stack->value[stack->top] = item;
    stack->priority[stack->top] = 0;
    stack->type[stack->top] = number;
  }
}

void push_char(N *stack, int item, int priority) {
  if (isfull(stack) == 1) {
    error(overflow);
  } else {
    stack->top++;
    stack->type[stack->top] = item;
    stack->value[stack->top] = 0;
    stack->priority[stack->top] = priority;
  }
}

double pop_value(N *stack) {
  double result = stack->value[stack->top];
  stack->top--;
  return result;
}

int pop_type(N *stack) {
  int result = stack->type[stack->top];
  stack->top--;
  return result;
}

void clear(int j, char item[]) {
  while (j >= 0) {
    item[j] = 0;
    j--;
  }
}

int print_stack_value(N *stack) {
  if (stack->top == -1) {
    printf("Stack empty\n");
  } else {
    for (int i = 0; i <= stack->top; i++) {
      printf(" %f |", stack->value[i]);
    }
    printf("\n");
  }
}

int print_stack_type(N *stack) {
  if (stack->top == -1) {
    printf("Stack empty\n");
  } else {
    for (int i = 0; i <= stack->top; i++) {
      printf(" %d |", stack->type[i]);
    }
    printf("\n");
  }
}

int print_stack_priority(N *stack) {
  if (stack->top == -1) {
    printf("Stack empty\n");
  } else {
    for (int i = 0; i <= stack->top; i++) {
      printf(" %d |", stack->priority[i]);
    }
    printf("\n");
  }
}

N inverse(N *stack) {
  N tmp;
  tmp.top = -1;
  for (int i = stack->top; i >= 0; i--) {
    if (stack->type[i] == number) {
      push_number(&tmp, stack->value[i]);
      pop_value(stack);
    } else {
      push_char(&tmp, stack->type[i], stack->priority[i]);
      pop_type(stack);
    }
  }
  return tmp;
}
