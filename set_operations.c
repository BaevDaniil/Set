#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set.h"
#include "interface.h"
#pragma warning(disable: 4996)

//������ ����������� ��������� ������ ��� ������ ��������
#define CREATE(newElem) if ((newElem = malloc(sizeof(set_t))) == NULL) {*error = MEMORY_ERROR; return setsList;}

//������� ������ ���������
list_of_set_t* FindSet(const char name[LENGTH_NAME], list_of_set_t* setsList) {
  list_of_set_t* set = setsList;
  while (set != NULL && strcmp(set->name, name) != 0) {
    set = set->next;
  }
  return set;
}

list_of_set_t* Union(list_of_set_t* setsList, error_t* error, const char nameResult[LENGTH_NAME], const char nameArg1[LENGTH_NAME], const char nameArg2[LENGTH_NAME]) {
  list_of_set_t* arg1 = FindSet(nameArg1, setsList);
  list_of_set_t* arg2 = FindSet(nameArg2, setsList);
  list_of_set_t* result = FindSet(nameResult, setsList);
  set_t* elemSet1;
  set_t* elemSet2;
  set_t* elemResult;
  set_t* newElem;
  set_t* elem = NULL;

  //�������� �� ���������� ������ �� ���������
  if (arg1 == NULL || arg2 == NULL || result == NULL) {
  *error = SET_NOT_FOUND;
    return setsList;
  }
  if (arg1 == result || arg2 == result) {
    *error = NAME_ERROR;
    return setsList;
  }

  elemResult = result->set;
  //������� ��������������� ���������
  while (elemResult != NULL) {
    result->set = elemResult->next;
    free(elemResult);
    elemResult = result->set;
  }
  result->card = 0;

  elemSet1 = arg1->set;
  elemSet2 = arg2->set;
  elemResult = result->set;
  while (elemSet1 != NULL && elemSet2 != NULL) {
    if (strcmp(elemSet1->elem, elemSet2->elem) < 0) {
      //���������� �������� �� set1
      CREATE(newElem);
      strcpy(newElem->elem, elemSet1->elem);
      elemSet1 = elemSet1->next;
    }
    else if (strcmp(elemSet1->elem, elemSet2->elem) > 0){
      //���������� �������� �� set2
      CREATE(newElem);
      strcpy(newElem->elem, elemSet2->elem);
      elemSet2 = elemSet2->next;
    }
    else {
      //���������� ���������� ��������
      CREATE(newElem);
      strcpy(newElem->elem, elemSet1->elem);
      elemSet1 = elemSet1->next;
      elemSet2 = elemSet2->next;
    }
    //���������� �������� � �������������� ���������
    if (result->set != NULL) {
      elemResult->next = newElem;
      elemResult = elemResult->next;
      result->card++;
    }
    else {
      result->set = newElem;
      elemResult = newElem;
      result->card++;
    }
  }

  //���������� ���������� ���������
  if (elemSet1 == NULL && elemSet2 != NULL) {
    elem = elemSet2;
  }
  else if (elemSet1 != NULL && elemSet2 == NULL) {
    elem = elemSet1;
  }
  while (elem != NULL) {
    CREATE(newElem);
    strcpy(newElem->elem, elem->elem);
    elem = elem->next;
    if (result->set != NULL) {
      elemResult->next = newElem;
      elemResult = elemResult->next;
      result->card++;
    }
    else {
      result->set = newElem;
      elemResult = newElem;
      result->card++;
    }
  }
  
  if (elemResult != NULL) {
    elemResult->next = NULL;
  }
  WriteElems(setsList, error, result->name);
  return setsList;
}

