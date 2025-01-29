/***************************************************
 * snackbar.c
 * Author: Elisabeth Brann
 * Date: 01/31/2025
 * Maintains a list of snacks available for purchase.
 */
#include <stdio.h>

struct snack {
  char* name;
  double price;
  int quantity;
};

int main() {
  struct snack coco = {"Coco Puffs", 1.50, 4};
  struct snack cheese = {"Manchego cheese", 15.50, 6};
  struct snack beans = {"Magic beans", 0.50, 0};
  struct snack menu[] = {coco, cheese, beans};
  printf("Welcome to Steven Struct's Snack Bar.\n");
  printf("How much money do you have? ");
  int money;
  scanf("%d", &money);
  printf("What snack would you like to buy? [0,1,2] ");
  int digit;
  scanf("%d", &digit);
  if (menu[digit].quantity == 0) {
    printf("%s %s", "Sorry, we are out of", menu[digit].name);
  }
  else if (menu[digit].price > money) {
    printf("You can't afford it!");
  }
  else {
    printf("%s %s", "You bought", menu[digit].name);
    printf("%s%.2f %s", "\nYou have $", money-menu[digit].price, "left");
  }
  return 0;
}
