#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>


int* findAnagrams(char* s, char* p, int* returnSize) {
    int lenght = strlen(p);
    *returnSize = 0;
    if(lenght > strlen(s))
    {
        
        return NULL;
    }

    int arr[26] = {0};

    int *containIndex = (int*)malloc(sizeof(int) * strlen(s));

    // Create hash table for p
    for(int i = 0; i < lenght; i++) {
        arr[p[i] - 'a']++;
    }

    int count_match = 0;

    int end_window, start_window = 0;
    for (end_window = 0; end_window < strlen(s); end_window++)
    {
        if( --arr[s[end_window] - 'a'] >= 0 )
        {
            if(count_match == 0) {
                //Lần đầu match = save index lại
                start_window = end_window;
            }
            count_match++;
            if (count_match == lenght)
            {
                // match rồi thì save lại và chuyển qua index mới
                containIndex[(*returnSize)++] = start_window;
                count_match = end_window - start_window;        //index
                arr[s[start_window] - 'a']++;
                start_window++;
            }
            
        } else {
            //Trong thời điểm kiểm tra range có match k mà tìm thấy thằng k phù hợp

            // Sẽ có 2 case : 1: b a b (trùng nhau) Case a be
            // Hander case 2 trước
            // BUG: Không thể phân chia được đâu là  a b e và b a b => mai debug thêm
            if(count_match > 0)
            {
                for (size_t i = start_window; i < end_window; i++)
                {
                    arr[s[i] - 'a']++;
                    if(arr[s[i] - 'a'] == 0)
                        start_window = i+1;
                }

                if(arr[s[end_window] - 'a'] == -1) {
                    // tức là tại vị trí này ký tự đang k có trong hash
                        // Không có trong hash thì xoá trạng thái đang ở trong quá trình match anagram
                        count_match = 0;
                } else {
                    //Nếu == 0 hay > 0 tức là ký tự hiện tại match với case nằm trong nó
                    for (size_t i = start_window; i < end_window; i++)
                    {
                        arr[s[i] - 'a']--;
                    }
                    count_match = end_window - start_window + 1;
                }

            }
        }
    }

    return containIndex;

}



int main() {

    char* s =  "abaacbabc";
    char* p =  "abc";
    int size;
    int* kq = findAnagrams(s, p, &size);
    printf("Size = %d { ", size);
    for(int i = 0; i < size; i++)
        printf(" %d ,", kq[i]);

     printf(" } \n");

    return 0;
}