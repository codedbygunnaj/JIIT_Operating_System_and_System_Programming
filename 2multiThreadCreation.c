//creating 5 threads:

#include<stdio.h>
#include<pthread.h>
#define NUMBER_OF_THREADS 5

void *myfun(void *arg)
{
    long tid=*(long *)arg; //converting to long pointer and then fetching value from the pointer using *
    printf("Thread id: #%ld \n",tid);
    pthread_exit(NULL);
}

int main()
{
    pthread_t myThread[NUMBER_OF_THREADS];
    printf("All threads have started.\n");
    long thread_args[NUMBER_OF_THREADS];
    for(int i=0;i<NUMBER_OF_THREADS;i++){
        thread_args[i]=i;
        pthread_create(&myThread[i],NULL,myfun,(void *)&thread_args[i]);
    }
    for(int i=0;i<NUMBER_OF_THREADS;i++){
        pthread_join(myThread[i],NULL);
    }
    printf("All threads have finished.\n");
    return 0;
}
