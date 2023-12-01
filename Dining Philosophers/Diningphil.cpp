#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

static const auto init = []{
 std::ios_base::sync_with_stdio(false);
 std::cin.tie(nullptr);
 std::cout.tie(nullptr);
 return false;
}();


const int NUM_PHILOSOPHERS = 5;
pthread_mutex_t forks[NUM_PHILOSOPHERS];
sem_t sem;

void *philosopher(void *arg) {
    int id = *((int *)arg);
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        cout << "Philosopher " + to_string(id) +  " is thinking" << endl;
        sleep(3); 

        sem_wait(&sem); 
        pthread_mutex_lock(&forks[left_fork]); 
        pthread_mutex_lock(&forks[right_fork]); 
        sem_post(&sem); 

        cout << "\nPhilosopher " + to_string(id) + " accquired " + to_string(left_fork) + " and " + to_string(right_fork) +" is eating" << endl;
        cout << "\nPhilosopher " + to_string(id) + " is eating" << endl;
        sleep(5); 

        pthread_mutex_unlock(&forks[left_fork]); 
        pthread_mutex_unlock(&forks[right_fork]); 
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    sem_init(&sem, 0, NUM_PHILOSOPHERS - 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
        
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    sem_destroy(&sem);

    return 0;
}
