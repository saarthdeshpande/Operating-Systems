#include<iostream>
#include <unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<iomanip>

using namespace std;

#define BUFFER_SIZE 5

struct Buffer {
  int in, out, buff[BUFFER_SIZE] = {0}, count = 0;
  sem_t empty, full;
  pthread_mutex_t bufflock;
  void init();
  void showBuff();
};

void Buffer::init() {
  in = out = 0;
  sem_init(&empty, 0, BUFFER_SIZE); // sem_t, pshared (whether shareable), initial value
  sem_init(&full, 0, 0);
  pthread_mutex_init(&bufflock, NULL);
}

Buffer buffer;
int item = 1;

void* producer(void* arg)
{
  int i = *(int*) arg;
  while (1) {
    sem_wait(&buffer.empty);
    pthread_mutex_lock(&buffer.bufflock);
    printf("\n[ Producer #%d ] - Produced Item %d", i, ++item);
    buffer.buff[(buffer.in++) % BUFFER_SIZE] = item;
    buffer.count += 1;
    buffer.showBuff();
    pthread_mutex_unlock(&buffer.bufflock);
    sem_post(&buffer.full);
    sleep(rand()%10);
  }
}

void* consumer(void* arg)
{
  int i = *(int*) arg;
  while (1) {
    sem_wait(&buffer.full);
    pthread_mutex_lock(&buffer.bufflock);
    int cons = buffer.buff[(buffer.out) % BUFFER_SIZE];
    printf("\n[ Consumer #%d ] - Consumed Item %d", i, cons);
    buffer.buff[(buffer.out++) % BUFFER_SIZE] = 0;
    buffer.count -= 1;
    buffer.showBuff();
    pthread_mutex_unlock(&buffer.bufflock);
    sem_post(&buffer.empty);
    sleep(rand()%10);
  }
}

void Buffer::showBuff() {
  if (buffer.count == 0) {
    cout << endl << endl << "Buffer Empty!" << endl;
  } else if (buffer.count == BUFFER_SIZE) {
    cout << endl << endl << "Buffer Full!" << endl;
    }
  cout << endl << "Buffer:\n======================================================\n";
  for(int element: buffer.buff)
    cout << setw(5) << element;
  cout << endl << "======================================================\n";
}

int main() {
  buffer.init();
  int producers, consumers;
  int c[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  pthread_t pid[10], cid[10];
  cout << "Enter number of Producers: ";
  cin >> producers;
  cout << "Enter number of Consumers: ";
  cin >> consumers;
  for(int i = 0;i < producers;i++)
    pthread_create(&pid[i], NULL, *producer, &c[i]);

  for(int i = 0;i < consumers;i++)
    pthread_create(&cid[i], NULL, *consumer, &c[i]);
    
  for (int i = 0;i < producers;i++)
    pthread_join(pid[i], NULL);
  for(int i = 0;i < consumers;i++)
    pthread_join(cid[i], NULL);

  return 0;
}