list_of_set_t* Intersection(list_of_set_t* setsList, error_t* error, const char nameResult[LENGTH_NAME], const char nameArg1[LENGTH_NAME], const char nameArg2[LENGTH_NAME]) {
  list_of_set_t* arg1 = FindSet(nameArg1, setsList);
  list_of_set_t* arg2 = FindSet(nameArg2, setsList);
  list_of_set_t* result = FindSet(nameResult, setsList);
  set_t* elemSet1;
  set_t* elemSet2;
  set_t* elemResult;
  set_t* newElem;

  //�������� �� ���������� ������ �� ���������
  if (arg1 == NULL || arg2 == NULL || result == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }
  if (arg1 == result || arg2 == result) {
    *error = NAME_ERROR;
    return setsList;
  }

  elemResult = result->set;
  //������� ��������������� ���������
  while (elemResult != NULL) {
    result->set = elemResult->next;
    free(elemResult);
    elemResult = result->set;
    result->card++;
  }
  result->card = 0;

  elemSet1 = arg1->set;
  elemSet2 = arg2->set;
  elemResult = result->set;
  while (elemSet1 != NULL && elemSet2 != NULL) {
    if (strcmp(elemSet1->elem, elemSet2->elem) < 0) {
      elemSet1 = elemSet1->next;
    }
    else if (strcmp(elemSet1->elem, elemSet2->elem) > 0) {
      elemSet2 = elemSet2->next;
    }
    else {
      CREATE(newElem);
      strcpy(newElem->elem, elemSet1->elem);
      elemSet1 = elemSet1->next;
      elemSet2 = elemSet2->next;
      //���������� �������� � �������������� ���������
      if (result->set != NULL) {
      	elemResult->next = newElem;
      	elemResult = elemResult->next;
      	result->card++;
      }
      else {
        result->set = newElem;
        elemResult = newElem;
        result->card++;
      }
    }
  }

  if (elemResult != NULL) {
    elemResult->next = NULL;
  }
  WriteElems(setsList, error, result->name);
  return setsList;
}

list_of_set_t* Difference(list_of_set_t* setsList, error_t* error, const char nameResult[LENGTH_NAME], const char nameArg1[LENGTH_NAME], const char nameArg2[LENGTH_NAME]) {
  list_of_set_t* arg1 = FindSet(nameArg1, setsList);
  list_of_set_t* arg2 = FindSet(nameArg2, setsList);
  list_of_set_t* result = FindSet(nameResult, setsList);
  set_t* elemSet1;
  set_t* elemSet2;
  set_t* elemResult;
  set_t* newElem;

  //�������� �� ���������� ������ �� ���������
  if (arg1 == NULL || arg2 == NULL || result == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }
  if (arg1 == result || arg2 == result) {
    *error = NAME_ERROR;
    return setsList;
  }

  elemResult = result->set;
  //������� ��������������� ���������
  while (elemResult != NULL) {
    result->set = elemResult->next;
    free(elemResult);
    elemResult = result->set;
  }
  result->card = 0;

  elemSet1 = arg1->set;
  elemSet2 = arg2->set;
  elemResult = result->set;
  while (elemSet1 != NULL && elemSet2 != NULL) {
    if (strcmp(elemSet1->elem, elemSet2->elem) < 0) {
      CREATE(newElem);
      strcpy(newElem->elem, elemSet1->elem);
      elemSet1 = elemSet1->next;
      //���������� �������� � �������������� ���������
      if (result->set != NULL) {
        elemResult->next = newElem;
        elemResult = elemResult->next;
        result->card++;
      }
      else {
        result->set = newElem;
        elemResult = newElem;
        result->card++;
      }
    }
    else if (strcmp(elemSet1->elem, elemSet2->elem) > 0) {
      elemSet2 = elemSet2->next;
    }
    else {
      elemSet1 = elemSet1->next;
      elemSet2 = elemSet2->next;
    }
  }

  //���������� ���������� ���������
  if (elemSet1 != NULL) {
    while (elemSet1 != NULL) {
      CREATE(newElem);
      strcpy(newElem->elem, elemSet1->elem);
      elemSet1 = elemSet1->next;
      if (result->set != NULL) {
        elemResult->next = newElem;
        elemResult = elemResult->next;
        result->card++;
      }
      else {
        result->set = newElem;
        elemResult = newElem;
        result->card++;
      }
    }
  }

  if (elemResult != NULL) {
    elemResult->next = NULL;
  }
  WriteElems(setsList, error, result->name);
  return setsList;
}

