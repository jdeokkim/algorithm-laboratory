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

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BINARY_HEAP_DEF static

/* 이진 힙을 나타내는 구조체. */
typedef struct BinaryHeap {
    int length;
    int capacity;
    unsigned int *ptr;
} BinaryHeap;

/* 이진 힙을 생성한다. */
BINARY_HEAP_DEF BinaryHeap *binary_heap_create(void);

/* 이진 힙 `heap`에 할당된 메모리를 해제한다. */
BINARY_HEAP_DEF void binary_heap_release(BinaryHeap *heap);

/* 이진 힙 `heap`에 들어 있는 모든 값을 제거한다. */
BINARY_HEAP_DEF void binary_heap_clear(BinaryHeap *heap);

/* 이진 힙 `heap`에 들어 있는 값의 개수를 반환한다. */
BINARY_HEAP_DEF int binary_heap_size(BinaryHeap *heap);

/* 이진 힙 `heap`이 비어 있는지 확인한다. */
BINARY_HEAP_DEF bool binary_heap_is_empty(BinaryHeap *heap);

/* 이진 힙 `heap`에 값 `value`를 추가한다. */
BINARY_HEAP_DEF void binary_heap_push(BinaryHeap *heap, unsigned int value);

/* 이진 힙 `heap`에서 최댓값을 삭제하고, 그 값을 반환한다. */
BINARY_HEAP_DEF int binary_heap_pop(BinaryHeap *heap);

#endif // `BINARY_HEAP_H`

#ifdef BINARY_HEAP_IMPLEMENTATION

/* 이진 힙을 생성한다. */
BINARY_HEAP_DEF BinaryHeap *binary_heap_create(void) {
    BinaryHeap *result = calloc(1, sizeof(BinaryHeap));
    
    result->capacity = 8;
    result->ptr = calloc(result->capacity, sizeof(unsigned int));
    
    return result;
}

/* 이진 힙 `heap`에 할당된 메모리를 해제한다. */
BINARY_HEAP_DEF void binary_heap_release(BinaryHeap *heap) {
    free(heap->ptr);
    free(heap);
}

/* 이진 힙 `heap`에 들어 있는 모든 값을 제거한다. */
BINARY_HEAP_DEF void binary_heap_clear(BinaryHeap *heap) {
    if (heap != NULL) heap->length = 0;
}

/* 이진 힙 `heap`에 들어 있는 값의 개수를 반환한다. */
BINARY_HEAP_DEF int binary_heap_size(BinaryHeap *heap) {
    return (heap != NULL) ? heap->length : 0;
}

/* 이진 힙 `heap`이 비어 있는지 확인한다. */
BINARY_HEAP_DEF bool binary_heap_is_empty(BinaryHeap *heap) {
    return (heap == NULL) || (heap != NULL && heap->length == 0);
}

/* 이진 힙 `heap`에 값 `value`를 추가한다. */
BINARY_HEAP_DEF void binary_heap_push(BinaryHeap *heap, unsigned int value) {
    if (heap == NULL) return;
    
    if (heap->length >= heap->capacity) {
        heap->capacity *= 2;
        heap->ptr = realloc(heap->ptr, heap->capacity * sizeof(unsigned int));
    }
    
    heap->ptr[++heap->length] = value;
    
    int i = heap->length;
    
    // 이진 힙을 상향식으로 복구한다.
    while (i > 1 && heap->ptr[i] > heap->ptr[i / 2]) {
        int temp_value = heap->ptr[i];
        
        heap->ptr[i] = heap->ptr[i / 2];
        heap->ptr[i / 2] = temp_value;
        
        i /= 2;
    }
}

/* 이진 힙 `heap`에서 최댓값을 삭제하고, 그 값을 반환한다. */
BINARY_HEAP_DEF int binary_heap_pop(BinaryHeap *heap) {
    if (heap == NULL || heap->length == 0) return -1;
    
    int result = heap->ptr[1];
    
    heap->ptr[1] = heap->ptr[heap->length];
    heap->ptr[heap->length--] = -1;
    
    int i = 1;
    
    // 이진 힙을 하향식으로 복구한다.
    while (2 * i <= heap->length) {
        int j = 2 * i;
        
        if (heap->ptr[j] < heap->ptr[j + 1] && j + 1 <= heap->length) j++;
        
        // 부모 노드가 자식 노드보다 크면 복구를 마친다.
        if (heap->ptr[i] > heap->ptr[j]) break;
        
        int temp_value = heap->ptr[i];
        
        heap->ptr[i] = heap->ptr[j];
        heap->ptr[j] = temp_value;
        
        i = j;
    }
    
    return result;
}

#endif // `BINARY_HEAP_IMPLEMENTATION`