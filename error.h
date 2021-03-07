#ifndef ERROR
#define ERROR

#pragma once

typedef enum {
  ALL_OK,       //������ ���
  READ_ERROR,   //������ ������ (� ����� � ������� ������)
  MEMORY_ERROR, //������ ������
  ELEM_ERROR,
  NAME_ERROR,   //������ ���������� (������������ ������ ��� ����������)
  ElEM_NOT_FOUND,
  SET_NOT_FOUND,
  UNEXPECTED_OPERAND,
  UNEXPECTED_OPERATION,
  NOT_ENOUGHT_ARGUMENT,
  ERROR_EXPRESSION,
} error_t;


#endif