#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
int* findAnagrams(char* s, char* p, int* returnSize) {
    int lenght = strlen(p);
    *returnSize = 0;
    if(lenght > strlen(s))
    {
        
        return NULL;
    }

    
    int arr[26] = {0}, window[26] = {0};

    int *containIndex = (int*)malloc(sizeof(int) * strlen(s));
    
    // Create hash table for p
    for(int i = 0; i < lenght; i++) {
        arr[p[i] - 'a']++;
        if(i < lenght - 1)
            window[s[i] - 'a']++;
    }
    //6 - 3 = 3
    int end_window;

    // a b c d d a
    for (size_t i = 0; i <= strlen(s) - lenght; i++)
    {
        end_window = i + lenght - 1;
        window[s[end_window] - 'a']++;
        bool flag = true;
        for (size_t j = 0; j < 26; j++)
        {
            if(arr[j] != window[j]) {
                flag = false;
                break;
            }
            
        }
        if(flag) {
            containIndex[(*returnSize)++] = i;
        }
        window[s[i] - 'a']--;
    }
    

    return containIndex;

}

//a b a a c b a b c
//a b c


int main() {

    char* s =  "cbaebabacd";
    char* p =  "abc";
    int size;
    int* kq = findAnagrams(s, p, &size);
    printf("Size = %d { ", size);
    for(int i = 0; i < size; i++)
        printf(" %d ,", kq[i]);

     printf(" } \n");

    return 0;
}