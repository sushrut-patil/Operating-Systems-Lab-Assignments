#include <bits/stdc++.h>
using namespace std;

/*
 Reader-Writer Problem of synchronization
*/
pthread_mutex_t writer, reader;
int readerCount = 0, Data = 100;

void *Reader(void *arg)
{
    int num;
    num = *(int *)arg;
    while (true)
    {
        pthread_mutex_lock(&reader);
        readerCount++;
        if (readerCount == 1)
        {
            pthread_mutex_lock(&writer);
        }
        pthread_mutex_unlock(&reader);
        cout << "Reader " << num << " is in critical region\n";
        cout << "Reader " << num << " is reading data " << Data << "\n";
        readerCount--;
        cout << "Reader " << num << " left critical region\n"
             << endl;
        if (readerCount == 0)
        {
            pthread_mutex_unlock(&writer);
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
        pthread_mutex_lock(&writer);
        
        cout << "writer " << num << " is in critical region \n";
        Data++;
        cout << "writer " << num << " has written data " << Data << "\n";
        cout << "writer " << num << " left critical region\n"
             << endl;
        pthread_mutex_unlock(&writer);
        sleep(1);
    }
    return NULL;
}

int main()
{
    int N;

    pthread_mutex_init(&writer, NULL);
    pthread_mutex_init(&reader, NULL);

    cout << "Enter the number of readers and writers : "
         << endl;
    cin >> N;

    // Create array of  threads
    pthread_t r[N], w[N];
    int index[N];
    for (int i = 0; i < N; i++)
    {
        index[i] = i + 1;
        pthread_create(&r[i], NULL, Reader, &index[i]);
        pthread_create(&w[i], NULL, Writer, &index[i]);
    }

    for (int j = 0; j < N; j++)
    {
        pthread_join(w[j], NULL);
        pthread_join(r[j], NULL);
    }

    pthread_mutex_destroy(&reader);
    pthread_mutex_destroy(&writer);
    return 0;
}