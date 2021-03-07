#ifndef SET
#define SET

#pragma once

#include "error.h"

#define LENGTH_ELEM 81
#define LENGTH_NAME 81

typedef char elemet_t[LENGTH_ELEM];

typedef struct elem {
  struct elem* next;
  elemet_t elem;
} set_t;

typedef struct set {
  struct set* next;
  set_t* set;
  int card;
  char name[LENGTH_NAME];
} list_of_set_t;

void DeleteAll(list_of_set_t* setsList);

list_of_set_t* WriteSetNames(list_of_set_t* setsList, error_t* error);

list_of_set_t* Create(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]);
list_of_set_t* Delete(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]);

list_of_set_t* CheckElem(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME], const char elem[LENGTH_ELEM]);
list_of_set_t* AddElem(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME], const char elem[LENGTH_ELEM]);
list_of_set_t* DeleteElem(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME], const char elem[LENGTH_ELEM]);

list_of_set_t* WriteElems(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]);
list_of_set_t* WriteCard(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]);

#endif