#ifndef ERROR
#define ERROR

#pragma once

typedef enum {
  ALL_OK,       //Ошибки нет
  READ_ERROR,   //Ошибка чтения (в связи с ошибкой потока)
  MEMORY_ERROR, //Ошибка памяти
  ELEM_ERROR,
  NAME_ERROR,   //Ошибка именования (недопустимый размер или именование)
  ElEM_NOT_FOUND,
  SET_NOT_FOUND,
  UNEXPECTED_OPERAND,
  UNEXPECTED_OPERATION,
  NOT_ENOUGHT_ARGUMENT,
  ERROR_EXPRESSION,
} error_t;


#endif