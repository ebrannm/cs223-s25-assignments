/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 3/28/25
 * Description: Uses N processes to search for a keyword in a set of files.
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/time.h>
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

int main(int argc, char** argv) {
  if (argc < 4) {
    printf("Usage: ./grep <NumProcesses> <Keyword> <Files>\n");
    return 1;
  }
  if (atoi(argv[1]) == 0) {
    printf("Need to designate at least one process!\n");
    return 1;
  }
  struct timeval start, end;
  gettimeofday(&start, NULL);
  int numProcesses = atoi(argv[1]);
  char* target = argv[2];
  int numFiles = argc - 3;
  if (numProcesses > numFiles) {
    numProcesses = numFiles;
  }
  int processesPerFile = numFiles/numProcesses;
  int difference = numFiles % numProcesses;
  printf("Searching %d files for keyword: %s\n", numFiles, target);
  for (int i = 0; i < numProcesses; i++) {
    int fileIndex = 3 + (i * processesPerFile);
    if (i < difference) {
      fileIndex += i;
    }
    else {
      fileIndex += difference;
    }
    int status;
    int ret = fork();
    if (ret == 0) {
      int count = 0;
      int pid = getpid();
      if (i < difference) {
        printf("Process [%d] searching %d files (%d to %d)\n", pid, 
          processesPerFile + 1, fileIndex, fileIndex + processesPerFile + 1);
      }
      else {
        printf("Process [%d] searching %d files (%d to %d)\n", pid, 
          processesPerFile, fileIndex, fileIndex + processesPerFile);
      }
      for (int j = 0; j < processesPerFile; j++) {
        FILE* file;
        file = fopen(argv[fileIndex + j], "r");
        if (file == NULL) {
          printf("Process [%d]: Error opening file %s\n", pid, argv[fileIndex + j]);
          continue;
        }
        char line[256];
        while (fgets(line, sizeof(line), file)) {
          char* found = strstr(line, target);
          if (found != NULL) {
            printf(ANSI_COLOR_GREEN "%d) " ANSI_COLOR_RESET ANSI_COLOR_CYAN "%s "
              ANSI_COLOR_RESET "%s", pid, argv[fileIndex + j], line);
            count++;
          }
        }
        fclose(file);
      }
      if (i < difference) {
        FILE* file;
        file = fopen(argv[fileIndex + processesPerFile], "r");
        if (file == NULL) {
          printf("Process [%d]: Error opening file %s\n", pid, argv[fileIndex + processesPerFile]);
          continue;
        }
        char line[256];
        while (fgets(line, sizeof(line), file)) {
          char* found = strstr(line, target);
          if (found != NULL) {
            printf(ANSI_COLOR_GREEN "%d)" ANSI_COLOR_RESET ANSI_COLOR_CYAN "%s "
              ANSI_COLOR_RESET "%s", pid, argv[fileIndex + processesPerFile], line);
            count++;
          }
        }
        fclose(file);
      }
      printf("Process [%d] found %d lines containing keyword: %s\n", pid, count, target);
      exit(count);
    }
  }
  int totalCount = 0;
  int status;
  for (int i = 0; i < numProcesses; i++) {
    pid_t childPid = waitpid(-1, &status, 0);
    totalCount += WEXITSTATUS(status);
  }
  printf("Total occurances: %d\n", totalCount);
  gettimeofday(&end, NULL);
  double timeElapsed;
  timeElapsed = (end.tv_sec - start.tv_sec) * 1e6;
  timeElapsed = (timeElapsed + (end.tv_usec - start.tv_usec)) * 1e-6;
  printf("Time elapsed: %f\n", timeElapsed);
  return 0;
}