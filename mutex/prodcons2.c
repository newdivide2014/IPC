/*
 * gcc producons2.c -lpthread
 * */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define min(x, y)       (x<y ? x:y)

#define MAXNITEMS       1000000
#define MAXNTHREADS     100

int nitems;             /* read-only by producer and consumer */

struct {
    pthread_mutex_t mutex;              //threads mutex
    int             buff[MAXNITEMS];
    int             nput;               //buff中下一次存放的元素下标
    int             nval;               //下一次存放的值
} shared = {
    PTHREAD_MUTEX_INITIALIZER
};

void *produce(void *), *consume(void *);

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Usage: prodcons2 <#items> <#threads>\n");
        return 0;
    }

    int nthreads = 0, i = 0, count[MAXNTHREADS] = {};
    pthread_t tid_produce[MAXNTHREADS] = {}, tid_consume = 0;

    nitems = min(atoi(argv[1]), MAXNITEMS);
    nthreads = min(atoi(argv[2]), MAXNTHREADS);
    
    //set_concurrenccy();

    // start all the producer threads
    for(i; i < nthreads; i++)
    {
        count[i] = 0;
        pthread_create(&tid_produce[i], NULL, produce, &count[i]);
    }
    // wati for all the producer threads
    for(i = 0; i < nthreads; i++)
    {
        pthread_join(tid_produce[i], NULL);
        printf("count[%d] = %d\n", i, count[i]);
    }

    pthread_create(&tid_consume, NULL, consume, NULL);
    pthread_join(tid_consume, NULL);

    return 0;
}


void *produce(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&shared.mutex);
        if(shared.nput >= nitems)
        {
            pthread_mutex_unlock(&shared.mutex);
            return NULL;
        }
        shared.buff[shared.nput] = shared.nval;
        shared.nput++;
        shared.nval++;
        pthread_mutex_unlock(&shared.mutex);
        *((int*)arg) += 1;
    }
}

void *consume(void *arg)
{
    int i = 0;
    for(i; i < nitems; i++)
    {
        if(shared.buff[i] != i)
        {
            printf("buff[%d] = %d\n", i, shared.buff[i]);
        }
    }
    return NULL;
}
