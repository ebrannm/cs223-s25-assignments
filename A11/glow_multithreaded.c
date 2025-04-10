/*----------------------------------------------
* Author: Elisabeth Brann 
* Date: 04/11/25
* Description: A multi-threaded program that applies 
* a glow effect to the image "earth-small.ppm"
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "read_ppm.h"
#include "write_ppm.h"

struct data {
  struct ppm_pixel* pixelArr;
  int startHeight;
  int endHeight;
  int readStart;
  int readEnd;
  int width;
  int fullHeight;
  struct ppm_pixel* glowArr;
  int blurRadius;
  int threshold;
};

void* glowMethod(void *data) {
  struct data *info = data;
  struct ppm_pixel* pixels = info->pixelArr;
  int workingHeight = info->endHeight;
  int w = info->width;
  int radius = info->blurRadius;
  struct ppm_pixel* glowPixels = info->glowArr;
  struct ppm_pixel* brightPixels = malloc(sizeof(struct ppm_pixel) * (info->readEnd - info->readStart) * w);
  printf("Thread sub-image slice: rows (%d, %d)\n", info->startHeight, workingHeight);
  for (int i = info->readStart; i < info->readEnd; i++) {
    for (int j = 0; j < w; j++) {
      unsigned char blue = pixels[i * w + j].blue;
      unsigned char green = pixels[i * w + j].green;
      unsigned char red = pixels[i * w + j].red;
      int brightness = (blue + green + red) / 3;
      if (brightness > info->threshold) {
        brightPixels[(i - info->readStart) * w + j] =  pixels[i * w + j];
      }
      else {
        struct ppm_pixel darkPixel;
        darkPixel.blue = 0;
        darkPixel.red = 0;
        darkPixel.green = 0;
        brightPixels[(i - info->readStart) * w + j] =  darkPixel;
        continue;
      }
    }
  }
  for (int i = info->startHeight; i < workingHeight; i++) {
    for (int j = 0; j < w; j++) {
      int lowerHeightIndex = i - radius;
      if (lowerHeightIndex < 0) {
        lowerHeightIndex = 0;
      }
      int upperHeightIndex = i + radius;
      if (upperHeightIndex >= info->readEnd) {
        upperHeightIndex = info->readEnd - 1;
      }
      int lowerWidthIndex = j - radius;
      if (lowerWidthIndex < 0) {
        lowerWidthIndex = 0;
      }
      int upperWidthIndex = j + radius;
      if (upperWidthIndex >= w) {
        upperWidthIndex = w - 1;
      }
      int count = 0;
      int greenSum = 0;
      int blueSum = 0;
      int redSum = 0;
      for (int k = lowerHeightIndex; k <= upperHeightIndex; k++) {
        for (int l = lowerWidthIndex; l <= upperWidthIndex; l++) {
          greenSum = greenSum + brightPixels[(k - info->readStart) * w + l].green;
          blueSum = blueSum + brightPixels[(k - info->readStart) * w + l].blue;
          redSum = redSum + brightPixels[(k - info->readStart) * w + l].red;
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
  free(info);
  free(brightPixels);
  return NULL;
}

int main(int argc, char* argv[]) {
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char* filename = "earth-small.ppm";
  
  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1) {
    switch (opt) {
      case 'N': N = atoi(optarg); break;
      case 't': threshold = atof(optarg); break;
      case 'b': blursize = atof(optarg); break;
      case 'f': filename = optarg; break;
      case '?': printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]); break;
    }
  }
  int w, h;
  struct ppm_pixel* pixels = read_ppm(filename, &w, &h);
  if (!pixels) {
    return 1;
  }
  struct ppm_pixel* glowPixels = (struct ppm_pixel*)malloc(sizeof(struct ppm_pixel) * (h) * (w));
  if (!glowPixels) {
    printf("Error allocating memory\n");
    free(pixels);
    return 1;
  }
  pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * N);
  for (int i = 0; i < N; i++) {
    int linesPerThread = h / N;
    struct data *info = (struct data*)malloc(sizeof(struct data));
    if (info == NULL) {
      printf("Error allocating memory\n");
      free(pixels);
      return 1;
    }
    info->startHeight = i * linesPerThread;
    info->endHeight = info->startHeight + linesPerThread;
    info->blurRadius = blursize / 2;
    int startRead = info->startHeight - info->blurRadius;
    if (startRead < 0) {
      startRead = 0;
    }
    info->readStart = startRead;
    int endRead = info->endHeight + info->blurRadius;
    if (endRead > h) {
      endRead = h;
    }
    info->readEnd = endRead;
    info->pixelArr = pixels;
    info->fullHeight = h;
    info->width = w;
    info->glowArr = glowPixels;
    info->threshold = threshold;
    pthread_create(&tid[i], NULL, glowMethod, info);
  }
  for (int i = 0; i < N; i++) {
    pthread_join(tid[i], NULL);
  }
  write_ppm("glow.ppm", glowPixels, w, h);
  free(glowPixels);
  free(pixels);
  free(tid);
  return 0;
}
