#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int msqid=msgget(ftok("transm1.cpp",0),0666 | IPC_CREAT), len;
    struct buf
    {
        long mtype;
        int pid;
    } mybuf;

    mybuf.mtype=1;
    mybuf.pid=getpid();
    len=sizeof(mybuf.pid)+1;
    msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0);

    msgrcv(msqid, (struct msgbuf*) &mybuf, 81, mybuf.pid, 0);
    printf("Response: Your PID is = %ld\n", mybuf.mtype);

    exit(0);
}