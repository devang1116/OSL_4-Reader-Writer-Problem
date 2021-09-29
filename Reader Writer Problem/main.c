//
//  main.c
//  Reader Writer Problem
//
//  Created by Devang Papinwar on 29/09/21.
//



#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t mutex;

sem_t writ;
int count = 1;
int reade = 0;

void *reader(void *read_no)
{
    pthread_mutex_lock(&mutex);
    reade++;
    printf("\nReader : %d , count : %d" , *((int *)read_no) , count);
    reade--;
    sem_wait(&writ);
    pthread_mutex_unlock(&mutex);
    return 1;
}

void *writer(void *write_no)
{
    sem_wait(&writ);
    count *= 6;
    printf("\nWriter : % d , count : %d" , *((int *)write_no) , count);
    sem_post(&writ);
    return 0;
}

int main(int argc, const char * argv[])
{
    printf("Reader Writer Problem : ");
    pthread_t read , write;
    
    int a[5] = {1,2,3,4,5};
    
    pthread_mutex_init(&mutex , NULL);
    
    sem_init(&writ , 0 , 0);
    
    pthread_create(&read , NULL , (void *)reader , (void *) &a[0]);
    pthread_join(&read , NULL);
    
    pthread_create(&write , NULL , (void *)writer , (void *) &a[1]);
    pthread_join(&write , NULL);
}
