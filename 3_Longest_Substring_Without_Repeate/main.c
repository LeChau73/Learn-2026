#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//TODO: mai code tiếp
//BUG: đang bị nếu d xuất hiện đầu thì k nhận viết được
int lengthOfLongestSubstring(char* s) {

    if(strlen(s) == 1)
        return 1;

    int tail = 0;
    int head = 0;
    int count_max = 0;
    int table[256] = {0};

    for (size_t i = 0; i < strlen(s); i++)
    {
        // Nếu là lần đầu thì gán
        if(table[s[i]] == 0)
            table[s[i]] = i;
    }

    while (s[tail] != '\0')
    {
        if(table[s[tail]] < tail)
        {
            //  Tức là xuất hiện lần 2 thì di chuyển start đến
            //  table[s[tail]] đang là index của phần tử bị lặp , +1 để bỏ nó ra
            if(table[s[tail]] >= head)
                head = table[s[tail]] + 1;  //correct
        }
        table[s[tail]] = tail; //update lại giá trị tại đó tương ứng với index hiện tại
        count_max = (tail - head + 1) < count_max ? count_max : (tail - head + 1);  //+ 1 đã tính rồi,cho nên lần
        tail++;
        //p w w
    }

    return count_max;

}


int main() {
    char* s = "aabaab!bb";// a -> 0
    // a b b a
    //   f   e
    // head         tail
    // d    v        d       v
    // 0    1        0       0
    // t   m   m   z   u   x  t
    // 

    int size = lengthOfLongestSubstring(s);
    printf("Count = %d\n", size);

    return 0;
}
