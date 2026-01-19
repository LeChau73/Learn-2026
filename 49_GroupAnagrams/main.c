#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    
    


    return ;
}



int main() {
    char* str[] = {"bat", "nat", "tan", "ate", "eat", "tea"};

    int sizeof_ptr = sizeof(str[0]);//sizeof(char [4])
    int sizeof_ptrLev2 = sizeof(str);


    int size = sizeof_ptrLev2 / sizeof_ptr;
    printf("\tsize[%d]\n\t", size);

    int size_return;

    //?: Cần độ dài của mỗi phần tử trong mảng trả về (vì phần tử trong mảng trả về một nhóm chuỗi) 
    int** returnColumnSizes;
                                                            // int** returnColumnSizes
    char*** str_value = groupAnagrams(str, size, &size_return, returnColumnSizes);

    for( int i = 0; i < size_return; i++ ) {
        char** ptr = str_value[i];
        printf("Ground[%d] = ", i);
        for(int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%s, ", ptr[j]);
        }
        printf("\n");
    }

    return 0;
}
