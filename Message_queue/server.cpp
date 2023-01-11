#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int msqid=msgget(ftok("transm1.cpp",0),0666 | IPC_CREAT), len;
    struct buf
    {
        long mtype;
        int  pid;
    } mybuf;

    while (true)
    {
        msgrcv(msqid, (struct msgbuf*) &mybuf, 81, 1, 0);
        mybuf.mtype=mybuf.pid;
        len=sizeof(mybuf.pid)+1;
        msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0);
    }
}