#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "interface.h"
#pragma warning(disable: 4996)

//Функция чтения строки из stdin
char* Read(error_t* error) {
  char *str = NULL, *testPointer = NULL;
  char buffer[BUF_LENGTH];
  int ch;
  int i, length = 1;

  //Циклическое чтение через буфер
  do {
    //Буферизация
    i = 0;
    do {
      ch = getchar();
      buffer[i] = (char)ch;
      i++;
    } while (ch != EOF && (char)ch != '\n' && i < BUF_LENGTH);
    //Выделение памяти
    testPointer = (char*)realloc(str, (length + i) * sizeof(char));
    if (testPointer == NULL) {
      free(str);
      *error = MEMORY_ERROR;
      return NULL;
    }
    str = testPointer;
    //Копирование буфера
    memcpy(str + length - 1, buffer, i + 1);
    length += i;
  } while (ch != EOF && (char)ch != '\n');

  //Запись нуля в конец строки (-2 чтобы обрезать последний считанный символ: первод строки)
  str[length - 2] = 0;
  *error = ch == EOF ? READ_ERROR : ALL_OK;
  return str;
}

//Функция обработки ошибок
void WriteError(error_t* error) {
  switch (*error) {
  case MEMORY_ERROR:
    printf("Not enopught memory\n");
    *error = ALL_OK;
    break;
  case NAME_ERROR:
    printf("Invalid name\n");
    *error = ALL_OK;
    break;
  case ELEM_ERROR:
    printf("Invalid elem\n");
    *error = ALL_OK;
    break;
  case ElEM_NOT_FOUND:
    printf("Elem not found\n");
    *error = ALL_OK;
    break;
  case SET_NOT_FOUND:
    printf("Set not found\n");
    *error = ALL_OK;
    break;
  case UNEXPECTED_OPERAND:
    printf("Unexpected operand\n");
    *error = ALL_OK;
    break;
  case UNEXPECTED_OPERATION:
    printf("Unexpected operation\n");
    *error = ALL_OK;
    break;
  case NOT_ENOUGHT_ARGUMENT:
    printf("Not enought argument\n");
    *error = ALL_OK;
    break;
  case ERROR_EXPRESSION:
    printf("Error expression\n");
    *error = ALL_OK;
    break;
  }
}

list_of_set_t* Exit(list_of_set_t* listSet, error_t* error) {
  *error = READ_ERROR;
  return listSet;
}

list_of_set_t* Help(list_of_set_t* listSet, error_t* error) {
  char operationsName[][MAX_FUNC_NAME_LEN] = { FUNCTION_0_ARG_NAME, FUNCTION_1_ARG_NAME, FUNCTION_2_ARG_NAME, FUNCTION_3_ARG_NAME, 0 };
  typedef enum { FUNCTION_0_ARG_ID, FUNCTION_1_ARG_ID, FUNCTION_2_ARG_ID, FUNCTION_3_ARG_ID } operationsID_t;
  printf("Names\nSet names are limited to 80 characters\nElement length is limited to 80 characters\nNames containing delimiters should be written in quotation marks\n\n");
  printf("\n");
  printf("Actions with sets\n\n");
  printf("%s - create set.\nExample: %s set, %s \"set one\"\n\n", operationsName[CREATE], operationsName[CREATE], operationsName[CREATE]);
  printf("%s - delete set.\nExample: %s set, %s \"set one\"\n\n", operationsName[DELETE], operationsName[DELETE], operationsName[DELETE]);
  printf("%s - writes all elements of set.\nExample: %s set, %s \"set one\"\n\n", operationsName[WRITE_ELEMS], operationsName[WRITE_ELEMS], operationsName[WRITE_ELEMS]);
  printf("%s - writes cardinality of set.\nExample: %s set, %s \"set one\"\n\n", operationsName[WRITE_CARD], operationsName[WRITE_CARD], operationsName[WRITE_CARD]);
  printf("\n");
  printf("Actions with elements\n\n");
  printf("%s - adds an element to the set.\nExample: %s set a, %s \"set one\" Word, %s set one \"a b c d\"\n\n", operationsName[ADD_ELEM], operationsName[ADD_ELEM], operationsName[ADD_ELEM], operationsName[ADD_ELEM]);
  printf("%s - removes an element from the set.\nExample: %s set a, %s \"set one\" Word, %s set one \"a b c d\"\n\n", operationsName[DELETE_ELEM], operationsName[DELETE_ELEM], operationsName[DELETE_ELEM], operationsName[DELETE_ELEM]);
  printf("%s - checks if an element is in the set.\nExample: %s set a, %s \"set one\" Word, %s set one \"a b c d\"\n\n", operationsName[CHECK_ELEM], operationsName[CHECK_ELEM], operationsName[CHECK_ELEM], operationsName[CHECK_ELEM]);
  printf("\n");
  printf("Operations\n\n");
  printf("%s - calc union of two sets. Requires a set to write the result\nExample: set1 = %s set2 set3\n\n", operationsName[UNION], operationsName[UNION]);
  printf("%s - calc intersection of two sets. Requires a set to write the result\nExample: set1 = %s set2 set3\n\n", operationsName[INTERSECTION], operationsName[INTERSECTION]);
  printf("%s - calc difference of two sets. Requires a set to write the result\nExample: set1 = %s set2 set3\n\n", operationsName[DIFFERENCE], operationsName[DIFFERENCE]);
  printf("%s - calc symmetric difference of two sets. Requires a set to write the result\nExample: set1 = %s set2 set3\n\n", operationsName[SYM_DIFFERENCE], operationsName[SYM_DIFFERENCE]);
  printf("%s - checks the inclusion of one set in another.\nExample: %s set2 set3 a\n\n", operationsName[CHECK_SUBSETS], operationsName[CHECK_SUBSETS]);
  printf("\n");
  printf("Other functions\n\n");
  printf("%s - write all set\'s names.\nExample: %s\n\n", operationsName[WRITE_SET_NAMES], operationsName[WRITE_SET_NAMES]);
  printf("%s - exit from program.\nExample: %s\n\n", operationsName[EXIT], operationsName[EXIT]);
  *error = ALL_OK;
  return listSet;
}