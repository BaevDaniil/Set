#ifndef PARCER
#define PARCER

#pragma once

#include "interface.h"
#include "error.h"
#include "set.h"
#include "set_operations.h"

#define MAX_FUNC_NAME_LEN 20

//Структуры для функций управления

//Функции вида Function
#define FUNCTION_0_ARG_NAME "WriteSetNames", "Exit", "Help"
#define FUNCTION_0_ARG_ID WRITE_SET_NAMES, EXIT, HELP
#define FUNCTION_0_ARG_POINTER WriteSetNames, Exit, Help
typedef struct {
  list_of_set_t* (*function)(list_of_set_t* setsList, error_t* error);
} function_0_arg_t;

//Функции вида Function arg
#define FUNCTION_1_ARG_NAME "Create", "Delete", "WriteElems", "WriteCard"
#define FUNCTION_1_ARG_ID CREATE, DELETE, WRITE_ELEMS, WRITE_CARD
#define FUNCTION_1_ARG_POINTER Create, Delete, WriteElems, WriteCard
typedef struct {
  list_of_set_t* (*function)(list_of_set_t* setsList, error_t* error, const char arg[LENGTH_NAME]);
} function_1_arg_t;

//Функции вида Function arg1 arg2
#define FUNCTION_2_ARG_NAME "AddElem", "DeleteElem", "CheckSubsets", "CheckElem"
#define FUNCTION_2_ARG_ID ADD_ELEM, DELETE_ELEM, CHECK_SUBSETS, CHECK_ELEM
#define FUNCTION_2_ARG_POINTER AddElem, DeleteElem, CheckSubsets, CheckElem
typedef struct {
  list_of_set_t* (*function)(list_of_set_t* setsList, error_t* error, const char arg1[LENGTH_NAME], const char arg2[LENGTH_NAME]);
} function_2_arg_t;

//Функции вида arg1 = Function arg2 arg3
#define FUNCTION_3_ARG_NAME "Union", "Intersection", "Difference", "SymDifference"
#define FUNCTION_3_ARG_ID UNION, INTERSECTION, DIFFERENCE, SYM_DIFFERENCE
#define FUNCTION_3_ARG_POINTER Union, Intersection, Difference, SymmetricDifference
typedef struct {
  list_of_set_t* (*function)(list_of_set_t* setsList, error_t* error, const char arg1[LENGTH_NAME], const char arg2[LENGTH_NAME], const char arg3[LENGTH_NAME]);
} function_3_arg_t;

//Объединение для разных типов функций
typedef union {
  function_0_arg_t func_0_arg;
  function_1_arg_t func_1_arg;
  function_2_arg_t func_2_arg;
  function_3_arg_t func_3_arg;
} func_t;

typedef struct {
  int flag;
  char name[LENGTH_NAME];
} operand_t;

typedef enum {
  ARG_0 = 1,
  ARG_1 = 3,
  ARG_2 = 5,
  ARG_3 = 8,
} oper_type_t;

//УТД выражение
typedef struct {
  oper_type_t type;
  func_t operation;
  operand_t result;
  operand_t arg1;
  operand_t arg2;
} expression_t;

expression_t Parse(char str[], error_t* error);

#endif