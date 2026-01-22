#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char* s, char* p, int* returnSize) {
    int lenght = strlen(p);
    int first = 0, last;
    int number = 0;
    int* bound = NULL;
    // Tạo hash map cho tập con cần tìm
    int arr[26] = {0};
    for (int i = 0; i < lenght; i++)
    {
        arr[p[i] - 'a']++;
    }

    for (int i = 0; i < strlen(s); i++)
    {
        if( arr[s[i] - 'a'] > 0 ) {
            //tức là có thì bắt đầu tìm
            first = i;
            last = i + lenght - 1;
            int temp[26];
            bool flag = true;
            memcpy(temp, arr, sizeof(arr));
            // đưa đoạn mà bắt đầu từ first đó vào hash đã tạo để check đúng k
            do
            {
                arr[s[first--] - 'a']--;
                arr[s[last--] - 'a']--;
            } while (first != last);
            // Check xem có phải là anagrams k?
            for (int index = 0; index < lenght; index++)
            {
                if(arr[p[i] - 'a'] != 0)
                {
                    flag = false;
                    break;
                }
            }
            // Nếu phải thì add index vào để trả về
            if(flag != false) {
                number++;
                bound = (int*)realloc(returnSize, sizeof(int) * number);
                if (!bound)
                {
                    printf("Cannot allocate\n");
                }
                bound[number-1] = i;
            }


            
        }
    }
    
    *returnSize = number;

    return bound;
}



int main() {


    return 0;
}