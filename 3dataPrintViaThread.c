#include<stdio.h>
#include<pthread.h>
#define NUM_OF_THREAD 2
struct details
{
    char name[50];
    int hallNum;
    int empId;
    char branch[50];
};
void * myFun(void *arg)
{
    struct details *emp_details=(struct details*)arg;
    printf("\n--- Employee Details ---\n");
    printf("Name: %s\n", emp_details->name);
    printf("Hall No.: %d\n", emp_details->hallNum);
    printf("Employee ID: %d\n", emp_details->empId);
    printf("Branch: %s\n", emp_details->branch);
    printf("-----------------------\n");
    pthread_exit(NULL);
}
int main()
{
    pthread_t myThreads[NUM_OF_THREAD];
    struct details val[NUM_OF_THREAD];
    strcpy(val[0].name, "Arjun Sharma");
    val[0].hallNum = 101;
    val[0].empId = 12345;
    strcpy(val[0].branch, "Computer Science");

    // Data for the second thread/employee
    strcpy(val[1].name, "Priya Singh");
    val[1].hallNum = 202;
    val[1].empId = 67890;
    strcpy(val[1].branch, "Electronics");
    for(int i=0;i<NUM_OF_THREAD;i++){
        pthread_create(&myThreads[i],NULL,myFun,(void *)&val[i]);
    }

    for(int i = 0; i < NUM_OF_THREAD; i++){
        pthread_join(myThreads[i], NULL);
    }
    printf("All threads have finished their work.\n");
    return 0;
}
