#include <pthread.h>
#include <stdio.h>

int a = 0;

void *mythread(void *dummy)
{
    pthread_t this_thid;
    this_thid = pthread_self();
    a = a+1;
    printf("Thread %lu, Calculation result = %d\n", this_thid, a);

    if (a==2)
    {
        pthread_t child_thid;
        printf("Creating child thread inside child thread\n");
        int result = pthread_create(&child_thid, NULL, mythread, NULL);
        if(result != 0)
        {
            printf ("Error on thread create, return value = %d\n", result);
            return NULL;
        }
        pthread_join(child_thid, NULL);
        printf("child thread inside child thread ended\n");
        return NULL;
    }
    return NULL;
}

int main()
{
    pthread_t child_thid, parent_thid;
    int result;

    parent_thid = pthread_self();
    a = a+1;
    printf("Thread %lu, Calculation result = %d\n", parent_thid, a);

    printf("Creating child thread\n");
    result = pthread_create(&child_thid, NULL, mythread, NULL);
    if(result != 0)
    {
        printf ("Error on thread create, return value = %d\n", result);
        return -1;
    }
    pthread_join(child_thid, NULL);
    printf("child thread ended\n");
    return 0;
}