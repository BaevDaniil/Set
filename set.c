#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set.h"
#include "interface.h"
#pragma warning(disable: 4996)

//Функция добавления множества в список
list_of_set_t* Create(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]) {
  list_of_set_t* newSet = NULL;
  list_of_set_t* curPointer = setsList;

  //Создание нового множества
  if ((newSet = malloc(sizeof(list_of_set_t))) == NULL) {
    *error = MEMORY_ERROR;
    return setsList;
  }
  newSet->card = 0;
  strcpy(newSet->name, name);
  newSet->set = NULL;
  
  //Подбор места в списке множеств
  //Проверка на добавление в начало списка
  if (setsList == NULL || strcmp(curPointer->name, newSet->name) > 0) {
    newSet->next = setsList;
    setsList = newSet;
  }
  else {
    //Поиск места
    while (curPointer->next != NULL && strcmp(curPointer->next->name, newSet->name) < 0) {
      curPointer = curPointer->next;
    }
    //Проверка на равенство имён
    if ((curPointer->next != NULL && strcmp(curPointer->next->name, newSet->name) == 0) || (curPointer != NULL && strcmp(curPointer->name, newSet->name) == 0)) {
      *error = NAME_ERROR;
      return setsList;
    }
    //Вставка
    newSet->next = curPointer->next;
    curPointer->next = newSet;
  }

  *error = ALL_OK;
  return setsList;
}

//Удаление множества по имени
list_of_set_t* Delete(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]) {
  list_of_set_t* curPoiner = setsList;
  list_of_set_t* deletedSet;
  set_t* deletedElem;

  //Проверка на пустой список
  if (setsList == NULL) {
    *error = SET_NOT_FOUND;
    return NULL;
  }
  //Удаление из начала
  if (strcmp(setsList->name, name) == 0) {
    deletedSet = setsList;
    //Деструктор элементов множества
    deletedElem = deletedSet->set;
    while (deletedElem != NULL) {
      deletedSet->set = deletedElem->next;
      free(deletedElem);
      deletedElem = deletedSet->set;
    }
    setsList = setsList->next;
    free(deletedSet);
    *error = ALL_OK;
    return setsList;
  }
  //Поиск множества в списке поимени
  while (curPoiner->next != NULL && strcmp(curPoiner->next->name, name) != 0) {
    curPoiner = curPoiner->next;
  }
  //Проверка на отсутствие множества в списке
  if (curPoiner->next == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }
  //Удаление множества
  deletedSet = curPoiner->next;

  //Деструктор элементов множества
  deletedElem = deletedSet->set;
  while (deletedElem != NULL) {
    deletedSet->set = deletedElem->next;
    free(deletedElem);
    deletedElem = deletedSet->set;
  }

  curPoiner->next = deletedSet->next;
  free(deletedSet);

  *error = ALL_OK;
  return setsList;
}

//Проверка принадлежности элемента
list_of_set_t* CheckElem(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME], const char elem[LENGTH_ELEM]) {
  list_of_set_t* setPointer = setsList;
  set_t* elemPointer;

  //Поиск множества
  while (setPointer != NULL && strcmp(setPointer->name, name) != 0) {
    setPointer = setPointer->next;
  }
  //Проверка на отсутствие множества
  if (setPointer == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }

  //Поиск элемента в списке
  elemPointer = setPointer->set;
  while (elemPointer != NULL && strcmp(elemPointer->elem, elem) != 0) {
    elemPointer = elemPointer->next;
  }
  if (elemPointer == NULL) {
    printf("\"%s\" is not belonging \"%s\"\n", elem, name);
  }
  else {
    printf("\"%s\" is belonging \"%s\"\n", elem, name);
  }

  return setsList;
}

