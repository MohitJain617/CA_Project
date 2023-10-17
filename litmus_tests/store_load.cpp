#include <iostream>
#include <pthread.h>
#include <random>
#include <semaphore.h>
#include <stdio.h>

// Thread safe random number generator
int randInt(const int & min, const int & max) {
    thread_local static std::random_device rd;
    thread_local static std::mt19937 rng(rd());
    thread_local std::uniform_int_distribution<int> distribution(min,max);
    return distribution(rng);
}

//-------------------------------------
//  Store Load reordering litmus test
//-------------------------------------
sem_t beginSem1;
sem_t beginSem2;
sem_t endSem;

int X, Y;
int r1, r2;

void *thread1Func(void *param)
{
    while (1)
    {
        sem_wait(&beginSem1);  // Wait for signal
        while (randInt(0,7) != 1) {}  // Random delay

        // *********************
        X = 1;  // Store X=1

        asm volatile("" ::: "memory");  // Prevent compiler reordering

        r1 = Y;  // Load Y -> R1
        // *********************

        sem_post(&endSem);
    }
    return NULL;
};

void *thread2Func(void *param)
{
    while (1)
    {
        sem_wait(&beginSem2);  // Wait for signal
        while (randInt(0,7) != 1 ) {}  // Random delay

        // *********************
        Y = 1;  // Store Y = 1

        asm volatile("" ::: "memory");  // Prevent compiler reordering

        r2 = X; // Load X -> R2
        // *********************

        sem_post(&endSem);
    }
    return NULL;
};

int main()
{
    // Initialize Semaphores, so that threads run in a syncrhonized fashion
    sem_init(&endSem, 0, 0);
    sem_init(&beginSem1, 0, 0);
    sem_init(&beginSem2, 0, 0);

    // Spawn threads
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread1Func, NULL);
    pthread_create(&thread2, NULL, thread2Func, NULL);

    // Repeat the experiment until interrupt
    int detected = 0;
    for (int itr = 1; ; itr++)
    {
        // Reset X and Y
        X = 0; Y = 0;

        // Unlock both threads
        sem_post(&beginSem1);
        sem_post(&beginSem2);

        // Wait for threads to execute
        sem_wait(&endSem);
        sem_wait(&endSem);

        // Check for reordering
        if (r1 == 0 && r2 == 0)
        {
            detected++;
			std::cout << detected <<" reorders found after " << itr << " iterations\n";
        }
    }
    return 0;
}
