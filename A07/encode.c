/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 3/06/25
 * Description: Reads in a PPM file (raw, or binary, format) 
 * and asks the user for a message to embed within it
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  int w, h;
  char* fileName = argv[1];
  struct ppm_pixel* pixels = read_ppm(fileName, &w, &h);
  if (!pixels) {
    return 1;
  }
  printf("Reading %s: with width %d and height %d\n", fileName, w, h);
  printf("Max number of characters in the image: %d\n", (int)((w * h * 3) / 8));
  char* word = malloc(((w * h * 3) / 8) + 1);
  if (!word) {
    printf("Memory allocation failed\n");
    free(pixels);
    return 1;
  }
  printf("Enter a phrase: ");
  scanf("%s", word);
  if (strlen(word) > ((w * h * 3) / 8)) {
    printf("Input text is too long\n");
    free(pixels);
    free(word);
    return 1;
  }
  int* ascii = malloc(sizeof(int) * strlen(word) * 8);
  if (!ascii) {
    printf("Memory allocation failed\n");
    free(pixels);
    free(word);
    return 1;
  }
  for (int i = 0; i < strlen(word); i++) {
    for(int j = 7; j >= 0; j-- ) {
      ascii[i * 8 + (7 - j)] = (word[i] >> j ) & 1;
      }
  }
  for (int i = 0; i < strlen(word) * 8; i += 3) {
    int pixel_index = i / 3;
    if (pixel_index >= w * h) {
      break;
    }
    struct ppm_pixel* pixel = &pixels[pixel_index];
    if (i < strlen(word) * 8) {
      pixel->red = (pixel->red & ~1) | ascii[i];
    }
    if (i + 1 < strlen(word) * 8) {
      pixel->green = (pixel->green & ~1) | ascii[i + 1];
    }
    if (i + 2 < strlen(word) * 8) {
      pixel->blue = (pixel->blue & ~1) | ascii[i + 2];
    }
  }
  char newFileName[256] = "";
  char file[256];
  strncpy(file, fileName, sizeof(file) - 1);
  char *end = strtok(file, ".");
  strcat(newFileName, end);
  strcat(newFileName, "-encoded.ppm");
  printf("Writing file %s\n", newFileName);
  write_ppm(newFileName, pixels, w, h);
  free(pixels);
  free(ascii);
  free(word);
  return 0;
}