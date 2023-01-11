#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    int *array;
    key_t key=ftok("4.cpp",0);

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
        array[0]=0;
        array[1]=1;
        array[2]=1;
        array[3]=1;
    }
    else
    {
        array[5]=1;
        while(!array[3])
            sleep(2);
        if(array[3] && array[5])
        {
            array[1]+=1;
            for(int i=0;i<1000000000;i++)
            {
                array[2]+=1;
            }
        }
        array[3]=0;
        array[5]=0;
    }
    shmdt(array);
}