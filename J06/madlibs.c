#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 32

int main() {
    int boolean;
    int number;
    printf("Boolean: ");
    scanf("%d", &boolean);
    printf("Number: ");
    scanf("%d", &number);
    char** adjectives = malloc(number * sizeof(char*));;
    for (int i = 0; i < number; i++) {
        adjectives[i] = malloc(MAXSIZE);
        printf("Adjective: ");
        scanf("%s", adjectives[i]);
    }
    printf("You are the most ");
    for (int i = number - 1; i >= 0; i--) {
        if (i > 0) {
            printf("%s, ", adjectives[i]);
        }
        else {
            printf("and %s", adjectives[i]);
        }
    }
    printf(" person that I know and you know its ");
    if (boolean) {
        printf("true!\n");
    }
    else {
        printf("false!\n");
    }
    for (int i = 0; i < number; i++) {
        free(adjectives[i]);
    }
    free(adjectives);
    return 0;
}