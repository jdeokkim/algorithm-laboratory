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

/* 단일 연결 리스트의 항목을 나타내는 구조체. */
typedef struct SinglyLinkedNode {
    int value;
    struct SinglyLinkedNode *next;
} SinglyLinkedNode;

/* 단일 연결 리스트를 나타내는 구조체. */
typedef struct SinglyLinkedList {
    SinglyLinkedNode *front;
    SinglyLinkedNode *back;
} SinglyLinkedList;

/* 단일 연결 리스트를 생성한다. */
LINKED_LIST_DEF SinglyLinkedList *sll_create(void);

/* 단일 연결 리스트 `ll`에 할당된 메모리를 해제한다. */
LINKED_LIST_DEF void sll_release(SinglyLinkedList *ll);

/* 단일 연결 리스트 `ll`의 모든 항목을 제거한다. */
LINKED_LIST_DEF void sll_clear(SinglyLinkedList *ll);

/* 단일 연결 리스트 `ll`의 시작 부분을 반환한다. */
LINKED_LIST_DEF SinglyLinkedNode *sll_front(SinglyLinkedList *ll);

/* 단일 연결 리스트 `ll`의 끝 부분을 반환한다. */
LINKED_LIST_DEF SinglyLinkedNode *sll_back(SinglyLinkedList *ll);

/* 단일 연결 리스트 `ll`의 시작 부분에 새로운 항목을 추가한다. */
LINKED_LIST_DEF void sll_push_front(SinglyLinkedList *ll, int value);

/* 단일 연결 리스트 `ll`의 끝 부분에 새로운 항목을 추가한다. */
LINKED_LIST_DEF void sll_push_back(SinglyLinkedList *ll, int value);

/* 단일 연결 리스트 `ll`의 시작 부분의 항목을 제거하고, 그 항목의 값을 반환한다. */
LINKED_LIST_DEF int sll_pop_front(SinglyLinkedList *ll);

/* 단일 연결 리스트 `ll`의 끝 부분의 항목을 제거하고, 그 항목의 값을 반환한다. */
LINKED_LIST_DEF int sll_pop_back(SinglyLinkedList *ll);

#endif // `LINKED_LIST_H`

#ifdef LINKED_LIST_IMPLEMENTATION

/* 단일 연결 리스트를 생성한다. */
LINKED_LIST_DEF SinglyLinkedList *sll_create(void) {
    return calloc(1, sizeof(SinglyLinkedList));
}

/* 단일 연결 리스트 `ll`에 할당된 메모리를 해제한다. */
LINKED_LIST_DEF void sll_release(SinglyLinkedList *ll) {
    sll_clear(ll);
    
    free(ll);
}

/* 단일 연결 리스트의 항목 `node`에 할당된 메모리를 해제한다. */
LINKED_LIST_DEF void _sll_node_release(SinglyLinkedNode *node) {
    free(node);
}

/* 단일 연결 리스트의 항목 `node`와 연결된 모든 항목을 제거한다. */
LINKED_LIST_DEF void _sll_node_clear(SinglyLinkedNode *node) {
    if (node == NULL || node->next == NULL) return;
    
    _sll_node_clear(node->next);
    _sll_node_release(node->next);
    
    node->next = NULL;
}

/* 단일 연결 리스트 `ll`의 모든 항목을 제거한다. */
LINKED_LIST_DEF void sll_clear(SinglyLinkedList *ll) {
    if (ll == NULL) return;
    
    _sll_node_clear(ll->front);
    _sll_node_release(ll->front);
    
    ll->front = ll->back = NULL;
}

/* 단일 연결 리스트 `ll`의 시작 부분을 반환한다. */
LINKED_LIST_DEF SinglyLinkedNode *sll_front(SinglyLinkedList *ll) {
    return ll->front;
}

/* 단일 연결 리스트 `ll`의 끝 부분을 반환한다. */
LINKED_LIST_DEF SinglyLinkedNode *sll_back(SinglyLinkedList *ll) {
    return ll->back;
}

/* 단일 연결 리스트를 생성한다. */
LINKED_LIST_DEF SinglyLinkedNode *_sll_node_create(int value) {
    SinglyLinkedNode *result = calloc(1, sizeof(SinglyLinkedNode));
    
    result->value = value;
    
    return result;
}

/* 단일 연결 리스트 `ll`의 시작 부분에 새로운 항목을 추가한다. */
LINKED_LIST_DEF void sll_push_front(SinglyLinkedList *ll, int value) {
    if (ll->front == NULL && ll->back == NULL) {
        ll->front = ll->back = _sll_node_create(value);
    } else {
        SinglyLinkedNode *front = _sll_node_create(value);
        
        front->next = ll->front;
        
        ll->front = front;
    }
}

/* 단일 연결 리스트 `ll`의 끝 부분에 새로운 항목을 추가한다. */
LINKED_LIST_DEF void sll_push_back(SinglyLinkedList *ll, int value) {
    if (ll->front == NULL && ll->back == NULL) {
        sll_push_front(ll, value);
    } else {
        SinglyLinkedNode *back = _sll_node_create(value);
        
        ll->back->next = back;
        ll->back = back;
    }
}

/* 단일 연결 리스트 `ll`의 시작 부분의 항목을 제거하고, 그 항목의 값을 반환한다. */
LINKED_LIST_DEF int sll_pop_front(SinglyLinkedList *ll) {
    if (ll == NULL || ll->front == NULL) return -1;
    
    SinglyLinkedNode *front = ll->front;
    
    int result = front->value;
    
    _sll_node_release(ll->front);
    
    if (front->next == NULL) ll->front = ll->back = NULL;
    else ll->front = front->next;
    
    return result;
}

/* 단일 연결 리스트 `ll`의 끝 부분의 항목을 제거하고, 그 항목의 값을 반환한다. */
LINKED_LIST_DEF int sll_pop_back(SinglyLinkedList *ll) {
    if (ll == NULL || ll->back == NULL) return -1;
    
    SinglyLinkedNode *front = ll->front;
    
    if (front->next == NULL) {
        int result = front->value;
        
        _sll_node_release(front);
        
        ll->front = ll->back = NULL;
        
        return result;
    } else {
        while (front->next != NULL && front->next->next != NULL)
            front = front->next;
        
        int result = front->next->value;
        
        _sll_node_release(front->next);
        
        front->next = NULL;
        
        return result;
    }
}

#endif // `LINKED_LIST_IMPLEMENTATION`