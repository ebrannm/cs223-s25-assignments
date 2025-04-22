/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 02/21/25
 * Description: Writes a PPM image given an array of pixels. 
 * Copied from Assignment 5.
 ---------------------------------------------*/
 #include "write_ppm.h"
 #include <stdio.h>
 #include <string.h>
 
 // implement *one* (but do not remove the other one)!
 
 void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
     FILE* filePointer;
     char header[20];
     filePointer = fopen(filename, "wb");
     if (!filePointer) {
         printf("Error opening file");
         return;
     }
     fprintf(filePointer, "P6\n%d %d\n255\n", w, h);
     int writeSize = fwrite(pixels, sizeof(struct ppm_pixel), w * h, filePointer);
     if (writeSize != w * h) {
         printf("Error writing pixel data to file");
         fclose(filePointer);
         return;
     }
     fclose(filePointer);
 }
 
 void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
 
 }
 