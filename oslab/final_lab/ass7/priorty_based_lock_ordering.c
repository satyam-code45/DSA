#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Number of distinct resources
#define NUM_RESOURCES 3

// Global array of mutexes representing resources R0, R1, R2...
pthread_mutex_t resource_mutex[NUM_RESOURCES];

// Structure to pass to each thread
typedef struct {
    int thread_id;
    int needed_resources[NUM_RESOURCES];
    int count;
} thread_info_t;

// Comparator for qsort: ascending order
int cmp_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);  // Dereference the pointers
}

void* thread_func(void* arg) {
    thread_info_t *info = (thread_info_t*)arg;  // Cast to pointer to struct

    // Sort resource IDs to enforce ascending lock order
    qsort(info->needed_resources, info->count, sizeof(int), cmp_int);

    printf("Thread %d requesting resources:", info->thread_id);
    for (int i = 0; i < info->count; i++) {
        printf(" R%d", info->needed_resources[i]);
    }
    printf("\n");

    // Acquire locks in ascending order
    for (int i = 0; i < info->count; i++) {
        int r = info->needed_resources[i];
        pthread_mutex_lock(&resource_mutex[r]);
        printf("Thread %d acquired R%d\n", info->thread_id, r);
    }

    // --- Critical section simulating work ---
    printf("Thread %d in critical section\n", info->thread_id);

    // Release locks in reverse order
    for (int i = info->count - 1; i >= 0; i--) {
        int r = info->needed_resources[i];
        pthread_mutex_unlock(&resource_mutex[r]);
        printf("Thread %d released R%d\n", info->thread_id, r);
    }

    return NULL;
}

int main() {
    pthread_t threads[2];
    thread_info_t infos[2] = {
        { .thread_id = 1, .needed_resources = {2, 0}, .count = 2 },
        { .thread_id = 2, .needed_resources = {1, 0}, .count = 2 }
    };

    // Initialize all resource mutexes
    for (int i = 0; i < NUM_RESOURCES; i++) {
        pthread_mutex_init(&resource_mutex[i], NULL);
    }

    // Create threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_func, &infos[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_RESOURCES; i++) {
        pthread_mutex_destroy(&resource_mutex[i]);
    }

    printf("All threads completed without deadlock.\n");
    return 0;
}
