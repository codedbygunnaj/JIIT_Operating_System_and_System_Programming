#include <stdio.h>
#include <pthread.h>

// --- Shared Global Resources ---
int account = 1000;
pthread_mutex_t account_mutex;
pthread_cond_t account_cond;

// --- Deposit Function (The "Signaler") ---
void deposit(int amount) {
    // 1. Lock the mutex to get exclusive access
    pthread_mutex_lock(&account_mutex);

    // 2. Perform the deposit
    account += amount;
    printf("Deposited %d, new balance is %d\n", amount, account);

    // 3. Signal waiting threads that the condition might now be true
    pthread_cond_signal(&account_cond);

    // 4. Unlock the mutex
    pthread_mutex_unlock(&account_mutex);
}

// --- Withdrawal Function (The "Waiter") ---
void withdrawal(int amount) {
    // 1. Lock the mutex to get exclusive access
    pthread_mutex_lock(&account_mutex);

    // 2. Use a 'while' loop to wait for the condition
    while (account < 1000) {
        printf("Balance is %d. Not enough to withdraw. Waiting...\n", account);
        // This atomically unlocks the mutex and puts the thread to sleep
        pthread_cond_wait(&account_cond, &account_mutex);
        // When woken up, it re-locks the mutex and checks the condition again
    }

    // 3. Perform the withdrawal
    account -= amount;
    printf("Withdrew %d, new balance is %d\n", amount, account);

    // 4. Unlock the mutex
    pthread_mutex_unlock(&account_mutex);
}

// --- Thread functions to call deposit/withdrawal ---
void *depositor_thread(void *arg) {
    deposit(200);
    return NULL;
}

void *withdrawer_thread(void *arg) {
    withdrawal(500);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutex and condition variable
    pthread_mutex_init(&account_mutex, NULL);
    pthread_cond_init(&account_cond, NULL);
    
    // To test the waiting condition, let's start with a low balance
    account = 800;
    printf("Starting balance is %d\n", account);

    // Create the threads
    pthread_create(&thread1, NULL, withdrawer_thread, NULL);
    pthread_create(&thread2, NULL, depositor_thread, NULL);

    // Join the threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex and condition variable
    pthread_mutex_destroy(&account_mutex);
    pthread_cond_destroy(&account_cond);

    printf("Final balance is: %d\n", account);
    return 0;
}