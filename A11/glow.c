/*----------------------------------------------
* Author: Elisabeth Brann 
* Date: 04/11/25
* Description: A single-threaded program that applies 
* a glow effect to the image "earth-small.ppm"
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main() {
  int w, h;
  char* fileName = "earth-small.ppm";
  int threshold = 200;
  struct ppm_pixel* pixels = read_ppm(fileName, &w, &h);
  if (!pixels) {
    return 1;
  }
  struct ppm_pixel* glowPixels = (struct ppm_pixel*)malloc(sizeof(struct ppm_pixel) * (h) * (w));
  struct ppm_pixel* brightPixels = (struct ppm_pixel*)malloc(sizeof(struct ppm_pixel) * (h) * (w));
  if (!glowPixels) {
    printf("Error allocating memory\n");
    free(pixels);
    return 1;
  }
  if (!brightPixels) {
    printf("Error allocating memory\n");
    free(pixels);
    free(glowPixels);
    return 1;
  }
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      unsigned char blue = pixels[i * w + j].blue;
      unsigned char green = pixels[i * w + j].green;
      unsigned char red = pixels[i * w + j].red;
      int brightness = (blue + green + red) / 3;
      if (brightness > threshold) {
        brightPixels[i * w + j] =  pixels[i * w + j];
      }
      else {
        struct ppm_pixel darkPixel;
        darkPixel.blue = 0;
        darkPixel.red = 0;
        darkPixel.green = 0;
        brightPixels[i * w + j] =  darkPixel;
        glowPixels[i * w + j] = pixels[i * w + j];
        continue;
      }
    }
  }
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int lowerHeightIndex = i - 12;
      if (lowerHeightIndex < 0) {
        lowerHeightIndex = 0;
      }
      int upperHeightIndex = i + 12;
      if (upperHeightIndex >= h) {
        upperHeightIndex = h - 1;
      }
      int lowerWidthIndex = j - 12;
      if (lowerWidthIndex < 0) {
        lowerWidthIndex = 0;
      }
      int upperWidthIndex = j + 12;
      if (upperWidthIndex >= w) {
        upperWidthIndex = w - 1;
      }
      int count = 0;
      int greenSum = 0;
      int blueSum = 0;
      int redSum = 0;
      for (int k = lowerHeightIndex; k <= upperHeightIndex; k++) {
        for (int l = lowerWidthIndex; l <= upperWidthIndex; l++) {
          greenSum = greenSum + brightPixels[k * w + l].green;
          blueSum = blueSum + brightPixels[k * w + l].blue;
          redSum = redSum + brightPixels[k * w + l].red;
          count++;
        }
      }
      struct ppm_pixel newPixel;
      blueSum = blueSum/count +  pixels[i * w + j].blue;
      if (blueSum > 255) {
        blueSum = 255;
      }
      newPixel.blue = blueSum;
      greenSum = greenSum/count +  pixels[i * w + j].green;
      if (greenSum > 255) {
        greenSum = 255;
      }
      newPixel.green = greenSum;
      redSum = redSum/count +  pixels[i * w + j].red;
      if (redSum > 255) {
        redSum = 255;
      }
      newPixel.red = redSum;
      glowPixels[i * w + j] = newPixel;
    }
  }
  write_ppm("glow.ppm", glowPixels, w, h);
  free(brightPixels);
  free(glowPixels);
  free(pixels);
}