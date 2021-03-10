#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set.h"
#include "interface.h"
#pragma warning(disable: 4996)

//������� ���������� ��������� � ������
list_of_set_t* Create(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]) {
  list_of_set_t* newSet = NULL;
  list_of_set_t* curPointer = setsList;

  //�������� ������ ���������
  if ((newSet = malloc(sizeof(list_of_set_t))) == NULL) {
    *error = MEMORY_ERROR;
    return setsList;
  }
  newSet->card = 0;
  strcpy(newSet->name, name);
  newSet->set = NULL;
  
  //������ ����� � ������ ��������
  //�������� �� ���������� � ������ ������
  if (setsList == NULL || strcmp(curPointer->name, newSet->name) > 0) {
    newSet->next = setsList;
    setsList = newSet;
  }
  else {
    //����� �����
    while (curPointer->next != NULL && strcmp(curPointer->next->name, newSet->name) < 0) {
      curPointer = curPointer->next;
    }
    //�������� �� ��������� ���
    if ((curPointer->next != NULL && strcmp(curPointer->next->name, newSet->name) == 0) || (curPointer != NULL && strcmp(curPointer->name, newSet->name) == 0)) {
      *error = NAME_ERROR;
      return setsList;
    }
    //�������
    newSet->next = curPointer->next;
    curPointer->next = newSet;
  }

  *error = ALL_OK;
  return setsList;
}

//�������� ��������� �� �����
list_of_set_t* Delete(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]) {
  list_of_set_t* curPoiner = setsList;
  list_of_set_t* deletedSet;
  set_t* deletedElem;

  //�������� �� ������ ������
  if (setsList == NULL) {
    *error = SET_NOT_FOUND;
    return NULL;
  }
  //�������� �� ������
  if (strcmp(setsList->name, name) == 0) {
    deletedSet = setsList;
    //���������� ��������� ���������
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
  //����� ��������� � ������ �������
  while (curPoiner->next != NULL && strcmp(curPoiner->next->name, name) != 0) {
    curPoiner = curPoiner->next;
  }
  //�������� �� ���������� ��������� � ������
  if (curPoiner->next == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }
  //�������� ���������
  deletedSet = curPoiner->next;

  //���������� ��������� ���������
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

//�������� �������������� ��������
list_of_set_t* CheckElem(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME], const char elem[LENGTH_ELEM]) {
  list_of_set_t* setPointer = setsList;
  set_t* elemPointer;

  //����� ���������
  while (setPointer != NULL && strcmp(setPointer->name, name) != 0) {
    setPointer = setPointer->next;
  }
  //�������� �� ���������� ���������
  if (setPointer == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }

  //����� �������� � ������
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

//����������� �������� ���������
list_of_set_t* AddElem(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME], const char elem[LENGTH_ELEM]) {
  list_of_set_t* setPointer = setsList;
  set_t* elemPointer;
  set_t* newElem;

  //����� ���������
  while (setPointer != NULL && strcmp(setPointer->name, name) < 0) {
    setPointer = setPointer->next;
  }
  //�������� �� ���������� ���������
  if (setPointer == NULL) {
    return setsList;
  }
  
  //�������� ������ ��������
  if ((newElem = malloc(sizeof(char) * LENGTH_ELEM)) == NULL) {
    *error = MEMORY_ERROR;
    return setsList;
  }
  strcpy(newElem->elem, elem);

  //�������� �� ���������� � ������ ������
  if (setPointer->set == NULL || strcmp(setPointer->set->elem, elem) > 0) {
    newElem->next = setPointer->set;
    setPointer->set = newElem;
    setPointer->card += 1;
  }
  else {
    //����� �����
    elemPointer = setPointer->set;
    while (elemPointer->next != NULL && strcmp(elemPointer->next->elem, elem) < 0) {
      elemPointer = elemPointer->next;
    }
    //�������� �� ��������� ���
    if ((elemPointer->next != NULL && strcmp(elemPointer->next->elem, elem) == 0) || (elemPointer != NULL && strcmp(elemPointer->elem, elem) == 0)) {
      *error = ELEM_ERROR;
      return setsList;
    }
    //�������
    newElem->next = elemPointer->next;
    elemPointer->next = newElem;
    setPointer->card += 1;
  }

  WriteElems(setsList, error, name);

  return setsList;
}

//��������� �������� ���������
list_of_set_t* DeleteElem(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME], const char elem[LENGTH_ELEM]) {
  list_of_set_t* setPointer = setsList;
  set_t* elemPointer;
  set_t* deletedElem;

  //����� ���������
  while (setPointer != NULL && strcmp(setPointer->name, name) != 0) {
    setPointer = setPointer->next;
  }
  //�������� �� ���������� ���������
  if (setPointer == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }

  //�������� �� ������ ���������
  if (setPointer->set == NULL) {
    *error = ElEM_NOT_FOUND;
    return setsList;
  }
  //�������� �� ������
  if (setPointer->set != NULL && strcmp(setPointer->set->elem, elem) == 0) {
    deletedElem = setPointer->set;
    setPointer->set = setPointer->set->next;
    free(deletedElem);
    setPointer->card -= 1;
    WriteElems(setsList, error, name);
    return setsList;
  }
  else {
    //����� �������� � ������
    elemPointer = setPointer->set;
    while (elemPointer->next != NULL && strcmp(elemPointer->next->elem, elem) < 0) {
      elemPointer = elemPointer->next;
    }
    //�������� �� ���������� ������ ��������
    if (elemPointer->next == NULL) {
      *error = ElEM_NOT_FOUND;
      return setsList;
    }
    //�������� ��������
    deletedElem = elemPointer->next;
    elemPointer->next = deletedElem->next;
    setPointer->card -= 1;
    free(deletedElem);
  }

  WriteElems(setsList, error, name);

  return setsList;
}

//������� ������ ������ ��������
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

//������� ������ ��������� ���������
list_of_set_t* WriteElems(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]) {
  list_of_set_t* setPointer = setsList;
  set_t* elemPointer;

  //����� ���������
  while (setPointer != NULL && strcmp(setPointer->name, name) != 0) {
    setPointer = setPointer->next;
  }
  //�������� �� ���������� ���������
  if (setPointer == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }

  if (setPointer->set == NULL) {
    printf("Set is empty\n");
    return setsList;
  }
  //�����
  printf("%s = ", name);
  elemPointer = setPointer->set;
  while (elemPointer != NULL) {
    printf("\"%s\"; ", elemPointer->elem);
    elemPointer = elemPointer->next;
  }
  printf("\n");
  return setsList;
}

//������� ������ �������� ���������
list_of_set_t* WriteCard(list_of_set_t* setsList, error_t* error, const char name[LENGTH_NAME]) {
  list_of_set_t* setPointer = setsList;

  //����� ���������
  while (setPointer != NULL && strcmp(setPointer->name, name) != 0) {
    setPointer = setPointer->next;
  }
  //�������� �� ���������� ���������
  if (setPointer == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }

  printf("�ardinality of \"%s\" = %d\n", setPointer->name, setPointer->card);
  return setsList;
}

//���������� ������ ��������
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