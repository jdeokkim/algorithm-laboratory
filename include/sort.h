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

#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>

#define SORT_DEF static

#define SORT_MAX_ARRAY_LENGTH 20000000

/* 셸 정렬에 사용되는 간격 순열을 나타내는 배열. */
SORT_DEF const int GAP_SEQUENCE[16] = { 
    1, 4, 13, 40, 121, 364, 1093, 3280, 9841, 29524, 
    88573, 265720, 797161, 2391484, 7174453, 21523360
};

/* 길이가 `count`인 배열 `ptr`을 선택 정렬한다. */
SORT_DEF void selection_sort(int *ptr, int count);

/* 길이가 `count`인 배열 `ptr`을 삽입 정렬한다. */
SORT_DEF void insertion_sort(int *ptr, int count);

/* 길이가 `count`인 배열 `ptr`을 셸 정렬한다. */
SORT_DEF void shell_sort(int *ptr, int count);

#endif // `SORT_H`

#ifdef SORT_IMPLEMENTATION

/* 길이가 `count`인 배열 `ptr`을 선택 정렬한다. */
SORT_DEF void selection_sort(int *ptr, int count) {
    /*
        [선택 정렬의 동작 과정]
        
        1. 배열에서 가장 작은 항목을 찾는다.
        2. 그 항목의 위치와 배열의 가장 첫 항목의 위치를 서로 바꾼다.
        3. 그 다음으로 가장 작은 항목을 찾고, 2번 과정을 거친다.
        4. 이러한 작업을 모든 항목이 정렬될 때까지 반복한다.
        
        [선택 정렬의 성능]
        
        - 선택 정렬은 배열의 각 원소를 `(N * (N - 1)) / 2)`번 비교한다.
        - 또한 선택 정렬은 각 원소의 위치를 `N`번 바꾼다.
        - 따라서 선택 정렬의 시간 복잡도는 `O(N^2)`이다.
    */
    
    if (ptr == NULL || count > SORT_MAX_ARRAY_LENGTH) return;
    
    for (int i = 0; i < count; i++) {
        int min_index = i;
        
        // 배열에서 가장 작은 항목을 찾는다.
        for (int j = i + 1; j < count; j++) {
            if (ptr[min_index] > ptr[j])
                min_index = j;
        }
        
        int temp_value = ptr[i];
        
        ptr[i] = ptr[min_index];
        ptr[min_index] = temp_value;
    }
}

/* 길이가 `count`인 배열 `ptr`을 삽입 정렬한다. */
SORT_DEF void insertion_sort(int *ptr, int count) {
    /*
        [삽입 정렬의 동작 과정]
        
        1. 배열에서 항목 하나를 선택한다.
        3. 그 항목보다 큰 항목을 전부 오른쪽으로 한 칸씩 이동시킨다.
        4. 이러한 작업을 모든 항목이 정렬될 때까지 반복한다.
        
        [삽입 정렬의 성능]
        
        - 삽입 정렬은 배열의 각 원소를 최소 `N - 1`번, 최대 `(N^2) / 2`번 비교한다.
        - 또한 삽입 정렬은 각 원소의 위치를 최소 `0`번, 최대 `(N^2) / 2`번 바꾼다.
        - 따라서 삽입 정렬의 시간 복잡도는 `O(N)` ~ `O(N^2)`이다.
    */
    
    if (ptr == NULL || count > SORT_MAX_ARRAY_LENGTH) return;
    
    for (int i = 1; i < count; i++) {
        for (int j = i; j > 0; j--) {
            if (ptr[j - 1] <= ptr[j]) break; 
            
            int temp_value = ptr[j];
            
            ptr[j] = ptr[j - 1];
            ptr[j - 1] = temp_value;
        }
    }
}

/* 길이가 `count`인 배열 `ptr`을 셸 정렬한다. */
SORT_DEF void shell_sort(int *ptr, int count) {
    /*
        [셸 정렬의 동작 과정]
        
        1. 배열의 매 `h`번째 항목을 부분적으로 삽입 정렬한다. 이렇게 부분적으로 정렬된 
           배열을 h-정렬된 배열이라고 한다.
        2. 그 다음에는 정해진 순열에 따라 `h`의 값을 줄이고 배열을 h-정렬시킨다.
        3. 이러한 작업을 `h`가 1이 될 때까지 반복한다.
        
        [셸 정렬의 성능]
        
        - 셸 정렬의 평균적인 시간 복잡도는 `h`의 값을 정하는 데에 사용되는 간격 순열에 따라
          조금씩 달라진다.
        - 일반적으로 셸 정렬의 시간 복잡도는 `O(N * log(N))` ~ `O(N^2)`임이 알려져 있다.
    */
    
    if (ptr == NULL || count > SORT_MAX_ARRAY_LENGTH) return;
    
    /* TODO: ... */
}

#endif // `SORT_IMPLEMENTATION`