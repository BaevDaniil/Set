#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "set.h"
#include <locale.h>
//#include "error.h"
#pragma warning(disable: 4996)

int main(void) {
  char* str = NULL;
  error_t error = ALL_OK;
  list_of_set_t* listSet = NULL;
  expression_t expression;

  setlocale(LC_CTYPE, "rus");

  printf("Enter \"Help\" for help\n");

  while (error == ALL_OK) {
    str = Read(&error);
    if (error != ALL_OK) {
      break;
    }
    expression = Parse(str, &error);
    if (error == ALL_OK) {
      switch (expression.type) {
      case ARG_0:
        expression.operation.func_0_arg.function(listSet, &error);
        break;
      case ARG_1:
        listSet = expression.operation.func_1_arg.function(listSet, &error, expression.arg1.name);
        break;
      case ARG_2:
        listSet = expression.operation.func_2_arg.function(listSet, &error, expression.arg1.name, expression.arg2.name);
        break;
      case ARG_3:
        listSet = expression.operation.func_3_arg.function(listSet, &error, expression.result.name, expression.arg1.name, expression.arg2.name);
        break;
      }
      WriteError(&error);
    }
    else {
      WriteError(&error);
    }
    free(str);
  }

  DeleteAll(listSet);
  
  return 0;
}