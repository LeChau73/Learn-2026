#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>

#include <stdlib.h>

// qsort(void *base,           // con trỏ đến mảng
//       size_t nmemb,         // số phần tử trong mảng
//       size_t size,          // kích thước mỗi phần tử (tính bằng byte)
//       int (*compar)(const void *, const void *));  // hàm so sánh

// callback compare nhỏ đến lớn
int compare(const void *a, const void* b) {
    int valA = *(int*)a;
    int valB = *(int*)b;

    if (valA < valB) return -1;
    if (valA > valB) return 1;
    return 0;
}

bool containsDuplicate(int* nums, int numsSize) {

    //QuickSort O(n log n)
    qsort(nums, numsSize, sizeof(int), compare);

    for(int i = 0; i < numsSize - 1; i++) {
        if(nums[i] == nums[i+1])
            return true;
    }

    return false;

}

int main() {
    int arr[] = {1, 2, 3, 4, 3, 5, 4};
    int lenght = sizeof(arr) / sizeof(arr[0]);
    printf("Result = %d", containsDuplicate(arr, lenght));

    return 0;
}