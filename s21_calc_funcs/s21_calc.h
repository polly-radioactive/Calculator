#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10000
#define SUCCESS 0
#define FAILURE 2

typedef enum {
  div_zero,
  math_error,
  overflow,
  brackets_error,
  input_missing,
  invalid,
  input_error
} Error;

enum type {
  zero,
  number,
  x,
  plus,
  minus,
  mult,
  division,
  pow_l,
  mod,
  sqrt_l,
  ln,
  log_l,
  cos_l,
  sin_l,
  tan_l,
  acos_l,
  asin_l,
  atan_l,
  left_bracket,
  right_bracket
};

struct stack {
  double value[MAX];
  int priority[MAX];
  int type[MAX];
  int top;
};
typedef struct stack N;

// error
int isfull(N *stack);
void error(int err);
int find_error(N *stack);

// base_func
void push_number(N *stack, double item);
void push_char(N *stack, int item, int priority);
double pop_value(N *stack);
int pop_type(N *stack);
void clear(int j, char item[]);
// int print_stack_value(N *stack);
// int print_stack_type(N *stack);
// int print_stack_priority(N *stack);
N inverse(N *stack);

// parser
int parser(char *str, N *stack);
void math_sign(N *stack, char c);
int func_main(N *stack, char func[], int j);
int a_func(N *stack, char func[], int j);
int s_func(N *stack, char func[], int j);
int l_func(N *stack, char func[], int j);

// convert
N convert_to_reverse_polish_notation(N *stack, double value_x);

// calc
int calc_reverse_polish_notation(N *stack, N *final);
int item_f(int item, int result, N *final);
int division_f(N *final, int result);
void pow_f(N *final);
int mod_f(N *final, int result);
int sqrt_f(N *final, int result);
int ln_f(N *final, int result);
int log_f(N *final, int result);

// main
double main_calc(char *str);
N clean_stack(N stack);

// credit
