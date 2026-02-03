#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>



/* Tạo 1 hash table cho p : hash giống như 1 table để tham chiếu khi kéo cửa sổ
    *   Tạo 1 window với size bằng p
    *   Duyệt qua từng phần tử của s, mỗi lần duyệt thì add vào window đó phần
    *   tử mới ,và bỏ phần tử đầu ra window
    *   So sánh 2 window ,nếu match thì add index vào
*/
int* findAnagrams(char* s, char* p, int* returnSize) {
    int lenght = strlen(p);
    *returnSize = 0;
    if(lenght > strlen(s))
    {
        
        return NULL;
    }

    
    int arr[26] = {0}, window[26] = {0};

    int *containIndex = (int*)malloc(sizeof(int) * strlen(s));
    
    // Tạo hash cho p và window cùng size với p bắt đầu từ index = 0
    for(int i = 0; i < lenght; i++) {
        arr[p[i] - 'a']++;
        if(i < lenght - 1)          // ở index cuối k thêm vào vì khi for ở dưới
            window[s[i] - 'a']++;
    }
    //6 - 3 = 3
    int end_window;

    // a b c d d a
    for (size_t i = 0; i <= strlen(s) - lenght; i++)
    {
        end_window = i + lenght - 1;    //lấy index cuối của window
        window[s[end_window] - 'a']++;  // thêm index cuối vào window
        bool flag = true;                   
        //  compare các phần từ trong window và hash
        for (size_t j = 0; j < 26; j++)     
        {
            if(arr[j] != window[j]) {
                flag = false;
                break;
            }
            
        }
        //match hết thì gán vào
        if(flag) {
            containIndex[(*returnSize)++] = i;
        }
        window[s[i] - 'a']--; //kéo cửa sổ đầu qua 1 đơn vì
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