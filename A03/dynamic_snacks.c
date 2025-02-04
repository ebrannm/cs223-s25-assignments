/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 02/07/25
 * Description: Allows for users to add snacks to a snackbar.
 ---------------------------------------------*/
#include <stdio.h>
#include  <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  double price;
  int quantity;
};

int main() {
  int num;
  printf("Enter a number of snacks: ");
  scanf("%d", &num);
  struct snack* menu = (struct snack*)malloc(sizeof(struct snack) * num);
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
    fprintf(snackfile, "%s %lf %d %s", name, cost, quantity, "\n");
  }
  fclose(snackfile);
  snackfile = fopen("snackinfo.txt", "r");
  for (int i = 0; i < num; i++) {
    struct snack currSnack;
    fscanf(snackfile, "%s %lf %d", currSnack.name, &currSnack.price, &currSnack.quantity);
    menu[i] = currSnack;
  }
  fclose(snackfile);
  printf("\nWelcome to Dynamic Donna's Snack Bar.\n");
  for (int i = 0; i < num; i++) {
    printf("%s %d%s %s %s %.2f %s %d", "\n", i, ")", menu[i].name, "\t\tcost:", menu[i].price, "\tquantity:", menu[i].quantity);
  }
  free(menu);
  return 0;
}