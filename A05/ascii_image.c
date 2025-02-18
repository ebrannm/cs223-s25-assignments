/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 02/21/25
 * Description: Takes a PPM image as a command line argument and
 * displays it as ASCII Art.
 ---------------------------------------------*/
#include <stdio.h>
#include "read_ppm.h"
#include <stdlib.h>
#include "write_ppm.h"

int main(int numArg, char** argv) {
  if (numArg < 2) {
    printf("Please enter a file!");
    return 1;
  }
  char* fileName = argv[1];
  int w, h;
  struct ppm_pixel* pixels = read_ppm(fileName, &w, &h);
  if (!pixels) {
    return 1;
  }
  char* asciiArr = (char*)malloc(w * h * sizeof(char));
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel pixel = pixels[i * w + j];
      int intensity = (pixel.red + pixel.green + pixel.blue)/3;
      if (intensity <= 25) {
        asciiArr[i * w + j] = '@';
      }
      else if (intensity <= 50) {
        asciiArr[i * w + j] = '#';
      }
      else if (intensity <= 75) {
        asciiArr[i * w + j] = '%';
      }
      else if (intensity <= 100) {
        asciiArr[i * w + j] = '*';
      }
      else if (intensity <= 125) {
        asciiArr[i * w + j] = 'o';
      }
      else if (intensity <= 150) {
        asciiArr[i * w + j] = ';';
      }
      else if (intensity <= 175) {
        asciiArr[i * w + j] = ':';
      }
      else if (intensity <= 200) {
        asciiArr[i * w + j] = ',';
      }
      else if (intensity <= 225) {
        asciiArr[i * w + j] = '.';
      }
      else if (intensity <= 255) {
        asciiArr[i * w + j] = ' ';
      }
    }
  }
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("%c", asciiArr[i * w + j]);
    }
    printf("\n");
  }
  free(pixels);
  free(asciiArr);
  return 0;
}
