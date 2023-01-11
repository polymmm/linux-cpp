#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int msqid=msgget(ftok("lab631.cpp",0),0666 | IPC_CREAT), len;
    struct buf
    {
        long mtype;
        int  mnum1;
        float mnum2;
    } mybuf;

    while (true)
    {
        msgrcv(msqid, (struct msgbuf*) &mybuf, 81, 0, 0);
        if (mybuf.mtype==255)
        {
            msgctl(msqid, IPC_RMID, (struct msqid_ds*) NULL);
            exit(0);
        }
        printf("message type = %ld, info = %d %.1f\n", mybuf.mtype, mybuf.mnum1, mybuf.mnum2);
        mybuf.mtype=2;
        mybuf.mnum1=33;
        mybuf.mnum2=55.5;
        len=sizeof(mybuf.mnum1)+sizeof(mybuf.mnum2)+1;
        msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0);
    }
}