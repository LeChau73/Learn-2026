#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>



//Hash funtion
bool isAnagram(char* s, char* t) {
    
    if(strlen(s) != strlen(t))
        return false;

    int arr[26];

    int j = 0;
    
    while(s[j] != '\0') {
        arr[s[j] - 'a']++;
        arr[t[j] - 'a']--;
        j++;
    }

    for(int i = 0; i < 26; i ++) {
        if(arr[i] != 0)
            return false;
    }
    
    return true;
}

int main() {


    return 0;
}