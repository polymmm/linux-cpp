#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int msqid=msgget(ftok("lab631.cpp",0),0666 | IPC_CREAT), len;
    struct buf
    {
        long mtype;
        int mnum1;
        float mnum2;
    } mybuf;

    mybuf.mtype=1;
    mybuf.mnum1=44;
    mybuf.mnum2=22.2;
    len=sizeof(mybuf.mnum1)+sizeof(mybuf.mnum2)+1;
    msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0);

    msgrcv(msqid, (struct msgbuf*) &mybuf, 81, 2, 0);
    printf("message type = %ld, info = %d %.1f\n", mybuf.mtype, mybuf.mnum1, mybuf.mnum2);

    mybuf.mtype=255;
    len=0;
    msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0);
    exit(0);
}