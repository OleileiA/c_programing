#include <stdio.h>
#include "test.h"

int main() {

    int arr[] = {4, 2, 1, 9, 5, 0, 3, 8, 7, 6};

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9 - i; ++j) {
            if(arr[j] > arr[j + 1]) swap(&arr[j], &arr[j + 1]);
        }
    }

    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }
}