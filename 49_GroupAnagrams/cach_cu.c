#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//DONE: Tạo ra hash table
//?: hash table đang sai => tạo ra lưu từng ký tự => Đã Fix

#define LOWERCASE 122
#define MAX_GROUND 104

typedef uint8_t status_avalable;

#define  PRESENT    1
#define  ABSENT     0
   

inline unsigned int hash(char ch);
bool findSubStr(status_avalable* hashTable, char* str);
bool insert_hashtable(status_avalable* hashTable, char* substr);
struct OneGrounpTable_Ty* Create_NewGrounp(char* substr);
void Init_Ground(struct OneGrounpTable_Ty* Init_GroundTy);
void find_Alldirectory(struct OneGrounpTable_Ty** OneGrounpTable, int* count_maxGroup, char* str);
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes);

//The letter is not capitalizedInit_Ground
//a b c d e f g h i j k l m n o p q r s t u v w x y z

struct OneGrounpTable_Ty {
    //hashtable
    bool hashTable_ty[LOWERCASE];
    char** str; //Contanier to save str similar each together
    int count; // Số lượng có trong nhóm đó
};

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    // Giải thích nhóm : là một nhóm các phần tử Anagrams

    //Count hash
    uint8_t count_hash = 0;
    // Mảng quản lý con trỏ mỗi nhóm
    struct OneGrounpTable_Ty* OneGrounpTable[MAX_GROUND];
    int count_maxGround = 0;

    char*** str_return = NULL;

    // TCase : Example 3
    if( strsSize == 1 ) {
        str_return = &strs;
        return str_return;
    }

    // TC : Example 1
    if( strsSize == 0 ) {
        str_return = &strs;
        return str_return;
    }

    for(int i = 0; i < strsSize; i++) {
        if ( i == 0 ) {
            //Thêm nhóm đầu tiên vào
            OneGrounpTable[count_maxGround] = Create_NewGrounp( strs[i] );
            count_maxGround++;
        } else {
            // Thực hiện tách str
            // Truyền vào địa chỉ của phần tử đầu tiên
            find_Alldirectory(OneGrounpTable, &count_maxGround, strs[i]);
        }
    }

    *returnSize = count_maxGround + 1;

    for(int i = 0; i < count_maxGround; i++) {
        str_return[i] = OneGrounpTable[i]->str;
        *returnColumnSizes[i] = OneGrounpTable[i]->count;
    }

    return str_return;
}

void find_Alldirectory(struct OneGrounpTable_Ty** OneGrounpTable, int* count_maxGroup, char* str) {
    bool kq = false;
    char** temp;

    for(int i = 0; i < *count_maxGroup; i++) {
        kq = findSubStr(OneGrounpTable[i]->hashTable_ty, str);


        //TODO: check lại đoạn đây vì OneGrounpTable là một con trỏ cấp 2 xem nó có ảnh hưởng các phần tử con của nó k
        if (kq == true) {
            OneGrounpTable[i]->count++;
            int index_new = OneGrounpTable[i]->count;
            // Nếu tìm được nhóm,thì add vào
            // Cấp phát thêm phần tử cho str
            //!: BUG
            temp = (char**) realloc( OneGrounpTable[i]->str, OneGrounpTable[i]->count * sizeof(char*) );
            if (temp == NULL) {
                fprintf(stderr, "Error allocate memory of fun readlloc\n");
                exit(EXIT_FAILURE); // Thoát với mã lỗi
            }
            OneGrounpTable[i]->str = temp;
            OneGrounpTable[i]->str[index_new-1] = str; //!: Có thể là bug &str
            // Tìm được thì trả về luôn
            return;
        }
    }

    // Tìm hết mà k tìm thất thì phải tạo mới directory cho nó
    OneGrounpTable[*count_maxGroup] = Create_NewGrounp(str);
    (*count_maxGroup)++;
}

struct OneGrounpTable_Ty* Create_NewGrounp(char* substr) {
    // Tạo ra nhóm mới
    // Tạo ra tổng số byte của OneGrounpTable_Ty
    // Một con trỏ void trỏ đến đối tượng được tạo ra 
    struct OneGrounpTable_Ty* OneGrounpTable = ( struct OneGrounpTable_Ty* )malloc( sizeof( struct OneGrounpTable_Ty ) );
    if (OneGrounpTable != NULL) {
        Init_Ground(OneGrounpTable);
    }

    // Add vào hash table
    insert_hashtable( OneGrounpTable->hashTable_ty, substr );
    // Thêm phần từ đầu tiên vào nhóm
    OneGrounpTable->str = &substr; //!: Debug lại chỗ này: có lẽ đã đúng
    return OneGrounpTable;
}

// ** Func : Gán giá trị ban đầu cho bảng hash table
void Init_Ground(struct OneGrounpTable_Ty* Init_GroundTy) {
    for (int i = 0; i < LOWERCASE; i++) {
        Init_GroundTy->hashTable_ty[i] = ABSENT;
    }
    Init_GroundTy->count = 1;
    // Cấp phát đúng 1 phần tử đầu tiên
    // 4byte kiểu con trỏ : lúc này str có thể lưu một con trỏ
    Init_GroundTy->str = ( char** )malloc( sizeof(char*) *  ( Init_GroundTy->count) );
}

/* Tính toán hash value */
unsigned int hash(char ch) {
    int hashValue = 0;
    
    hashValue = ch;

    return hashValue;
}

bool insert_hashtable(status_avalable* hashTable, char* substr) {
    for(int i = 0; i < strlen(substr); i++) {
        int hash_value = hash(substr[i]);
        hashTable[hash_value] = PRESENT;
    }
}

bool findSubStr(status_avalable* hashTable, char* str) {
    for(int i = 0; i < strlen(str); i++) {

        int hash_value = hash(str[i]);

        if (hashTable[hash_value] == ABSENT)
            return false;
    
    }
    return true;
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
