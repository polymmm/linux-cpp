#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char *array;
    int shmid;
    key_t key=ftok("mem_writer.cpp",0);
    if((shmid=shmget(key,100*sizeof(int),0666|IPC_CREAT|IPC_EXCL))<0)
    {
        if (errno == EEXIST)
        {
            shmid=shmget(key,3*sizeof(int),0);
        }
    }

    array=(char*)shmat(shmid,NULL,0);
    int i=0;
    while(array[i])
    {
        printf("%c",array[i]);
        i++;
    }
    shmdt(array);
}