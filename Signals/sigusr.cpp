#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <signal.h>
#include <string.h>

int semid;
struct sembuf buf;

void locker(int sig)
{
    buf.sem_op=-1;
    semop(semid,&buf,1);
}

void unlocker(int sig)
{
    buf.sem_op=1;
    semop(semid,&buf,1);
}

int main()
{
    signal(SIGUSR1,locker);
    signal(SIGUSR2,unlocker);
    semid = semget(ftok("7-8.c",0),1,0666|IPC_CREAT);
    int fd[2];
    char string[15];

    buf.sem_flg=0;
    buf.sem_num=0;

    pipe(fd);

    if (fork())
    {
        for(int count_p=6; count_p<15;count_p+=2)
        {
            memset(string, 0, sizeof(string));
            write(fd[1], "Test01234567891", count_p);

            kill(getpid(),SIGUSR1);

            read(fd[0],string,15);
            printf("%s\n", string);
        }
    }
    else
    {
        for(int count_c=7; count_c<16;count_c+=2)
        {
            read(fd[0],string,15);
            printf("%s\n", string);
            memset(string, 0, sizeof(string));
            write(fd[1], "Test01234567891", count_c);

            kill(getpid(),SIGUSR2);
        }
    }
}