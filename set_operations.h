#ifndef SET_OPERATON
#define SET_OPERATON

#pragma once

#include "set.h"

list_of_set_t* Union(list_of_set_t* setsList, error_t* error,const char nameResult[LENGTH_NAME], const char nameArg1[LENGTH_NAME], const char nameArg2[LENGTH_NAME]);
list_of_set_t* Intersection(list_of_set_t* setsList, error_t* error, const char nameResult[LENGTH_NAME], const char nameArg1[LENGTH_NAME], const char nameArg2[LENGTH_NAME]);
list_of_set_t* Difference(list_of_set_t* setsList, error_t* error, const char nameResult[LENGTH_NAME], const char nameArg1[LENGTH_NAME], const char nameArg2[LENGTH_NAME]);
list_of_set_t* SymmetricDifference(list_of_set_t* setsList, error_t* error, const char nameResult[LENGTH_NAME], const char nameArg1[LENGTH_NAME], const char nameArg2[LENGTH_NAME]);

list_of_set_t* CheckSubsets(list_of_set_t* setsList, error_t* error, const char nameArg1[LENGTH_NAME], const char nameArg2[LENGTH_NAME]);

#endif