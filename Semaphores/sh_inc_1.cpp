#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <iostream>

int main()
{
    int shmid,semid,need=1;
    int *array;
    struct sembuf buf;
    key_t key=ftok("sh_inc_1.cpp",0);

    semid=semget(key,1,0666|IPC_CREAT);
    buf.sem_op=-1;
    buf.sem_flg=0;
    buf.sem_num=0;
    semop(semid,&buf,1);

    if((shmid=shmget(key,3*sizeof(int),0666|IPC_CREAT|IPC_EXCL))<0)
        if(errno==EEXIST)
        {
            shmid=shmget(key,3*sizeof(int),0);
            need=0;
        }

    array=(int*)shmat(shmid,NULL,0);

    if(need)
    {
        array[0]=1;
        array[1]=0;
        array[2]=1;
    }
    else
    {
        array[0]+=1;
        for(int i=0;i<10000000;i++)
        {
            array[2]+=1;
        }
    }

    printf( "IT WORKS!\n");
    printf( "%d %d %d",array[0] ,array[1],array[2]);
}