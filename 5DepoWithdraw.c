 #include <pthread.h>
 #include <iostream>
 using namespace std;
 int balance = 1000;
 pthread_mutex_t lock;
 pthread_cond_t cond;
 bool deposit_done = false;
 // Thread 1: Deposits 50, 50 times
 void* depositThread(void* arg) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < 50; i++) {
        balance += 50;
        cout << "Deposited 
    }
    deposit_done = true;
 50, Balance: " << balance << endl;
    pthread_cond_signal(&cond);  // Signal withdrawal thread to start
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
 }
 // Thread 2: Withdraws 20, 20 times
 void* withdrawThread(void* arg) {
    pthread_mutex_lock(&lock);
    while (!deposit_done) {
        pthread_cond_wait(&cond, &lock);  // Wait until deposit is done
    }
    for (int i = 0; i < 20; i++) {
        balance -= 20;
    }
    cout << "Final Balance after withdrawals: " << balance << endl;
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
 }
 int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&t1, NULL, depositThread, NULL);
    pthread_create(&t2, NULL, withdrawThread, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
 }