list_of_set_t* SymmetricDifference(list_of_set_t* setsList, error_t* error, const char nameResult[LENGTH_NAME], const char nameArg1[LENGTH_NAME], const char nameArg2[LENGTH_NAME]) {
  list_of_set_t* arg1 = FindSet(nameArg1, setsList);
  list_of_set_t* arg2 = FindSet(nameArg2, setsList);
  list_of_set_t* result = FindSet(nameResult, setsList);
  set_t* elemSet1;
  set_t* elemSet2;
  set_t* elemResult;
  set_t* newElem;
  set_t* elem = NULL;

  //�������� �� ���������� ������ �� ���������
  if (arg1 == NULL || arg2 == NULL || result == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }
  if (arg1 == result || arg2 == result) {
    *error = NAME_ERROR;
    return setsList;
  }

  elemResult = result->set;
  //������� ��������������� ���������
  while (elemResult != NULL) {
    result->set = elemResult->next;
    free(elemResult);
    elemResult = result->set;
  }
  result->card = 0;

  elemSet1 = arg1->set;
  elemSet2 = arg2->set;
  elemResult = result->set;
  while (elemSet1 != NULL && elemSet2 != NULL) {
    if (strcmp(elemSet1->elem, elemSet2->elem) < 0) {
      //���������� �������� �� set1
      CREATE(newElem);
      strcpy(newElem->elem, elemSet1->elem);
      elemSet1 = elemSet1->next;
    }
    else if (strcmp(elemSet1->elem, elemSet2->elem) > 0) {
      //���������� �������� �� set2
      CREATE(newElem);
      strcpy(newElem->elem, elemSet2->elem);
      elemSet2 = elemSet2->next;
    }
    else {
      newElem = NULL;
      elemSet1 = elemSet1->next;
      elemSet2 = elemSet2->next;
    }
    //���������� �������� � �������������� ���������
    if (result->set != NULL && newElem != NULL) {
      elemResult->next = newElem;
      elemResult = elemResult->next;
      result->card++;
    }
    else if (newElem != NULL) {
      result->set = newElem;
      elemResult = newElem;
      result->card++;
    }
  }

  //���������� ���������� ���������
  if (elemSet1 == NULL && elemSet2 != NULL) {
    elem = elemSet2;
  }
  else if (elemSet1 != NULL && elemSet2 == NULL) {
    elem = elemSet1;
  }
  while (elem != NULL) {
    CREATE(newElem);
    strcpy(newElem->elem, elem->elem);
    elem = elem->next;
    if (result->set != NULL) {
      elemResult->next = newElem;
      elemResult = elemResult->next;
      result->card++;
    }
    else {
      result->set = newElem;
      elemResult = newElem;
      result->card++;
    }
  }

  if (elemResult != NULL) {
    elemResult->next = NULL;
  }
  WriteElems(setsList, error, result->name);
  return setsList;
}

//������� �������� ��������� (����� �� ������ ���������� �������� ��� ������������)
//nameResult �� ������������
list_of_set_t* CheckSubsets(list_of_set_t* setsList, error_t* error, const char nameArg1[LENGTH_NAME], const char nameArg2[LENGTH_NAME]) {
  list_of_set_t* arg1 = FindSet(nameArg1, setsList);
  list_of_set_t* arg2 = FindSet(nameArg2, setsList);
  set_t* elemSet1;
  set_t* elemSet2;

  //�������� �� ���������� ������ �� ���������
  if (arg1 == NULL || arg2 == NULL) {
    *error = SET_NOT_FOUND;
    return setsList;
  }

  elemSet1 = arg1->set;
  elemSet2 = arg2->set;
  while (elemSet1 != NULL && elemSet2 != NULL) {
    if (strcmp(elemSet1->elem, elemSet2->elem) < 0) {
      printf("\"%s\" is not subsets of \"%s\"\n", nameArg1, nameArg2);
      return setsList;
    }
    else if (strcmp(elemSet1->elem, elemSet2->elem) > 0) {
      elemSet2 = elemSet2->next;
    }
    else {
      elemSet1 = elemSet1->next;
      elemSet2 = elemSet2->next;
    }
  }

  if (elemSet1 == NULL) {
    printf("\"%s\" is subsets of \"%s\"\n", nameArg1, nameArg2);
  }
  else {
    printf("\"%s\" is not subsets of \"%s\"\n", nameArg1, nameArg2);
  }
  return setsList;
}