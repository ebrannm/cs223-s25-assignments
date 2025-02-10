/*----------------------------------------------
 * Author: Elisabeth Brann 
 * Date: 02/14/25
 * Description: Tests whether a given matrix is a magic square.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE* arrFile;
  arrFile = stdin;
  int rows;
  int columns;
  fscanf(arrFile, "%d %d", &rows, &columns);
  if (columns != rows) {
    printf("M is NOT a magic square!");
    exit(0);
  }
  int** arr;
  arr = malloc(sizeof(int*) * rows);
  if (arr == NULL) {
    printf("Memory allocation failed for row pointers. Exiting...\n");
    exit(1);
  }
  for (int i = 0; i < rows; i++) {
    arr[i] = (int*)malloc(columns * sizeof(int));
    if (arr[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(arr[j]);
      }
      free(arr);
      printf("Memory allocation failed for column pointers. Exiting...\n");
      exit(1);
    }
  }
  for (int i = 0; i<rows; i++) {
    for (int j = 0; j < columns; j++) {
      fscanf(arrFile, "%d", &arr[i][j]);
    }
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
  int diagSum1 = 0;
  int diagSum2 = 0;
  for (int i = 0; i < columns; i++) {
    diagSum1 += arr[i][i];
    diagSum2 += arr[i][columns-1-i];
  }
  if (diagSum1 != diagSum2) {
    for (int i = 0; i < rows; i++) {
      free(arr[i]);
    }
    free(arr);
    printf("M is NOT a magic square!");
    exit(0);
  }
  for (int i = 0; i < rows; i++) {
    int rowSum = 0;
    int colSum = 0;
    for (int j = 0; j < rows; j++) {
      rowSum += arr[i][j];
      colSum += arr[j][i];
    }
    if (rowSum != colSum || colSum != diagSum1) {
      for (int j = 0; j < rows; j++) {
        free(arr[j]);
      }
      free(arr);
      printf("M is NOT a magic square!");
      exit(0);
    }
  }
  printf("%s %d%s", "M is a magic square (magic constant =", diagSum1, ")");
  for (int i = 0; i < rows; i++) {
    free(arr[i]);
  }
  free(arr);
  return 0;
}