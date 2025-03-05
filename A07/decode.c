/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 3/06/25
 * Description: Reads in a PPM file (raw, or binary, format) and then outputs 
 * any message that might be stored in the least significant bits of each color.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }
  int w, h;
  char* fileName = argv[1];
  struct ppm_pixel* pixels = read_ppm(fileName, &w, &h);
  if (!pixels) {
    return 1;
  }
  printf("Reading %s: with width %d and height %d\n", fileName, w, h);
  printf("Max number of characters in the image: %d\n", (int)(w * h * 3)/7);
  int *ascii = malloc(sizeof(int) * w * h * 3);
  if (!ascii) {
    printf("Memory allocation failed\n");
    free(pixels);
    return 1;
  }
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel pixel = pixels[i * w + j];
      ascii[(i * w + j) * 3] = pixel.red % 2;
      ascii[((i * w + j) * 3) + 1] = pixel.green % 2;
      ascii[((i * w + j) * 3) + 2] = pixel.blue % 2;
    }
  }
  for (int i = 0; (i + 7) < (w * h * 3); i = i + 8) {
    char letter = (ascii[i] << 7) | (ascii[i+1] << 6) | (ascii[i+2] << 5) | 
      (ascii[i+3] << 4) | (ascii[i+4] << 3) | (ascii[i+5] << 2) | 
      (ascii[i+6] << 1) | ascii[i+7];
    if (letter == '\0') break;
    printf("%c", letter);
  }
  free(pixels);
  free(ascii);
  return 0;
}