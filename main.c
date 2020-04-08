#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_STRING_LEN 20
typedef long double l_double;
typedef unsigned long long int ull_int;

void* average(void* data);
void* max(void* data);
void* min(void* data);

struct Data{
    ull_int argn;
    l_double* arr_data;
};


void* average(void* data)
{
    struct Data* object = (struct Data*)data;
    l_double sum = 0, average;

    for(ull_int i = 0; i < object->argn; i++)
        sum += object->arr_data[i];

    average = sum / object->argn;

    printf("\nTHE AVERAGE VALUE IS : %0.3Lf", average);
    return NULL;
}


void* min(void* data)
{
    struct Data* object = (struct Data*)data;
    l_double min = object->arr_data[0];

    for(ull_int i = 0; i < object->argn; i++)
    {
        if(min > object->arr_data[i])
            min = object->arr_data[i];
    }

    printf("\nTHE MINIMUM VALUE IS : %0.3Lf", min);
    return NULL;
}


void* max(void* data)
{
    struct Data* object = (struct Data*)data;
    l_double max = object->arr_data[0];

    for(ull_int i = 0; i < object->argn; i++)
    {
        if(max < object->arr_data[i])
            max = object->arr_data[i];
    }

    printf("\nTHE MAXIMUM VALUE IS : %0.3Lf", max);
    return NULL;
}


int main(ull_int argn, char** args)
{
    // welcome message
    system("clear");
    printf("\n#######################################################################");
    printf("\n#                                                                     #");
    printf("\n#            Welcome: I will help you solving the problem             #");
    printf("\n#       I will calculate the MIN, MAX and AVERAGE with threads        #");
    printf("\n#                             :-> :-) :->                             #");
    printf("\n#                                                                     #");
    printf("\n#######################################################################");
    printf("\n\n");
    // check for user input in the execution line
    if (argn == 1)
    {
	printf("It seems that you did not pass any number.\n");
	printf("[You can pass the data(seperated with space) in the execution line of the application]\n");
	printf("Like this ==> ./a.out [[arg1] [arg2] [...]]\n");
	printf("But don't worry I can help you... You can give the data here too.\n\n");
    // ask user for continue to provide input now
	fflush(stdin);
	    
	do{
	   char choice = 'y';
	   printf("Do you want to give inputs now ?(y/n)  ");
	   scanf(" %c",&choice);
	   if(choice == 'n')
	   	goto end;
	   else if(choice == 'y')
		break;
	}while(1);

	printf("\n");
    	printf("Enter the number of data elements to be entered : ");
	scanf("%llu", &argn);
	++argn;

	// initializing args
	args = (void*)malloc(argn * sizeof(char*));
	for(ull_int i = 0; i < argn; i++)
	    args[i] = (void*)malloc(MAX_STRING_LEN * sizeof(char));

	printf("\n[Enter the numbers adjacent to the staments](MAX DIGIT COUNT = 20)\n");
	for (ull_int i = 1; i<argn; i++)
	{
	    printf("Enter the element %llu : ", i);
	    scanf("%s", args[i]);
	}
    }
    // create instance of the struct Data
    struct Data object = {
        argn - 1,
        (void*)calloc(argn-1, sizeof(l_double))
    };

    for(ull_int i = 1; i < argn; i++)
        object.arr_data[i-1] = strtold(args[i], NULL);

    printf("\n*The provided values(rounded to 3 decimal values) are : \n=> [ ");
    for(ull_int i = 0; i < argn - 1; i++)
        printf("%0.3Lf ,", object.arr_data[i]);
    printf("\b]\n\n");

    pthread_t averageThread, minThread, maxThread;
    pthread_create(&averageThread, NULL, average, &object);
    pthread_create(&minThread, NULL, min, &object);
    pthread_create(&maxThread, NULL, max, &object);
    pthread_join(maxThread, NULL);
    pthread_join(minThread, NULL);
    pthread_join(averageThread, NULL);
    printf("\n(The values are rounded to 3 decimal values)");

    end:
    printf("\n\nThank You for your visit :-) :-> \n");
    printf("\n");
    getchar();
    return 0;
}
