#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/time.h>
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

struct data {
  char** files;
  int numProcesses;
  int difference;
  int threadNum;
  int index;
  char* target;
};

void* threadProcess(void *data) {
  struct data *info = data;
  int count = 0;
  if ((info->threadNum) < info->difference) {
    printf("Thread %d searching %d files (%d to %d)\n", info->threadNum, 
      info->numProcesses + 1, info->index, info->index + info->numProcesses + 1);
  }
  else {
    printf("Thread %d searching %d files (%d to %d)\n", info->threadNum, 
      info->numProcesses, info->index, info->index + info->numProcesses);
  }
  for (int j = 0; j < info->numProcesses; j++) {
    FILE* file;
    file = fopen(info->files[info->index + j], "r");
    if (file == NULL) {
      printf("Thread %d: Error opening file %s\n", info->threadNum, 
        info->files[info->index + j]);
      continue;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
      char* found = strstr(line, info->target);
      if (found != NULL) {
        printf(ANSI_COLOR_GREEN "%d) " ANSI_COLOR_RESET ANSI_COLOR_CYAN "%s "
          ANSI_COLOR_RESET "%s", info->threadNum, info->files[info->index + j],
          line);
        count++;
      }
    }
    fclose(file);
  }
  if (info->threadNum < info->difference) {
    FILE* file;
    file = fopen(info->files[info->index + info->numProcesses], "r");
    if (file == NULL) {
      printf("Thread %d: Error opening file %s\n", info->threadNum, 
        info->files[info->index + info->numProcesses]);
      return NULL;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
      char* found = strstr(line, info->target);
      if (found != NULL) {
        printf(ANSI_COLOR_GREEN "%d)" ANSI_COLOR_RESET ANSI_COLOR_CYAN "%s "
          ANSI_COLOR_RESET "%s", info->threadNum, 
          info->files[info->index + info->numProcesses], line);
        count++;
      }
    }
    fclose(file);
  }
  printf("Thread %d found %d lines containing keyword: %s\n", 
    info->threadNum, count, info->target);
  free(info);
  return NULL;
}

int main(int argc, char** argv) {
  if (argc < 4) {
    printf("Usage: ./grep <NumThreads> <Keyword> <Files>\n");
    return 1;
  }
  if (atoi(argv[1]) == 0) {
    printf("Need to designate at least one thread!\n");
    return 1;
  }
  struct timeval start, end;
  gettimeofday(&start, NULL);
  int numThreads = atoi(argv[1]);
  char* target = argv[2];
  int numFiles = argc - 3;
  if (numThreads > numFiles) {
    numThreads = numFiles;
  }
  int threadsPerFile = numFiles/numThreads;
  int difference = numFiles % numThreads;
  printf("Searching %d files for keyword: %s\n", numFiles, target);
  pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * numThreads);
  if (tid == NULL) {
    printf("Error allocating memory\n");
    return 1;
  }
  for (int i = 0; i < numThreads; i++) {
    int fileIndex = 3 + (i * threadsPerFile);
    if (i < difference) {
      fileIndex += i;
    }
    else {
      fileIndex += difference;
    }
    struct data *info = (struct data*)malloc(sizeof(struct data));
    if (info == NULL) {
      printf("Error allocating memory\n");
      free(tid);
      return 1;
    }
    info->files = argv;
    info->numProcesses = threadsPerFile;
    info->difference = difference;
    info->threadNum = i;
    info->index = fileIndex;
    info->target = target;
    pthread_create(&tid[i], NULL, threadProcess, info);
  }
  for (int i = 0; i < numThreads; i++) {
    pthread_join(tid[i], NULL);
  }
  free(tid);
  gettimeofday(&end, NULL);
  double timeElapsed;
  timeElapsed = (end.tv_sec - start.tv_sec) * 1e6;
  timeElapsed = (timeElapsed + (end.tv_usec - start.tv_usec)) * 1e-6;
  printf("Time elapsed: %f\n", timeElapsed);
  return 0;
}
