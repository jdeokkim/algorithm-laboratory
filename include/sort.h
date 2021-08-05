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

/* 길이가 `count`인 배열 `ptr`을 선택 정렬한다. */
SORT_DEF void selection_sort(int *ptr, int count);

/* 길이가 `count`인 배열 `ptr`을 삽입 정렬한다. */
SORT_DEF void insertion_sort(int *ptr, int count);

/* 길이가 `count`인 배열 `ptr`을 셸 정렬한다. */
SORT_DEF void shell_sort(int *ptr, int count);

/* 길이가 `count`인 배열 `ptr`을 병합 정렬한다. */
SORT_DEF void merge_sort(int *ptr, int count);

/* 길이가 `count`인 배열 `ptr`을 퀵 정렬한다. */
SORT_DEF void quick_sort(int *ptr, int count);

#endif // `SORT_H`

#ifdef SORT_IMPLEMENTATION

/* 셸 정렬에 사용되는 커누스 간격 순열을 나타내는 배열. */
SORT_DEF const int GAP_SEQUENCE[16] = { 
    1, 4, 13, 40, 121, 364, 1093, 3280, 9841, 29524, 
    88573, 265720, 797161, 2391484, 7174453, 21523360
};

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
        2. 그 항목보다 큰 항목을 전부 오른쪽으로 한 칸씩 이동시킨다.
        3. 이러한 작업을 모든 항목이 정렬될 때까지 반복한다.
        
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
    
    int h_index = 0;
    
    for (int i = 1; GAP_SEQUENCE[h_index + 1] < count; i++) 
        h_index = i;
    
    // `h`가 1이 될 때까지 배열을 h-정렬시킨다.
    while (GAP_SEQUENCE[h_index] >= 1) {
        int h = GAP_SEQUENCE[h_index];
        
        // 배열의 매 `h`번째 항목을 부분적으로 삽입 정렬한다.
        for (int i = h; i < count; i++) {
            for (int j = i; j >= h; j -= h) {
                if (ptr[j] > ptr[j - h]) break;
                
                int temp_value = ptr[j];
            
                ptr[j] = ptr[j - h];
                ptr[j - h] = temp_value;
            }
        }
        
        h_index--;
    } 
}

/* 배열 `ptr`의 부분 배열 `ptr[low..mid]`과 `ptr[(mid + 1)..high]`를 하나로 합친다. */
SORT_DEF void _merge_two_arrays(int *ptr, int *aux_ptr, int low, int mid, int high) {
    int i = low, j = mid + 1;
    
    for (int k = low; k <= high; k++)
        aux_ptr[k] = ptr[k];
    
    for (int k = low; k <= high; k++) {
        /*
            왼쪽 절반에 남은 항목이 존재하거나 왼쪽 절반의 항목이 오른쪽 절반의 항목보다 작은 경우,
            왼쪽 절반에서 항목 한 개를 꺼내고, 그렇지 않을 경우 오른쪽 절반에서 항목 한 개를 꺼낸다.
        */
        
        if (i <= mid && (j > high || aux_ptr[i] <= aux_ptr[j])) ptr[k] = aux_ptr[i++];
        else ptr[k] = aux_ptr[j++];
    }
}

/* 배열 `ptr`의 부분 배열 `ptr[low..high]`를 병합 정렬한다. */
SORT_DEF void _merge_sort_helper(int *ptr, int *aux_ptr, int low, int high) {
    if (low >= high) return;
    
    int mid = (low + high) / 2;
    
    // `ptr[low..(mid + 1)]`과 `ptr[(mid + 1)..high]`를 정렬한다.
    _merge_sort_helper(ptr, aux_ptr, low, mid);
    _merge_sort_helper(ptr, aux_ptr, mid + 1, high);
    
    // 정렬된 두 배열을 하나로 합친다.
    _merge_two_arrays(ptr, aux_ptr, low, mid, high);
}
 
/* 길이가 `count`인 배열 `ptr`을 병합 정렬한다. */
SORT_DEF void merge_sort(int *ptr, int count) {
    /*
        [병합 정렬의 동작 과정]
        
        1. 배열을 왼쪽 절반과 오른쪽 절반으로 나눈다.
        2. 두 배열을 각각 재귀적으로 정렬한 다음, 하나로 합친다.
        
        [병합 정렬의 성능]
        
        - 병합 정렬은 구현 방법에 따라 하향식 (top-down) 병합 정렬과 상향식 (bottom-up) 
          병합 정렬로 나눌 수 있다.
        - 하향식 병합 정렬과 상향식 병합 정렬의 시간 복잡도는 모두 `O(N * log(N))`이고, 
          정렬을 위해 `N`에 비례하는 메모리 공간을 추가적으로 사용한다.
    */
    
    int *aux_ptr = calloc(count, sizeof(int));
    
    for (int i = 0; i < count; i++)
        aux_ptr[i] = ptr[i];
    
    _merge_sort_helper(ptr, aux_ptr, 0, count - 1);
    
    free(aux_ptr);
}

/* 배열 `ptr`의 부분 배열 `ptr[low..high]`를 적절하게 분할하고, 분할 기준 항목의 인덱스를 반환한다. */
SORT_DEF int _quick_sort_partition(int *ptr, int low, int high) {
    int i = low, j = high + 1;
    
    for (;;) {
        while (ptr[i] < ptr[low] && i < high) i++;
        while (ptr[j] > ptr[low] && j > low) j--;
        
        if (i >= j) break;
        
        int temp_value = ptr[i];
        
        ptr[i] = ptr[j];
        ptr[j] = temp_value;
    }
    
    int temp_value = ptr[low];
        
    ptr[low] = ptr[j];
    ptr[j] = temp_value;
    
    return j;
}

/* 배열 `ptr`의 부분 배열 `ptr[low..high]`를 퀵 정렬한다. */
SORT_DEF void _quick_sort_helper(int *ptr, int low, int high) {
    if (low >= high) return;
    
    int mid = _quick_sort_partition(ptr, low, high);
    
    _quick_sort_helper(ptr, low, mid - 1);
    _quick_sort_helper(ptr, mid + 1, high);
}

/* 길이가 `count`인 배열 `ptr`을 퀵 정렬한다. */
SORT_DEF void quick_sort(int *ptr, int count) {
    /*
        [퀵 정렬의 동작 과정]
        
        1. 배열에서 임의의 항목 `v`를 선택한다.
        2. `v`보다 왼쪽에 있는 항목은 모두 `v`보다 작고, 오른쪽에 있는 항목은 모두 `v`보다
           크도록 배열을 나눈다.
        3. `v`를 기준으로 나눈 두 부분 배열을 재귀적으로 정렬한다.
        
        [퀵 정렬의 성능]
        
        - 퀵 정렬의 시간 복잡도는 `O(N * log(N))` ~ `O(N^2)`임이 알려져 있다.
    */
    
    /* TODO: 퀵 정렬의 실행 시간 예측을 위해 배열을 무작위로 섞기 */
    
    _quick_sort_helper(ptr, 0, count - 1);
}

#endif // `SORT_IMPLEMENTATION`