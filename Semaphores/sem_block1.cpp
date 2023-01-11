#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>

int main()
{
    int semid;
    struct sembuf buf;

    semid=semget(ftok("sem_block1.cpp",0),1,0666|IPC_CREAT);
    buf.sem_op=-5;
    buf.sem_flg=0;
    buf.sem_num=0;
    semop(semid,&buf,1);
    printf("You did it 5 times\n IT WORKS!\n");
}