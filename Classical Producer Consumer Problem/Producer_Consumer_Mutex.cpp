#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

pthread_mutex_t mutex;
int Data = 100, pcount = 0,ccount=0;
const int Size = 5;
int BufferData[Size];

void *Consumer(void *arg)
{
    int num;
    num = *(int *)arg;

    pthread_mutex_lock(&mutex);
    cout << "Consumer "<< num <<" is in critical region\n";
    if (pcount > 0)
    {
        cout << "Consumer  "<< num <<" Access Buffer and Consumes Data from Buffer\n";
        cout << "Data Consumed by Consumer  "<< num << " is " << BufferData[ccount] << "\n";
        ccount++;
        sleep(1); // simulate work
        pthread_mutex_unlock(&mutex);
    }
    else
    {
        cout << "Buffer is EMPTY"
             << "\n";
        pthread_mutex_unlock(&mutex);
    }
    cout << "Consumer "<< num <<" left critical region\n"
         << endl;
    return NULL;
}

void *Producer(void *arg)
{
    int num;
    num = *(int *)arg;

    pthread_mutex_lock(&mutex);
    cout << "Producer  "<< num <<" is in critical region\n";
    if (pcount < Size)
    {
        cout << "Producer "<< num <<"  Access Buffer and Stores Data in Buffer\n";
        BufferData[pcount] = Data++;
        cout << "Data produced by Producer "<< num <<" is " << BufferData[pcount] << "\n";
        pcount++;
        sleep(1); // simulate work
        pthread_mutex_unlock(&mutex);
    }
    else
    {
        cout << "Buffer is FUll"
             << "\n";
        pthread_mutex_unlock(&mutex);
    }
    cout << "Producer  "<< num <<" left critical region\n"
         << endl;
    return NULL;
}

int main()
{
    int N;
    // Intialize mutex
    pthread_mutex_init(&mutex, NULL);

    cout << "Enter the number of readers and writers"
         << endl;
    cin >> N;

    // Declare Threads
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