#include<stdio.h>
#include<pthread.h>

int bal=1000;
pthread_mutex_t balMutex;

void * deposit(void *arg)
{
    for(int i=0;i<50;i++){
        pthread_mutex_lock(&balMutex);
        bal+=50;
        pthread_mutex_unlock(&balMutex);
    }
    return NULL;
}

void * withdraw(void *arg)
{
    for(int i=0;i<20;i++){
        pthread_mutex_lock(&balMutex);
        bal-=20;
        pthread_mutex_unlock(&balMutex);
    }
    return NULL;
}

int main()
{
    pthread_t t1,t2;
    pthread_mutex_init(&balMutex,NULL);

    pthread_create(&t1,NULL,deposit,NULL);
    pthread_create(&t2,NULL,withdraw,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&balMutex);
    printf("Final balance is: %d\n", bal);
    return 0;
}
