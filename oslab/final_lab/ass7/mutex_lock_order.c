#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>  // For intptr_t

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* arg) {
    int id = (int)(intptr_t)arg;  // Safe casting from void* to int
    // Acquire locks in fixed order
    pthread_mutex_lock(&mutex1);
    printf("Thread %d acquired mutex1\n", id);

    pthread_mutex_lock(&mutex2);
    printf("Thread %d acquired mutex2\n", id);

    // Critical section
    printf("Thread %d in critical section\n", id);

    // Release locks in reverse order
    pthread_mutex_unlock(&mutex2);
    printf("Thread %d released mutex2\n", id);

    pthread_mutex_unlock(&mutex1);
    printf("Thread %d released mutex1\n", id);

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // Create threads and pass IDs safely
    pthread_create(&t1, NULL, thread_func, (void*)(intptr_t)id1);
    pthread_create(&t2, NULL, thread_func, (void*)(intptr_t)id2);

    // Wait for threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
