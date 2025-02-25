/*----------------------------------------------
 * Author: Elisabeth Brann 
 * Date: 02/28/25
 * Description: Takes a C file as a command line argument and uses a stack to check for matched braces
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char value;
  int row;
  int column;
  struct node* next;
};

void push(char character, int row, int col, struct node** head) {
  struct node* newNode = malloc(sizeof(struct node));
  if (!newNode) {
    printf("Memory allocation failed\n");
    return;
  }
  newNode->value = character;
  newNode->row = row;
  newNode->column = col;
  newNode->next = *head;
  *head = newNode;
}

struct node* pop(struct node** head) {
  if (*head == NULL) {
    return NULL;
  }
  struct node* temp = *head;
  *head = (*head)->next;
  return temp;
}

void printList(struct node* head) {
    for(struct node * n = head; n!= NULL; n = n->next) {
    printf("%c", n->value);
  }
}

void clearList(struct node* head) {
  struct node* curr = head;
  struct node* next = NULL;
  while(curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
}
 
int main(int numArg, char** argv) {
  if (numArg < 2) {
    printf("Please enter a file!");
    return 1;
  }
  char* fileName = argv[1];
  FILE *filePointer;
  filePointer = fopen(fileName, "r");
  if (filePointer == NULL) {
    printf("file can't be opened \n");
    return 1;
  }
  char currChar;
  int line = 1;
  int column = 0;
  struct node* head = NULL;
  while ((currChar = fgetc(filePointer)) != EOF) {
    column++;
    if (currChar == '{') {
      push(currChar, line, column, &head);
    }
    if (currChar == '}') {
      struct node* popped = pop(&head);
      if (popped == NULL) {
        printf("Unmatched closing brace on Line %d and Column %d\n", line, column);
      }
      else if (popped->value != '{') {
        printf("Unmatched closing brace on Line %d and Column %d\n", line, column);
        free(popped);
      }
      else {
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n", popped->row, popped->column, line, column);
        free(popped);
      }
    }
    if (currChar == '\n') {
      line++;
      column = 0;
    }
  }
  while (head != NULL) {
    struct node* popped = pop(&head);
    printf("Unmatched opening brace at Line %d and Column %d\n", popped->row, popped->column);
    free(popped);
  }
  fclose(filePointer);
  return 0;
}

