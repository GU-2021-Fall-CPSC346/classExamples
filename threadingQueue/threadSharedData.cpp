#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */
#include <stdlib.h>

struct ArrData {
    int values[10];
    int valueCount;
    int threadID;
};

/* function to be executed by the new thread */
void* workerThread(void* vargs)
{
    struct ArrData* data = (struct ArrData*)vargs;
    pthread_t myID = pthread_self();

    pthread_detach(pthread_self());
    printf("Hello from new thread - got %d\n", (int)myID);

    //printf("%d", data->valueCount);
    for(int i = 0; i < data->valueCount; i++) {
        printf("%d ", data->values[i]);
    }
    printf("\n");

    while(true) {
        // Write all to my ID
        for(int i = 0; i < data->valueCount; i++) {
            data->values[i] = (int)myID;
        }
        // Read out all

        for(int i = 0; i < data->valueCount; i++) {
            printf("%d ", data->values[i]);
            if( data->values[i] != (int)myID ) {
                printf("ERROR IN DATA!\n");
                exit(0);
            }
        }
        printf("\n");
    }


    pthread_exit(NULL);			/* terminate the thread */
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
    int        rc;         	/* return value                           */
    pthread_t  thread_id;     	/* thread's ID (just an integer)          */
    pthread_t  thread_id2;     	/* thread's ID (just an integer)          */
    int        t         = 11;  /* data passed to the new thread          */

    struct ArrData *data = (struct ArrData *)malloc(sizeof(struct ArrData));

    data->threadID = 5;

    data->valueCount = 10;
    for(int i = 0; i < data->valueCount; i++) {
        data->values[i] = i;
    }


    rc = pthread_create(&thread_id, NULL, workerThread, (void*)data);
    rc = pthread_create(&thread_id2, NULL, workerThread, (void*)data);

    printf("\n Created new thread (%u) ... \n", (int)thread_id);
    printf("\n Created new thread2 (%u) ... \n", (int)thread_id2);

    pthread_join(thread_id, NULL);
    pthread_exit(NULL);		/* terminate the thread */
}
