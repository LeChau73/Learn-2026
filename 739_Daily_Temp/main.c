#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct
{
    int* contain;
    int  ptr_top;
    int  max_tail;
    int  max_cap;
}queue_int;

void init(queue_int* qe, int size) {
    qe->contain = (int*)malloc(sizeof(int)*size);
    qe->ptr_top = 0;
    qe->max_tail = 0;
    qe->max_cap = size;
}

void push(queue_int* qe, int data) {
    if(qe->max_tail + 1 > qe->max_cap)
    {
        return;
    }
    qe->contain[qe->max_tail++] = data;

}

int pop(queue_int* qe) {
    if(qe->ptr_top + 1 > qe->max_tail)
    {
        return -1;
    }
    return qe->contain[qe->ptr_top++];
}


int pop_no_remove(queue_int* qe) {
    if(qe->ptr_top + 1 > qe->max_tail)
    {
        return -1;
    }
    int value = qe->contain[qe->ptr_top];
    return value;
}

void erase(queue_int* qe) {

    memset(qe->contain, 0x00, sizeof(int)*qe->max_tail);
    qe->ptr_top = 0;
    qe->max_tail = 0;
}

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {

    if(temperaturesSize <= 0)
        return (int*)calloc(1, 4);

    // Allocate for values return ( array contain number diff between warmer temperature and size of array )
    int* output = (int*)malloc(sizeof(int)* (temperaturesSize + 1) );

    if(output == NULL)
        return NULL;

    //mask
    output[temperaturesSize] = 0x0;

    // Allocated for retrunSize
    *returnSize = temperaturesSize;

    queue_int qe_l;
    init(&qe_l, temperaturesSize);

    int first = 0;
    int second = 0;
    int ref_cmp;
    // 73,74,75,71,69,72,76,73
    while ( first <= second && second < temperaturesSize - 1 ) {

        int f_deference = temperatures[first];
        int s_deference = temperatures[++second];
        int hieu_so = s_deference - f_deference;

        if(hieu_so > 0) {
            push(&qe_l, second);
            int kc = second - first;
            output[first++] = kc;
            if(kc > 1) {
                while( first != second ) {
                    int value_top = pop_no_remove(&qe_l);
                    if( value_top <= first ) {  //index hiện tại mà bằng với phần tử trong queue
                        pop(&qe_l); //Bỏ nó ra lấy phần tử tiếp theo
                        value_top = pop_no_remove(&qe_l);
                    }
                    int a = value_top - first;
                    output[first++] = a;
                }
            }
            //xoá queue đi
            erase(&qe_l);
        } else {
            if( second == temperaturesSize - 1 && first < second ) {
                output[first++] = 0;
                second = first;
            }

            if(s_deference > pop_no_remove(&qe_l)) { //lấy phần từ tiếp theo so sánh với đỉnh của queue
                push(&qe_l, second);
            }
        }
    }
    output[first] = 0;

    return output;
}


int main() {

    int arr[] = {77,54,66,63,90,94,36,90,89,87};

    int size_return;
    int* output =  dailyTemperatures(arr, sizeof(arr)/sizeof(arr[0]), &size_return);

    printf("OutPut : ");
    for (int i = 0; i < size_return; i++)
    {
        printf(" %d ", output[i]);
    }
    

    return 0;
}