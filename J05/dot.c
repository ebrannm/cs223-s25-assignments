#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000

struct data {
  int startIndex;
  int endIndex;
  int* v;
  int* u;
  int sum;
};

void* product(void* data) {
  struct data* info = data;
  int sum = 0;
  for (int i = info->startIndex; i < info->endIndex; i++) {
    sum = info->v[i] * info->u[i] + sum;
  }
  info->sum = sum;
  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int v[SIZE];
  int u[SIZE];
  int dotproduct = 0;
   
  for (int i = 0; i < SIZE; i++) {
    v[i] = rand() % 1000 - 500;
    u[i] = rand() % 1000 - 500;
    dotproduct += u[i] * v[i];
  }
  printf("Ground truth dot product: %d\n", dotproduct);

  // TODO: Implement your thread solution here
  printf("Test with 4 threads\n");
  pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * 4);
  int processesPerThread = SIZE/4;
  int thread_dotproduct = 0;
  struct data* info = (struct data*)malloc(sizeof(struct data) * 4);
  for (int i = 0; i < 4; i++) {
    info[i].startIndex = i * processesPerThread;
    info[i].endIndex = (i + 1) * processesPerThread;
    info[i].u = u;
    info[i].v = v;
    info[i].sum = 0;
    pthread_create(&tid[i], NULL, product, (void*) &info[i]);
  }
  for (int i = 0; i < 4; i++) {
    pthread_join(tid[i], NULL);
    thread_dotproduct = thread_dotproduct + info[i].sum;
  }
  printf("Answer with threads: %d\n", thread_dotproduct);
  free(tid);
  free(info);
  return 0;
}
