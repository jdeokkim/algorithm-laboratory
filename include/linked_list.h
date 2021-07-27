/*
    Copyright (c) 2021 jdeokkim

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

#define LINKED_LIST_DEF static

/* 단일 연결 리스트를 나타내는 구조체. */
typedef struct LinkedList {
    int value;
    LinkedList *next;
} LinkedList;

/* 단일 연결 리스트를 생성한다. */
LINKED_LIST_DEF LinkedList *linked_list_create(void);

/* 단일 연결 리스트 `ll`에 할당된 메모리를 해제한다. */
LINKED_LIST_DEF void linked_list_release(LinkedList *ll);

/* 단일 연결 리스트 `ll`의 시작 부분에 값 `value`를 추가한다. */
LINKED_LIST_DEF void linked_list_push_front(LinkedList *ll, int value);

/* 단일 연결 리스트 `ll`의 끝 부분에 값 `value`를 추가한다. */
LINKED_LIST_DEF void linked_list_push_back(LinkedList *ll, int value);

/* 단일 연결 리스트 `ll`의 시작 부분의 값을 제거하고, 그 값을 반환한다. */
LINKED_LIST_DEF int linked_list_pop_front(LinkedList *ll);

/* 단일 연결 리스트 `ll`의 끝 부분의 값을 제거하고, 그 값을 반환한다. */
LINKED_LIST_DEF int linked_list_pop_back(LinkedList *ll);

/* 단일 연결 리스트 `ll`의 시작 부분의 값을 반환한다. */
LINKED_LIST_DEF int linked_list_peek_front(LinkedList *ll);

/* 단일 연결 리스트 `ll`의 끝 부분의 값을 반환한다. */
LINKED_LIST_DEF int linked_list_peek_back(LinkedList *ll);

#endif // `LINKED_LIST_H`

#ifdef LINKED_LIST_IMPLEMENTATION

/* TODO: ... */

#endif // `LINKED_LIST_IMPLEMENTATION`