#include <sys/stat.h>
#include <stdio.h>
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
    int fd=open("mem_writer.cpp",O_RDONLY);
    while(read(fd,&array[i],1))
    {
        i++;
    }
    shmdt(array);
}