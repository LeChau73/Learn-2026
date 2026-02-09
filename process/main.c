#include <stdio.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 10
typedef struct
{
    char data[10];
}item;

item buffer[BUF_SIZE];
int in = 0;
int out = 0;

int main(int argc, char* argv[]) {

    //first create share mem
    
    int fd;
    char path[10];
    strcat(path, "/shm_7224");
    //sprintf(path, "/shm_7224", getpid());
    printf("path = %s\n", path);
    // Cretate the shared mem object 
    fd = shm_open(path, O_CREAT | O_RDWR, 0600);
    printf("fd = %d\n", fd);
    if(fd == -1) {
        err(1, "shm_open");
    }
    //Set size for file conpreent to struct item
    int size = sizeof(item) * BUF_SIZE;
    int status = ftruncate(fd, size);

    if(status == -1) {
        err(1, "ftruncate");
    }

    //addr: first addr
    //lenghth : mength of mapping
    //
    item* ptr = mmap(NULL, size, PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0);
    if(ptr != MAP_FAILED) {
        strcpy(ptr[0].data, "Test");
    }

    item next_produced;
    strcpy(next_produced.data, "item ");
    int count = 0;

    while (1)
    {
        //full then wait
        while( ( ( in + 1 ) % BUF_SIZE ) == out );
        count++;
        char buf[10];
        snprintf(buf, sizeof(buf), "%d", count);

        int j = 4;
        while( buf[j - 4] != '\0')
            next_produced.data[j++] = buf[j -4];
        //produce an item

        buffer[in] = next_produced;

        j = 4;
        while(next_produced.data[j] != '\0')
            next_produced.data[j++] = 0x20;

        printf("Produced: %s\n", buffer[in].data);
        in = (in + 1) % BUF_SIZE;
        memcpy(ptr, buffer, 100);
        //strcpy(ptr, buffer);
        printf("Share mem current \n");
        printf("ptr = %s\n ", ptr);
        
        sleep(5);
    }
    

    return 0;
}