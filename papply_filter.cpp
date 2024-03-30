#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <time.h>

using namespace std;
long thread_size;
int **image;
int **Mask;
int mask_size;
int image_row, image_column;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int flag_Sync = 0;
ofstream output;

void *applyKernel(void *rank)
{
    struct timespec s, e;
    double TimeElapsed;
    clock_gettime(CLOCK_MONOTONIC, &s);

    long myrank = (long)rank;
    long data = (image_row / thread_size);
    long start = myrank * data;
    long stop = myrank * data + data;
    for (int i = start; i < stop; i++)
    {
        for (int j = 0; j < image_column; j++)
        {
            int sum = 0;
            for (int k = 0; k < mask_size; k++)
            {
                for (int l = 0; l < mask_size; l++)
                {
                    int a = (i + k) % image_row;
                    int b = (j + l) % image_column;

                    sum += image[a][b] * Mask[k][l];
                }
            }
            image[i][j] = sum;
        }
    }

    while (flag_Sync != myrank)
        ;
    pthread_mutex_lock(&mutex);

    for (int i = start; i < stop; i++)
    {
        for (int j = 0; j < image_column; j++)
            output << image[i][j] << " ";
        output << "\n";
    }

    flag_Sync++;
    pthread_mutex_unlock(&mutex);
    clock_gettime(CLOCK_MONOTONIC, &e);
    TimeElapsed = (e.tv_nsec - s.tv_nsec) * (1e+6);

    cout << "Rank " << rank << " Start " << start << " elapsed " << TimeElapsed << endl;

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cerr << argv[0] << " Error argv " << endl;
        return 1;
    }
    pthread_t threads[12];

    string inputFile = argv[1];
    string _maskFile = argv[2];
    string outputFile = argv[3];
    thread_size = stoul(argv[4]);

    output.open(outputFile);

    ifstream input(inputFile);
    input >> image_row;
    input >> image_column;
    output << image_row;
    output << image_column;
    image = new int *[image_row];
    for (int i = 0; i < image_row; i++)
        image[i] = new int[image_column];

    for (int i = 0; i < image_row; i++)
    {
        for (int j = 0; j < image_column; j++)
            input >> image[i][j];
    }
    input.close();

    ifstream maskFile(_maskFile);
    maskFile >> mask_size;
    Mask = new int *[mask_size];
    for (int i = 0; i < mask_size; i++)
        Mask[i] = new int[mask_size];
    for (int i = 0; i < mask_size; i++)
    {
        for (int j = 0; j < mask_size; j++)
            maskFile >> Mask[i][j];
    }

    for (long rank = 0; rank < thread_size; rank++)
    {
        int status = pthread_create(&threads[rank], NULL, &applyKernel, (void *)rank);

    }
    for (long t = 0; t < thread_size; t++)
    {
        pthread_join(threads[t], NULL);
    }
    // output<<image_row;//y

    output.close();

    for (int i = image_row - 1; i >= 0; i--)
        delete[] image[i];
    for (int i = mask_size - 1; i >= 0; i--)
        delete[] Mask[i];
    delete[] image;
    delete[] Mask;
    image = NULL;
    Mask = NULL;

    return 0;
}