//Конструктор элемента множества
list_of_set_t* AddElem(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME], const char elem[LENGTH_ELEM]) {
  list_of_set_t* setPointer = setsList;
  set_t* elemPointer;
  set_t* newElem;

  //Поиск множества
  while (setPointer != NULL && strcmp(setPointer->name, name) < 0) {
    setPointer = setPointer->next;
  }
  //Проверка на отсутствие множества
  if (setPointer == NULL) {
    return setsList;
  }
  
  //Создание нового элемента
  if ((newElem = malloc(sizeof(char) * LENGTH_ELEM)) == NULL) {
    *error = MEMORY_ERROR;
    return setsList;
  }
  strcpy(newElem->elem, elem);

  //Проверка на добавление в начало списка
  if (setPointer->set == NULL || strcmp(setPointer->set->elem, elem) > 0) {
    newElem->next = setPointer->set;
    setPointer->set = newElem;
    setPointer->card += 1;
  }
  else {
    //Поиск места
    elemPointer = setPointer->set;
    while (elemPointer->next != NULL && strcmp(elemPointer->next->elem, elem) < 0) {
      elemPointer = elemPointer->next;
    }
    //Проверка на равенство имён
    if ((elemPointer->next != NULL && strcmp(elemPointer->next->elem, elem) == 0) || (elemPointer != NULL && strcmp(elemPointer->elem, elem) == 0)) {
      *error = ELEM_ERROR;
      return setsList;
    }
    //Вставка
    newElem->next = elemPointer->next;
    elemPointer->next = newElem;
    setPointer->card += 1;
  }

  WriteElems(setsList, error, name);

  return setsList;
}

//Удаленеие элемента множества
list_of_set_t* DeleteElem(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME], const char elem[LENGTH_ELEM]) {
  list_of_set_t* setPointer = setsList;
  set_t* elemPointer;
  set_t* deletedElem;

  //Поиск множества
  while (setPointer != NULL && strcmp(setPointer->name, name) != 0) {
    setPointer = setPointer->next;
  }
  //Проверка на отсутствие множества
  if (setPointer == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }

  //Проверка на пустое множество
  if (setPointer->set == NULL) {
    *error = ElEM_NOT_FOUND;
    return setsList;
  }
  //Удаление из начала
  if (setPointer->set != NULL && strcmp(setPointer->set->elem, elem) == 0) {
    deletedElem = setPointer->set;
    setPointer->set = setPointer->set->next;
    free(deletedElem);
    setPointer->card -= 1;
    WriteElems(setsList, error, name);
    return setsList;
  }
  else {
    //Поиск элемента в списке
    elemPointer = setPointer->set;
    while (elemPointer->next != NULL && strcmp(elemPointer->next->elem, elem) < 0) {
      elemPointer = elemPointer->next;
    }
    //Проверка на отсутствие такого элемента
    if (elemPointer->next == NULL) {
      *error = ElEM_NOT_FOUND;
      return setsList;
    }
    //Удаление элемента
    deletedElem = elemPointer->next;
    elemPointer->next = deletedElem->next;
    setPointer->card -= 1;
    free(deletedElem);
  }

  WriteElems(setsList, error, name);

  return setsList;
}

//Функция вывода списка множеств
list_of_set_t* WriteSetNames(list_of_set_t* setsList, error_t* error) {
  list_of_set_t* curPointer = setsList;

  if (setsList == NULL) {
    printf("List of sets is empty");
  }
  while (curPointer) {
    printf("\"%s\"; ", curPointer->name);
    curPointer = curPointer->next;
  }
  printf("\n");
  *error = ALL_OK;
  return setsList;
}

//Функция вывода элементов множества
list_of_set_t* WriteElems(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]) {
  list_of_set_t* setPointer = setsList;
  set_t* elemPointer;

  //Поиск множества
  while (setPointer != NULL && strcmp(setPointer->name, name) != 0) {
    setPointer = setPointer->next;
  }
  //Проверка на отсутствие множества
  if (setPointer == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }

  if (setPointer->set == NULL) {
    printf("Set is empty\n");
    return setsList;
  }
  //Вывод
  printf("%s = ", name);
  elemPointer = setPointer->set;
  while (elemPointer != NULL) {
    printf("\"%s\"; ", elemPointer->elem);
    elemPointer = elemPointer->next;
  }
  printf("\n");
  return setsList;
}

//Функция вывода мощности множества
list_of_set_t* WriteCard(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]) {
  list_of_set_t* setPointer = setsList;

  //Поиск множества
  while (setPointer != NULL && strcmp(setPointer->name, name) != 0) {
    setPointer = setPointer->next;
  }
  //Проверка на отсутствие множества
  if (setPointer == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }

  printf("Сardinality of \"%s\" = %d\n", setPointer->name, setPointer->card);
  return setsList;
}

//Деструктор списка сножеств
void DeleteAll(list_of_set_t* setsList) {
  list_of_set_t* deletedSet = setsList;
  set_t* deletedElem;

  while (deletedSet != NULL) {
    deletedElem = deletedSet->set;
    while (deletedElem != NULL) {
      deletedSet->set = deletedElem->next;
      free(deletedElem);
      deletedElem = deletedSet->set;
    }
    setsList = setsList->next;
    free(deletedSet);
    deletedSet = setsList;
  }
}