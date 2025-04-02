#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void child_handler(int SIG) {
  int pid = getpid();
  if (SIG == SIGALRM){
    printf("Marco [%d]\n", pid);
    int ppid = getppid();
    kill(ppid, SIGALRM);
  }
  if (SIG == SIGTERM) {
    exit(0);
  }
}

void parent_handler(int SIG) {
  int pid = getpid();
  if (SIG == SIGALRM){
    printf("Polo [%d]\n", pid);
  }
  if (SIG == SIGTERM) {
    exit(0);
  }
}

int main() {
  int pid = getpid();
  printf("Parent is %d\n", pid);
  int ret = fork();
  if (ret == 0) {
    signal(SIGALRM, child_handler);
    signal(SIGTERM, child_handler);
    while (1) {
      pause();
    }
  }
  else if (ret != 0) {
    signal(SIGALRM, parent_handler);
    signal(SIGTERM, parent_handler);
    while (1) {
      char input;
      scanf(" %c", &input);
      if (input == 'm') {
        kill(ret, SIGALRM);
      }
      else if (input == 'q') {
        kill(ret, SIGTERM);
        return 0;
      }
      else {
        printf("invalid input, please enter either 'm' or 'q'\n");
      }
    }
  }
  else {
    printf("Fork failed");
    return 1;
  }
  return 0;
}
