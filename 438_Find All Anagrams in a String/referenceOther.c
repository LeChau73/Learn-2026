/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char* s, char* p, int* returnSize) {
    
    int* table = calloc(26,sizeof(int));
    int* ans = malloc(sizeof(int)*strlen(s));
    (*returnSize) = 0;

    int i = 0;
    //Tạo ra 1 table như mình làm
    while(p[i] != '\0')
    {
        table[p[i++] - 97]++;
    }

    int head = 0, tail = 0;
    //int count = 0;
    int p_count = strlen(p);    //lấy size của p

    while(s[tail] != '\0')
    {
        //printf("%d \n", )
        table[s[tail] - 97]--;  //Đưa ký tự hiện tại vào table
        if ((table[s[tail] - 97]) >= 0) //Nếu mà match với table
        {   
            if ((tail - head + 1) == p_count)   //Nếu mà match hết
            {
                ans[(*returnSize)] = head;
                (*returnSize)++;
                table[s[head++] - 97]++; // trả về và tăng lên 1 đơn vị
            }
        }
        else    //Nếu không match
        {
            while(table[s[tail] - 97] < 0)  //Nếu mà end hiện tại chưa được về trạng thái ban đầu
            {
                table[s[head++] - 97]++;    //trả về đến khi nào table y nguyên
            }
        }
        tail++; //tăng lên 1 đơn vị
    }

    return ans;
}