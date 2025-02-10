/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 02/14/25
 * Description: Allows users to add snacks to the snackbar and 
 * displays them in alphabetical order
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  double price;
  int quantity;
};

struct node {
  struct snack* data;
  struct node* next;
};

struct node* insertFirst(struct node* head, struct snack* snack) {
  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  newNode->data = malloc(sizeof(struct snack));
  memcpy(newNode->data, snack, sizeof(struct snack));
  newNode->next = head;
  return newNode;
}

struct node* split(struct node* head) {
  struct node* fast = head;
  struct node* slow = head;
  while (fast != NULL && fast->next != NULL) {
    fast = fast->next->next;
    if (fast != NULL) {
      slow = slow->next;
    }
  }
  struct node* temp = slow->next;
  slow->next = NULL;
  return temp;
}

struct node* mergeName(struct node* first, struct node* second) {
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  if (strcmp(first->data->name, second->data->name) < 0) {
    first->next = mergeName(first->next, second);
    return first;
  }
  else {
    second->next = mergeName(first, second->next);
    return second;
  }
}

struct node* sortName(struct node* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }
  struct node* second = split(head);
  head = sortName(head);
  second = sortName(second);
  return mergeName(head, second);
}

struct node* mergeQuantity(struct node* first, struct node* second) {
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  if (first->data->quantity < second->data->quantity) {
    first->next = mergeQuantity(first->next, second);
    return first;
  }
  else {
    second->next = mergeQuantity(first, second->next);
    return second;
  }
}

struct node* sortQuantity(struct node* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }
  struct node* second = split(head);
  head = sortQuantity(head);
  second = sortQuantity(second);
  return mergeQuantity(head, second);
}

struct node* mergeCost(struct node* first, struct node* second) {
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  if (first->data->price < second->data->price) {
    first->next = mergeCost(first->next, second);
    return first;
  }
  else {
    second->next = mergeCost(first, second->next);
    return second;
  }
}

struct node* sortCost(struct node* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }
  struct node* second = split(head);
  head = sortCost(head);
  second = sortCost(second);
  return mergeCost(head, second);
}

void printSnack(struct snack* snack) {
  printf("%s %s %.2f %s %d\n", snack->name, "\t\tcost:", snack->price, "\tquantity:", snack->quantity);
}

void printList(struct node* head) {
  struct node* current = head;
  int num = 0;
  while (current != NULL) {
    printf("%d) ", num);
    printSnack(current->data);
    current = current->next;
    num += 1;
  }
}

void clear(struct node* head) {
  struct node* current = head; 
  struct node* nextNode = NULL;
  while (current != NULL) {
    nextNode = current->next;
    free(current->data);
    free(current);
    current = nextNode;
  }
}

int main() {
  int num;
  printf("Enter a number of snacks: ");
  scanf("%d", &num);
  FILE* snackfile;
  snackfile = fopen("snackinfo.txt", "w");
  for (int i = 0; i < num; i++) {
    printf("Enter a name: ");
    char name[32];
    scanf("%s", name);
    printf("Enter a cost: ");
    double cost;
    scanf("%lf", &cost);
    printf("Enter a quantity: ");
    int quantity;
    scanf("%d", &quantity);
    fprintf(snackfile, "%s %lf %d\n", name, cost, quantity);
  }
  fclose(snackfile);
  snackfile = fopen("snackinfo.txt", "r");
  struct node* head = NULL;
  for (int i = 0; i < num; i++) {
    struct snack currSnack;
    fscanf(snackfile, "%s %lf %d", currSnack.name, &currSnack.price, &currSnack.quantity);
    head = insertFirst(head, &currSnack);
  }
  fclose(snackfile);
  printf("\nWelcome to Sorted Sally's Snack Bar.\n");
  printf("\nSorted alphabetically:\n");
  head = sortName(head);
  printList(head);
  printf("\nSorted by cost:\n");
  head = sortCost(head);
  printList(head);
  printf("\nSorted by Quantity:\n");
  head = sortQuantity(head);
  printList(head);
  clear(head);
  return 0;
}