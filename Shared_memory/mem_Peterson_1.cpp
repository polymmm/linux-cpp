#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>

int main()
{
    int *array;
    int pid=0;
    key_t key=ftok("mem_Peterson_1.cpp",0);

    int shmid=shmget(key,6*sizeof(int),0666|IPC_CREAT|IPC_EXCL),need=1;
    if (shmid<0)
        if (errno == EEXIST)
        {
            shmid=shmget(key,4*sizeof(int),0);
            need=0;
        }

    array=(int*)shmat(shmid,NULL,0);

    if(need)
    {
        array[0]=1;
        array[1]=0;
        array[2]=1;
        array[3]=0;
    }
    else
    {
        array[4]=1;
        while(array[3])
            sleep(2);
        if(!array[3] && array[4])
        {
            array[0]+=1;
            for(int i=0;i<1000000000;i++)
            {
                array[2]+=1;
            }
            array[3]=1;
            array[4]=0;
        }
    }

    printf("%d %d %ld", array[0],array[1],array[2]);
    shmdt(array);
}