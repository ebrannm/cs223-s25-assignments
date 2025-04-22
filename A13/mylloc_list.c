/*----------------------------------------------
* Author: Elisabeth Brann 
* Date: 04/25/25
* Description: Custom implementation of malloc and free based 
* on the reading, with added functionality of tracking how much of
* a chunk is in use.
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int used;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  if (size <= 0) {
    return NULL;
  }
  struct chunk *ptr = flist;
  struct chunk *prev = NULL;
  while (ptr != NULL) {
    if (ptr->size >= size) {
      if (prev != NULL) {
        prev->next = ptr->next;
      }
      else {
        flist = ptr->next;
      }
      ptr->used = size;
      return (void*) (ptr + 1);
    }
    else {
      prev = ptr;
      ptr = ptr->next;
    }
  }
  void *memory = sbrk(size + sizeof(struct chunk));
  if (memory == (void*) - 1) {
    return NULL;
  }
  else {
    struct chunk *cnk = (struct chunk*) memory;
    cnk->size = size;
    cnk->used = size;
    cnk->next = NULL;
    return (void*) (cnk + 1);
  }
}

void free(void *memory) {
  if (memory != NULL) {
    struct chunk *cnk = (struct chunk*) ((struct chunk*) memory - 1);
    cnk->next = flist;
    cnk->used = 0;
    flist = cnk;
  }
  return;
}