// Reader-Writer problem using monitors 

#include <iostream> 
#include <pthread.h>
#include<unistd.h>
#include <semaphore.h> 
using namespace std; 

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1, numreader = 0;

void *writer(void *writerNumber)
{
	while (1) {
		sem_wait(&wrt);
		cnt *= 2;
		printf("[ Writer #%d ] - Modified count to %d\n", *((int *) writerNumber), cnt);
		sem_post(&wrt);		// signal
		sleep(rand()%10);
	}
}

void *reader(void *readerNumber)
{
	while (1) {
		pthread_mutex_lock(&mutex);
		numreader++;
		if (numreader == 1)	// block writer if first reader
			sem_wait(&wrt);
		pthread_mutex_unlock(&mutex);
		printf("[ Reader #%d ] - Read count as %d\n", *((int *) readerNumber), cnt);
		pthread_mutex_lock(&mutex);
		numreader--;
		if (numreader == 0)	// if last reader, wake up writer
			sem_post(&wrt);
		pthread_mutex_unlock(&mutex);
		sleep(rand()%10);
	}
}

int main() 
{ 
	int nr, nw;
	pthread_mutex_init(&mutex, NULL);
	sem_init(&wrt, 0, 1);
    cout << "Number of Readers: ";
    cin >> nr;
    cout << "Number of Writers: ";
    cin >> nw;
	pthread_t r[nr], w[nw];
	int rid[nr], wid[nw]; 
	for (int i = 0; i < nr; i++) { 
        rid[i] = i;
		// creating threads which execute reader function 
		pthread_create(&r[i], NULL, &reader, &rid[i]); 
    }
    for (int i = 0; i < nw; i++) { 
        wid[i] = i;
		// creating threads which execute writer function 
		pthread_create(&w[i], NULL, &writer, &wid[i]); 
	} 

	for (int i = 0; i < nr; i++) 
		pthread_join(r[i], NULL); 
	 
	for (int i = 0; i < nw; i++) 
		pthread_join(w[i], NULL);
	
	pthread_mutex_destroy(&mutex);
	sem_destroy(&wrt);
} 
