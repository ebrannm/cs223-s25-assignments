/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 3/28/25
 * Description: Spawns processes according to the given diagram.
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

int main() {
  int pid = getpid();
  printf("%d] A0\n", pid);
  int ret = fork();
  if (ret == 0) {
    int pid = getpid();
    printf("%d] B1\n", pid);
    printf("%d] Bye\n", pid);
    exit(0);
  }
  else {
    printf("%d] B0\n", pid);
    int ret = fork();
    if (ret == 0) {
      int pid = getpid();
      printf("%d] C1\n", pid);
      printf("%d] Bye\n", pid);
      exit(0);
    }
    else {
      printf("%d] C0\n", pid);
      printf("%d] Bye\n", pid);
    }
  }
  return 0;
}
