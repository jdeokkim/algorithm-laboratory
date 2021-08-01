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
typedef struct SinglyLinkedList {
    int value;
    struct SinglyLinkedList *next;
} SinglyLinkedList;

/* 단일 연결 리스트를 생성한다. */
LINKED_LIST_DEF SinglyLinkedList *sll_create(int value);

/* 단일 연결 리스트 `ll`에 할당된 메모리를 해제한다. */
LINKED_LIST_DEF void sll_release(SinglyLinkedList *ll);

/* 단일 연결 리스트 `ll`와 연결된 모든 값을 제거한다. */
LINKED_LIST_DEF void sll_clear(SinglyLinkedList *ll);

/* 단일 연결 리스트 `ll`의 시작 부분을 반환한다. */
LINKED_LIST_DEF SinglyLinkedList *sll_front(SinglyLinkedList *ll);

/* 단일 연결 리스트 `ll`의 끝 부분을 반환한다. */
LINKED_LIST_DEF SinglyLinkedList *sll_back(SinglyLinkedList *ll);

/* 단일 연결 리스트 `ll`의 시작 부분에 값 `value`를 추가한다. */
LINKED_LIST_DEF void sll_push_front(SinglyLinkedList **ll, int value);

/* 단일 연결 리스트 `ll`의 끝 부분에 값 `value`를 추가한다. */
LINKED_LIST_DEF void sll_push_back(SinglyLinkedList **ll, int value);

/* 단일 연결 리스트 `ll`의 시작 부분의 값을 제거하고, 그 값을 반환한다. */
LINKED_LIST_DEF int sll_pop_front(SinglyLinkedList **ll);

/* 단일 연결 리스트 `ll`의 끝 부분의 값을 제거하고, 그 값을 반환한다. */
LINKED_LIST_DEF int sll_pop_back(SinglyLinkedList **ll);

#endif // `LINKED_LIST_H`

#ifdef LINKED_LIST_IMPLEMENTATION

/* 단일 연결 리스트를 생성한다. */
LINKED_LIST_DEF SinglyLinkedList *sll_create(int value) {
    SinglyLinkedList *result = calloc(1, sizeof(SinglyLinkedList));
    
    result->value = value;
    
    return result;
}

/* 단일 연결 리스트 `ll`에 할당된 메모리를 해제한다. */
LINKED_LIST_DEF void sll_release(SinglyLinkedList *ll) {
    sll_clear(ll);
    free(ll);
}

/* 단일 연결 리스트 `ll`와 연결된 모든 값을 제거한다. */
LINKED_LIST_DEF void sll_clear(SinglyLinkedList *ll) {
    if (ll != NULL && ll->next != NULL) {
        sll_release(ll->next);
        ll->next = NULL;
    }
}

/* 단일 연결 리스트 `ll`의 시작 부분을 반환한다. */
LINKED_LIST_DEF SinglyLinkedList *sll_front(SinglyLinkedList *ll) {
    return ll;
}

/* 단일 연결 리스트 `ll`의 끝 부분을 반환한다. */
LINKED_LIST_DEF SinglyLinkedList *sll_back(SinglyLinkedList *ll) {
    SinglyLinkedList *ptr = ll;
    
    while (ptr->next != NULL) 
        ptr = ptr->next;
    
    return ptr;
}

/* 단일 연결 리스트 `ll`의 시작 부분에 값 `value`를 추가한다. */
LINKED_LIST_DEF void sll_push_front(SinglyLinkedList **ll, int value) {
    if (ll == NULL || *ll == NULL) return;
    
    SinglyLinkedList *front = sll_create(value);
    front->next = *ll;
    
    *ll = front;
}

/* 단일 연결 리스트 `ll`의 끝 부분에 값 `value`를 추가한다. */
LINKED_LIST_DEF void sll_push_back(SinglyLinkedList **ll, int value) {
    if (ll == NULL || *ll == NULL) return;
    
    SinglyLinkedList *back = sll_back(*ll);
    
    back->next = sll_create(value);
}

/* 단일 연결 리스트 `ll`의 시작 부분의 값을 제거하고, 그 값을 반환한다. */
LINKED_LIST_DEF int sll_pop_front(SinglyLinkedList **ll) {
    if (ll == NULL || *ll == NULL) return -1;
    
    SinglyLinkedList *ptr = (*ll)->next;
    
    int result = (*ll)->value;
    
    (*ll)->next = NULL;
    sll_release(*ll);
    
    *ll = ptr;
}

/* 단일 연결 리스트 `ll`의 끝 부분의 값을 제거하고, 그 값을 반환한다. */
LINKED_LIST_DEF int sll_pop_back(SinglyLinkedList **ll) {
    if (ll == NULL || *ll == NULL) return -1;
    
    SinglyLinkedList *ptr = *ll;
    
    if (ptr->next == NULL) {
        int result = ptr->value;
        
        sll_release(*ll);
        *ll = NULL;
        
        return result;
    } else {
        while (ptr->next != NULL && ptr->next->next != NULL)
            ptr = ptr->next;
        
        int result = ptr->next->value;
        
        sll_release(ptr->next);
        ptr->next = NULL;
        
        return result;
    }
}

#endif // `LINKED_LIST_IMPLEMENTATION`