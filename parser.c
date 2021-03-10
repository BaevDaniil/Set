#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parcer.h"
#pragma warning(disable: 4996)

int isFunction(unsigned char str[], int begin, int end, func_t* operation) {
  char operationsName[][MAX_FUNC_NAME_LEN] = { FUNCTION_0_ARG_NAME, FUNCTION_1_ARG_NAME, FUNCTION_2_ARG_NAME, FUNCTION_3_ARG_NAME, 0 };
  enum { FUNCTION_0_ARG_ID, FUNCTION_1_ARG_ID, FUNCTION_2_ARG_ID, FUNCTION_3_ARG_ID} operationsID;
  function_0_arg_t functionArg0[] = { FUNCTION_0_ARG_POINTER };
  function_1_arg_t functionArg1[] = { FUNCTION_1_ARG_POINTER };
  function_2_arg_t functionArg2[] = { FUNCTION_2_ARG_POINTER };
  function_3_arg_t functionArg3[] = { FUNCTION_3_ARG_POINTER };
  char lexeme[LENGTH_NAME];
  int i = 0;

  strncpy(lexeme, &(char)str[begin], end - begin);
  lexeme[end - begin] = 0;
  while (operationsName[i][0] != 0) {
    if (strcmp(operationsName[i], lexeme) == 0) {
      operationsID = i;
      if (operationsID <= (FUNCTION_0_ARG_ID)) {
        operation->func_0_arg.function = functionArg0[operationsID].function;
        return ARG_0;
      }
      if (operationsID <= (FUNCTION_1_ARG_ID)) {
        operation->func_1_arg.function = functionArg1[operationsID - (FUNCTION_0_ARG_ID) - 1].function;
        return ARG_1;
      }
      if (operationsID <= (FUNCTION_2_ARG_ID)) {
        operation->func_2_arg.function = functionArg2[operationsID - (FUNCTION_1_ARG_ID) - 1].function;
        return ARG_2;
      }
      if (operationsID <= (FUNCTION_3_ARG_ID)) {
        operation->func_3_arg.function = functionArg3[operationsID - (FUNCTION_2_ARG_ID) - 1].function;
        return ARG_3;
      }
    }
    i++;
  }
  return -1;
}

expression_t Parse(unsigned char str[], error_t* error) {
  int i = 0;
  int begin, end;
  int n = 0;
  int type;
  expression_t expression;

  expression.type = -1;
  expression.arg1.flag = 0;
  expression.arg2.flag = 0;
  expression.result.flag = 0;

  while (str[i] != 0) {
    while ((isspace((int)str[i]))) {
      i++;
    }
    if (str[i] == 0) {
      break;
    }

    if (str[i] == '=' && n == 1) {
      i++;
      n++;
      while ((isspace((int)str[i]))) {
        i++;
      }
    }
    else if (str[i] == '=') {
      *error = UNEXPECTED_OPERATION;
      return expression;
    }

    if (str[i] == '"') {
      begin = i + 1;
      i++;
      while (str[i] != '"' && str[i] != 0) {
        i++;
      }
      end = i;
      if (str[i] == 0 && str[end] != '"') {
        *error = NAME_ERROR;
        return expression;
      }
      i++;
    }
    else {
      begin = i;
      while (!(isspace((int)str[i])) && str[i] != 0) {
        i++;
      }
      end = i;
    }

    if ((end - begin + 1) > LENGTH_NAME) {
      *error = NAME_ERROR;
      return expression;
    }

    if ((type = isFunction(str, begin, end, &(expression.operation))) != -1) {
      if (n != 0 && n != 2) {
        *error = UNEXPECTED_OPERATION;
        return expression;
      }
      n++;
      expression.type = type;
    }
    else {
      if (n == 0) {
        if (end - begin > 0) {
          strncpy(expression.result.name, &(char)str[begin], end - begin);
          expression.result.name[end - begin] = 0;
          expression.result.flag = 1;
          n++;
        }
        else {
          *error = NAME_ERROR;
          return expression;
        }
      }
      else if (n == 3 || (n == 1 && expression.result.flag == 0)) {
        if (end - begin > 0) {
          strncpy(expression.arg1.name, &(char)str[begin], end - begin);
          expression.arg1.name[end - begin] = 0;
          expression.arg1.flag = 1;
          n++;
        }
        else {
          *error = NAME_ERROR;
          return expression;
        }
      }
      else if (n == 4 || n == 2) {
        if (end - begin > 0) {
          strncpy(expression.arg2.name, &(char)str[begin], end - begin);
          expression.arg2.name[end - begin] = 0;
          expression.arg2.flag = 1;
          n++;
        }
        else {
          *error = NAME_ERROR;
          return expression;
        }
      }
      else {
        *error = UNEXPECTED_OPERAND;
        return expression;
      }
    }
  }
  if (expression.type != (expression.result.flag + expression.arg1.flag + expression.arg2.flag + n)) {
    *error = ERROR_EXPRESSION;
  }
  return expression;
}