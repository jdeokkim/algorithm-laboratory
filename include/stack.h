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

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_DEF static

/* 스택을 나타내는 구조체. */
typedef struct Stack {
    int length;
    int capacity;
    unsigned int *ptr;
} Stack;

/* 스택을 생성한다. */
STACK_DEF Stack *stack_create(void);

/* 스택 `stack`에 할당된 메모리를 해제한다. */
STACK_DEF void stack_release(Stack *stack);

/* 스택 `stack`에 들어 있는 모든 값을 제거한다. */
STACK_DEF void stack_clear(Stack *stack);

/* 스택 `stack`에 들어 있는 값의 개수를 반환한다. */
STACK_DEF int stack_size(Stack *stack);

/* 스택 `stack`이 비어 있는지 확인한다. */
STACK_DEF bool stack_is_empty(Stack *stack);

/* 스택 `stack`에 값 `value`를 추가한다. */
STACK_DEF void stack_push(Stack *stack, unsigned int value);

/* 스택 `stack`에서 가장 마지막에 추가된 값을 제거하고, 그 값을 반환한다. */
STACK_DEF int stack_pop(Stack *stack);

/* 스택 `stack`에서 가장 마지막에 추가된 값을 반환한다. */
STACK_DEF int stack_peek(Stack *stack);

#endif // `STACK_H`

#ifdef STACK_IMPLEMENTATION

/* 스택을 생성한다. */
STACK_DEF Stack *stack_create(void) {
    Stack *result = calloc(1, sizeof(Stack));
    
    result->capacity = 8;
    result->ptr = calloc(result->capacity, sizeof(unsigned int));
    
    return result;
}

/* 스택 `stack`에 할당된 메모리를 해제한다. */
STACK_DEF void stack_release(Stack *stack) {
    free(stack);
}

/* 스택 `stack`에 들어 있는 모든 값을 제거한다. */
STACK_DEF void stack_clear(Stack *stack) {
    if (stack != NULL) stack->length = 0;
}

/* 스택 `stack`에 들어 있는 항목의 개수를 반환한다. */
STACK_DEF int stack_size(Stack *stack) {
    return (stack != NULL) ? stack->length : -1;
}

/* 스택 `stack`이 비어 있는지 확인한다. */
STACK_DEF bool stack_is_empty(Stack *stack) {
    return (stack != NULL && stack->length <= 0);
}

/* 스택 `stack`에 값 `value`를 추가한다. */
STACK_DEF void stack_push(Stack *stack, unsigned int value) {
    if (stack == NULL) return;
    
    if (stack->length >= stack->capacity) {
        stack->capacity *= 2;
        stack->ptr = realloc(stack->ptr, 2 * stack->capacity * sizeof(unsigned int));
    }
    
    stack->ptr[stack->length++] = value;
}

/* 스택 `stack`에서 가장 마지막에 추가된 항목을 제거하고, 그 항목을 반환한다. */
STACK_DEF int stack_pop(Stack *stack) {
    if (stack == NULL || stack->length <= 0) return -1;
    
    return stack->ptr[(stack->length--) - 1];
}

/* 스택 `stack`에서 가장 마지막에 추가된 항목을 반환한다. */
STACK_DEF int stack_peek(Stack *stack) {
    return (stack != NULL && stack->length > 0) ? stack->ptr[stack->length - 1] : -1;
}

#endif // `STACK_IMPLEMENTATION`