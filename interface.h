#ifndef INTERFACE
#define INTERFACE

#pragma once

#include "error.h"
#include "set.h"
#include "parcer.h"

#define BUF_LENGTH 32

char* Read(error_t* error);

list_of_set_t* Exit(list_of_set_t* setsList, error_t* error);
list_of_set_t* Help(list_of_set_t* listSet, error_t* error);

void WriteError(error_t* error);

#endif