#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int msqid=msgget(ftok("transm1.cpp",0),0666 | IPC_CREAT), maxlen=81;
    struct buf
    {
        long mtype;
        int  mnum1;
        float mnum2;
    } mybuf;

    while (true)
    {
        msgrcv(msqid, (struct msgbuf*) &mybuf, maxlen, 0, 0);
        if (mybuf.mtype==255)
        {
            msgctl(msqid, IPC_RMID, (struct msqid_ds*) NULL);
            exit(0);
        }
        printf("message type = %ld, info = %d %.1f\n", mybuf.mtype, mybuf.mnum1, mybuf.mnum2);
    }
}