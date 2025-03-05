/*----------------------------------------------
 * Author: Elisabeth Brann 
 * Date: 02/21/25
 * Description: Reads PPM files stored in binary format and returns a 
 * 1D array of ppm_pixel. Copied from Assignment 5.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *filePointer;
  char header[1024];
  int line = 0;
  filePointer = fopen(filename, "rb");
  if (!filePointer) {
    printf("File could not be opened\n");
    return NULL;
  }
  fgets(header, 1024, filePointer);
  if (header[0] != 'P' || header[1] != '6') {
    fclose(filePointer);
    printf("Incorrect file format\n");
    return NULL;
  }
  while (fgets(header, sizeof(header), filePointer)) {
    if (header[0] != '#') {
      sscanf(header, "%d %d", w, h);
      break;
    }
  }
  fgets(header, 20, filePointer);
  struct ppm_pixel* pixelArray = (struct ppm_pixel*)malloc(sizeof(struct ppm_pixel) * (*h) * (*w));
  if (!pixelArray) {
    fclose(filePointer);
    printf("Malloc failed.");
    return NULL;
  }
  int readSize = fread(pixelArray, sizeof(struct ppm_pixel), (*w) * (*h), filePointer);
  if (readSize != (*w) * (*h)) {
    free(pixelArray);
    fclose(filePointer);
    printf("Unexpected error in reading data.");
    return NULL;
  }
  fclose(filePointer);
  return pixelArray;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}