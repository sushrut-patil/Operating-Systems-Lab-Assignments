#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

pthread_mutex_t mutex;
sem_t Empty, Full;
const int Size = 5;
int Data = 100;
int BufferData[Size];
int pcount = 0, ccount = 0;

void *Consumer(void *arg)
{
    int num;
    num = *(int *)arg;

    while (true)
    {
        sem_wait(&Full);
        pthread_mutex_lock(&mutex);

        cout << "Consumer " << num << " is in critical region\n";

        cout << "Consumer " << num << " Access Buffer and Consumes Data from Buffer\n";
        cout << "Data Consumed by Consumer " << num << " is " << BufferData[ccount] << "\n";
        ccount = (ccount + 1) % Size; 
        sleep(1); 

        pthread_mutex_unlock(&mutex);
        cout << "Consumer " << num << " left critical region\n\n";

        sem_post(&Empty);
        usleep(1000); 
    }

    return NULL;
}

void *Producer(void *arg)
{
    int num;
    num = *(int *)arg;

    while (true)
    {
        sem_wait(&Empty);
        pthread_mutex_lock(&mutex);

        cout << "\nProducer " << num << " is in critical region\n";
        cout << "Producer " << num << " Access Buffer and Stores Data in Buffer\n";
        BufferData[pcount] = Data++;
        cout << "Data produced by Producer " << num << " is " << BufferData[pcount] << "\n";
        pcount = (pcount + 1) % Size; 
        sleep(1); 

        pthread_mutex_unlock(&mutex);
        cout << "Producer " << num << " left critical region\n\n";

        sem_post(&Full);
        usleep(1000); 
    }
    return NULL;
}

int main()
{
    int N;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&Empty, 0, Size);
    sem_init(&Full, 0, 0);

    cout << "Enter the number of producers and consumers: ";
    cin >> N;

    pthread_t prod[N], cons[N];

    

    int index[N];

    for (int i = 0; i < N; i++)
    {
        index[i] = i + 1;
        pthread_create(&prod[i], NULL, Producer, &index[i]);
        pthread_create(&cons[i], NULL, Consumer, &index[i]);
    }

    for (int j = 0; j < N; j++)
    {
        pthread_join(prod[j], NULL);
        pthread_join(cons[j], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
