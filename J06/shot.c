#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int SIG) {
  if (SIG == SIGINT) {
    printf("Help! I've been shot!\n");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sig_handler);
  while(1) {
    continue;
  }
  return 0;
}
