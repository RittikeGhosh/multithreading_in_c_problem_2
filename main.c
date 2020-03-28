#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct Data{
    int argn;
    double* arr_data;
};


void* average(void* data)
{
    struct Data* object = (struct Data*)data;
    double sum = 0, average;

    for(int i = 0; i < object->argn; i++)
        sum += object->arr_data[i];
    
    average = sum / object->argn;

    printf("THE AVERAGE VALUE IS : %g\n", average);

    return NULL;
}


void* min(void* data)
{
    struct Data* object = (struct Data*)data;

    double min = object->arr_data[0];

    for(int i = 0; i < object->argn; i++)
    {
        if(min > object->arr_data[i])
            min = object->arr_data[i];
    }

    printf("\nTHE MINIMUM VALUE IS : %g\n", min);

    return NULL;
}


void* max(void* data)
{
    struct Data* object = (struct Data*)data;

    double max = object->arr_data[0];

    for(int i = 0; i < object->argn; i++)
    {
        if(max < object->arr_data[i])
            max = object->arr_data[i];
    }

    printf("\nTHE MAXIMUM VALUE IS : %g\n", max);

    return NULL;
}


int main(int argn, char** args)
{
    printf("\nWelcome: I will help you solving the problem \n");

    struct Data object = {
        argn - 1,
        (void*)calloc(argn-1, sizeof(double))
    };

    for(int i = 1; i < argn; i++)
        object.arr_data[i-1] = strtod(args[i], NULL);

    printf("\nThe provided values are : ");
    for(int i = 0; i < argn - 1; i++)
        printf("%g ", object.arr_data[i]);
    
    printf("\n\n");

    pthread_t averageThread;
    pthread_t minThread;
    pthread_t maxThread;

    pthread_create(&averageThread, NULL, average, &object);
    pthread_create(&minThread, NULL, min, &object);
    pthread_create(&maxThread, NULL, max, &object);

    pthread_join(maxThread, NULL);
    pthread_join(minThread, NULL);
    pthread_join(averageThread, NULL);
    // getchar();
    return 0;
}