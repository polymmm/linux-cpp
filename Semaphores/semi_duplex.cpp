#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/sem.h>

int main()
{
    int fd[2];
    char string[15];
    int semid=semget(ftok("semi_duplex.cpp",0),1,0666|IPC_CREAT);
    struct sembuf buf;

    buf.sem_flg=0;
    buf.sem_num=0;

    pipe(fd);

    if (fork())
    {
        for(int count_p=6; count_p<15;count_p+=2)
        {
            memset(string, 0, sizeof(string));
            write(fd[1], "abcde0123456789", count_p);

            buf.sem_op=-1;
            semop(semid,&buf,1);

            read(fd[0],string,15);
            printf("%s\n",string);
        }
    }
    else
    {
        for(int count_c=7; count_c<16;count_c+=2)
        {
            read(fd[0],string,15);
            printf("%s\n",string);
            memset(string, 0, sizeof(string));
            write(fd[1], "abcde0123456789", count_c);

            buf.sem_op=1;
            semop(semid,&buf,1);
        }
    }
}