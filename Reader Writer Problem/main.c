//
//  main.c
//  Reader Writer Problem
//
//  Created by Devang Papinwar on 29/09/21.
//


#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

// creation of two semaphores
sem_t x,y;

int readercount = 0;

//MARK: Reader Represention
void *reader(void* param)
{
    sem_wait(&x);
    readercount++;
    if(readercount==1)
        sem_wait(&y);
    sem_post(&x);
    printf("%d reader is inside\n",*((int *)param));
    
    sem_wait(&x);
    readercount--;
    if(readercount==0)
    {
        sem_post(&y);
    }
    sem_post(&x);
    printf("%d Reader is leaving\n",*((int *)param));
    return NULL;
}

//MARK: Writer Represention
void *writer(void* param)
{
    printf("%d Writer is trying to enter \n" , *((int *)param));
    sem_wait(&y);
    printf("%d Writer has entered\n" , *((int *)param));
    sem_post(&y);
    printf("%d Writer is leaving\n" , *((int *)param));
    return NULL;
}

int main()
{
    pthread_t writerthreads[100],readerthreads[100];
    int size,i;
    printf("Enter the number of readers:");
    scanf("%d",&size);
    printf("\n");
    
    int a[10] = {1,2,3,4,5,6,7,8,9,0};
    
    sem_init(&x,0,1);
    sem_init(&y,0,1);
    
    for(i = 0 ; i < size ; i++)
    {
        pthread_create(&writerthreads[i],NULL,(void *)reader,(void *)&a[i]);
        pthread_create(&readerthreads[i],NULL,(void *)writer,(void *)&a[i]);
    }
    for(i = 0  ; i < size ; i++)
    {
        pthread_join(writerthreads[i],NULL);
        pthread_join(readerthreads[i],NULL);
    }

}
