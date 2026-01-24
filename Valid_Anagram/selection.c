
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

//TODO: merge sort
void selectionSoft(char** arr)
{
    int length = strlen(*arr);

    //malloc 
    char* allocate = malloc(sizeof(char)* length + 1);

    //phải thêm thằng null nữa
    strcpy(allocate, *arr);
    
    for ( int i = 0; i < length - 1; i++ )
    {
        int minIndex = i;
        int min = allocate[i];
        for ( int j = i + 1; j < length; j++ )
        {
            if ( min > allocate[j] )
            {
                min = allocate[j];
                minIndex = j;
            }
        }

        if (i != minIndex)
        {
            allocate[minIndex] = allocate[i];
            allocate[i] = min;
        }
    }

    *arr = allocate;
}

bool compareBoth(char s[], char t[])
{
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if( (s[i] - t[i] ) != 0 )
            return false;
    }
    return true;
}


// abc abc

bool isAnagram(char* s, char* t) {
    
    int lenS = strlen(s);
    int lenT = strlen(t);

    if (lenS != lenT)
        return false;

    

    if (lenS > 0)
    {
        //soft
        selectionSoft(&s);
        selectionSoft(&t);
        return compareBoth(s, t);
    }
    return true;


}