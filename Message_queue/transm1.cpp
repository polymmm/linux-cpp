#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int msqid=msgget(ftok("transm1.cpp",0),0666 | IPC_CREAT), len;
    struct buf
    {
        long mtype;
        int mnum1;
        float mnum2;
    } mybuf;

    for (int i=0;i<5;i++)
    {
        mybuf.mtype=1;
        mybuf.mnum1=44;
        mybuf.mnum2=22.2;
        len=sizeof(mybuf.mnum1)+sizeof(mybuf.mnum2)+1;
        msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0);
    }
    mybuf.mtype=255;
    len=0;
    msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0);
}