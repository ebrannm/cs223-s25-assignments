#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Enter a file");
        return(1);
    }
    FILE* fp = fopen(argv[1], "r");
    unsigned int mask = ~(1 << 7);
    char c = fgetc(fp);
    while (c != EOF) {
        c = c >> 1;
        c = c & mask;
        printf("%c", c);
        c = fgetc(fp);
    }
    fclose(fp);
    return 0;
}
