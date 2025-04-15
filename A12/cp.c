/*----------------------------------------------
* Author: Elisabeth Brann 
* Date: 04/18/25
* Description: Producer/consumer method.
* Infinite loop, must be exited with ctrl-c
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>

#define N 10
pthread_mutex_t lock; 

struct threadData {
  int* index;
  int* size;
  int* queue;
};

int produce_item() {
    return rand() % 10;
}

void consume_item(int item) {
    printf("Received item: %d\n", item);
}

void* producer(void* threadInfo) {
  struct threadData* data = (struct threadData*)threadInfo;
  int* index = data->index;
  int* size = data->size;
  int* queue = data->queue;
  while (1) {
    pthread_mutex_lock(&lock); 
    if (*size == N) {
      pthread_mutex_unlock(&lock);
      sleep(1);
      continue;
    }
    else {
      int entry = produce_item();
      queue[*index] = entry;
      *size = *size + 1;
      pthread_mutex_unlock(&lock);
      *index = (*index + 1) % N;
      sleep(1);
    }
  }
}

void* consumer(void* threadInfo) {
  struct threadData* data = (struct threadData*)threadInfo;
  int* index = data->index;
  int* size = data->size;
  int* queue = data->queue;
  while(1) {
    pthread_mutex_lock(&lock);
    if (*size == 0) {
      pthread_mutex_unlock(&lock);
      sleep(1);
      continue;
    }
    else {
      int entry = queue[*index];
      consume_item(entry);
      queue[*index] = 0;
      *size = *size - 1;
      pthread_mutex_unlock(&lock);
      *index = (*index + 1) % N;
      sleep(1);
    }
  }
}


int main() {
  srand(time(NULL));
  int consumeIndex = 0;
  int produceIndex = 0;
  int size = 0;
  int queue[N] = {0};
  pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * 2);
  pthread_mutex_init(&lock, NULL);
  if (tid == NULL) {
    printf("Error allocating memory\n");
    return 1;
  }
  struct threadData* producerInfo = (struct threadData*)malloc(sizeof(struct threadData));
  producerInfo->index = &produceIndex;
  producerInfo->size = &size;
  producerInfo->queue = queue;
  pthread_create(&tid[0], NULL, producer, producerInfo);
  struct threadData* consumerInfo = (struct threadData*)malloc(sizeof(struct threadData));
  consumerInfo->index = &consumeIndex;
  consumerInfo->size = &size;
  consumerInfo->queue = queue;
  pthread_create(&tid[1], NULL, consumer, consumerInfo);
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_mutex_destroy(&lock);
  free(producerInfo);
  free(consumerInfo);
  free(tid);
  return 0;
}

