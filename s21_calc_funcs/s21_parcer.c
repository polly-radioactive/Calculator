#include "s21_calc.h"

int parser(char *str, N *stack) {
  char c, chislo[256], func[256];
  double value;
  int i = 0, j = 0, flag = 0;
  for (int k = 0; str[k] != '\0'; k++) {
    c = str[k];
    if (isdigit(c) || c == '.') {
      chislo[i] = c;
      i++;
      flag = 1;
    } else {
      if (flag == 1) {
        value = atof(chislo);
        push_number(stack, value);
      }
      flag = 2;
      if (c == 'm' || c == 'o' || c == 'd' || c == 's' || c == 'q' ||
          c == 'r' || c == 't' || c == 'l' || c == 'n' || c == 'g' ||
          c == 'c' || c == 's' || c == 'i' || c == 'a') {
        func[j] = c;
        j++;
      }
      while (i > 0) {
        chislo[i] = 0;
        i--;
      }
      i = 0;
      if (c == 'x') {
        push_char(stack, x, 0);
      }
      if (c == '(') {
        push_char(stack, left_bracket, -1);
        if (str[k + 1] == '-' || str[k + 1] == '+') {
          push_number(stack, 0);
        }
      }
      if (c == ')' || c == '+' || c == '-' || c == '*' || c == '/' ||
          c == '^') {
        math_sign(stack, c);
      }
      if (func[0] != '\0') {
        j = func_main(stack, func, j);
      }
    }
  }
  return 0;
}

void math_sign(N *stack, char c) {
  if (c == ')') {
    push_char(stack, right_bracket, -1);
  }
  if (c == '+') {
    push_char(stack, plus, 1);
  }
  if (c == '-') {
    push_char(stack, minus, 1);
  }
  if (c == '*') {
    push_char(stack, mult, 2);
  }
  if (c == '/') {
    push_char(stack, division, 2);
  }
  if (c == '^') {
    push_char(stack, pow_l, 3);
  }
}

int func_main(N *stack, char func[], int j) {
  if (func[0] == 'm' && func[1] == 'o' && func[2] == 'd') {
    push_char(stack, mod, 2);
    clear(j, func);
    j = 0;
  }
  if (func[0] == 's' && (func[1] == 'q' || func[1] == 'i') &&
      (func[2] == 'r' || func[2] == 'n')) {
    j = s_func(stack, func, j);
  }

  if (func[0] == 'l' && (func[1] == 'n' || func[1] == 'o')) {
    j = l_func(stack, func, j);
  }
  if (func[0] == 'c' && func[1] == 'o' && func[2] == 's') {
    push_char(stack, cos_l, 4);
    clear(j, func);
    j = 0;
  }
  if (func[0] == 't' && func[1] == 'a' && func[2] == 'n') {
    push_char(stack, tan_l, 4);
    clear(j, func);
    j = 0;
  }
  if (func[0] == 'a' && (func[1] == 'c' || func[1] == 's' || func[1] == 't') &&
      (func[2] == 'o' || func[2] == 'i' || func[2] == 'a') &&
      (func[3] == 'n' || func[3] == 's')) {
    j = a_func(stack, func, j);
  }
  return j;
}

int a_func(N *stack, char func[], int j) {
  if (func[0] == 'a' && func[1] == 'c' && func[2] == 'o' && func[3] == 's') {
    push_char(stack, acos_l, 4);
    clear(j, func);
    j = 0;
  }
  if (func[0] == 'a' && func[1] == 's' && func[2] == 'i' && func[3] == 'n') {
    push_char(stack, asin_l, 4);
    clear(j, func);
    j = 0;
  }
  if (func[0] == 'a' && func[1] == 't' && func[2] == 'a' && func[3] == 'n') {
    push_char(stack, atan_l, 4);
    clear(j, func);
    j = 0;
  }
  return j;
}

int s_func(N *stack, char func[], int j) {
  if (func[0] == 's' && func[1] == 'q' && func[2] == 'r' && func[3] == 't') {
    push_char(stack, sqrt_l, 3);
    clear(j, func);
    j = 0;
  }
  if (func[0] == 's' && func[1] == 'i' && func[2] == 'n') {
    push_char(stack, sin_l, 4);
    clear(j, func);
    j = 0;
  }
  return j;
}

int l_func(N *stack, char func[], int j) {
  if (func[0] == 'l' && func[1] == 'n') {
    push_char(stack, ln, 4);
    clear(j, func);
    j = 0;
  }
  if (func[0] == 'l' && func[1] == 'o' && func[2] == 'g') {
    push_char(stack, log_l, 4);
    clear(j, func);
    j = 0;
  }
  return j;
}