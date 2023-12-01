#include <pthread.h>
#include <semaphore.h>
#include <bits/stdc++.h>
using namespace std;

static const auto init = []
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return false;
}();

sem_t reader, writer;
int readerCount = 0, Data = 100;

void *Reader(void *arg)
{
    int num;
    num = *(int *)arg;
    while (true)
    {
        sem_wait(&reader);
        readerCount++;
        if (readerCount == 1)
        {
            sem_wait(&writer);
        }
        sem_post(&reader);
        cout << "Reader " + to_string(num) + " is in critical region" << endl;
        cout << "Reader " + to_string(num) + " is reading data " + to_string(Data) << endl;
        readerCount--;
        cout << "Reader " + to_string(num) + " left critical region\n"
             << endl;

        if (readerCount == 0)
        {
            sem_post(&writer);
        }
        sleep(1);
    }
    return NULL;
}

void *Writer(void *arg)
{
    int num;
    num = *(int *)arg;
    while (true)
    {
        sem_wait(&writer);
        cout << "writer " + to_string(num) + " is in critical region\n";
        Data++;
        cout << "writer " + to_string(num) + " has written data " + to_string(Data)<<"\n";
        cout << "writer " + to_string(num) + " left critical region\n"
             << endl;

        sem_post(&writer);
        sleep(1);
    }
    return NULL;
}

int main()
{
    int N;
    sem_init(&reader, 0, 1);
    sem_init(&writer, 0, 1);

    cout << "Enter the number of readers and writers" << endl;
    cin >> N;

    // Create array of  threads
    pthread_t r[N], w[N];

    int index[N];

    for (int i = 0; i < N; i++)
    {
        index[i] = i + 1;
        pthread_create(&w[i], NULL, Writer, &index[i]);
        pthread_create(&r[i], NULL, Reader, &index[i]);
    }

    for (int j = 0; j < N; j++)
    {
        pthread_join(w[j], NULL);
        pthread_join(r[j], NULL);
    }

    sem_destroy(&reader);
    sem_destroy(&writer);

    return 0;
}