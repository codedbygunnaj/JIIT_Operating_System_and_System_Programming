#include<stdio.h>
#include<pthread.h>
void *myFun(void *arg)
{
    printf("This is a thread, bbg\n");
    return NULL;
}
int main()
{
    pthread_t tid;
    printf("Entering thread function: \n");
    pthread_create(&tid,NULL,myFun,NULL);
    pthread_join(tid,NULL);
    printf("Exiting thread function...\n");
    return 0;
}
