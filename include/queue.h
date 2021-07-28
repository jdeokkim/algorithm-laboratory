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

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_DEF static

/* 큐를 나타내는 구조체. */
typedef struct Queue {
    int length;
    int capacity;
    int *ptr;
} Queue;

/* 큐를 생성한다. */
QUEUE_DEF Queue *queue_create(void);

/* 큐 `queue`에 할당된 메모리를 해제한다. */
QUEUE_DEF void queue_release(Queue *queue);

/* 큐 `queue`에 들어 있는 모든 값을 제거한다. */
QUEUE_DEF void queue_clear(Queue *queue);

/* 큐 `queue`에 들어 있는 값의 개수를 반환한다. */
QUEUE_DEF int queue_size(Queue *queue);

/* 큐 `queue`이 비어 있는지 확인한다. */
QUEUE_DEF bool queue_is_empty(Queue *queue);

/* 큐 `queue`에 값 `value`를 추가한다. */
QUEUE_DEF void queue_push(Queue *queue, int value);

/* 큐 `queue`에서 가장 처음에 추가된 값을 제거하고, 그 값을 반환한다. */
QUEUE_DEF int queue_pop(Queue *queue);

/* 큐 `queue`에서 가장 처음에 추가된 값을 반환한다.*/
QUEUE_DEF int queue_front(Queue *queue);

/* 큐 `queue`에서 가장 마지막에 추가된 값을 반환한다. */
QUEUE_DEF int queue_back(Queue *queue);

#endif // `QUEUE_H`

#ifdef QUEUE_IMPLEMENTATION

/* 큐를 생성한다. */
QUEUE_DEF Queue *queue_create(void) {
    Queue *result = calloc(1, sizeof(Queue));
    
    result->capacity = 8;
    result->ptr = calloc(result->capacity, sizeof(int));
    
    return result;
}

/* 큐 `queue`에 할당된 메모리를 해제한다. */
QUEUE_DEF void queue_release(Queue *queue) {
    free(queue);
}

/* 큐 `queue`에 들어 있는 모든 값을 제거한다. */
QUEUE_DEF void queue_clear(Queue *queue) {
    if (queue != NULL) queue->length = 0;
}

/* 큐 `queue`에 들어 있는 값의 개수를 반환한다. */
QUEUE_DEF int queue_size(Queue *queue) {
    return (queue != NULL) ? queue->length : -1;
}

/* 큐 `queue`이 비어 있는지 확인한다. */
QUEUE_DEF bool queue_is_empty(Queue *queue) {
    return (queue != NULL && queue->length <= 0);
}

/* 큐 `queue`에 값 `value`를 추가한다. */
QUEUE_DEF void queue_push(Queue *queue, int value) {
    if (queue == NULL) return;
    
    if (queue->length >= queue->capacity) {
        queue->capacity *= 2;
        queue->ptr = realloc(queue->ptr, 2 * queue->capacity * sizeof(int));
    }
    
    queue->ptr[queue->length++] = value;
}

/* 큐 `queue`에서 가장 처음에 추가된 값을 제거하고, 그 값을 반환한다. */
QUEUE_DEF int queue_pop(Queue *queue) {
    if (queue == NULL || queue->length <= 0) return -1;
    
    int result = queue->ptr[0];
    
    memmove(&queue->ptr[0], &queue->ptr[1], (--queue->length) * sizeof(int));
    
    return result;
}

/* 큐 `queue`에서 가장 처음에 추가된 값을 반환한다.*/
QUEUE_DEF int queue_front(Queue *queue) {
    return (queue != NULL && queue->length > 0) ? queue->ptr[0] : -1;
}

/* 큐 `queue`에서 가장 마지막에 추가된 값을 반환한다. */
QUEUE_DEF int queue_back(Queue *queue) {
    return (queue != NULL && queue->length > 0) ? queue->ptr[queue->length - 1] : -1;
}

#endif // `QUEUE_IMPLEMENTATION`