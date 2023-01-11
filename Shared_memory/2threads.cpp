#include <pthread.h>
#include <stdio.h>

int a=0;

void *mythread1(void* d)
{
    a++;
    printf("a = %d, thread id = %ld\n", a, pthread_self());
    return NULL;
}

void *mythread2(void* d)
{
    a++;
    printf("a = %d, thread id = %ld\n", a, pthread_self());
    return NULL;
}

int main()
{
    pthread_t thid1, thid2;
    printf("child #1\n");
    pthread_create(&thid1,(pthread_attr_t*)NULL,mythread1,NULL);
    pthread_join(thid1,(void**)NULL);
    printf("child #2\n");
    pthread_create(&thid2,(pthread_attr_t*)NULL,mythread2,NULL);
    pthread_join(thid2,(void**)NULL);
    printf("parent\n");
    a++;
    printf("a = %d, thread id = %ld\n", a, pthread_self());
}