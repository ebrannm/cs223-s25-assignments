/*----------------------------------------------
 * Author: Elisabeth Brann
 * Date: 02/07/25
 * Description: Randomly places a Wampus within a grid whose size is 
 * dictated by the user
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
  int rows;
  int columns;
  printf("Number of rows: ");
  scanf("%d", &rows);
  printf("Number of columns: ");
  scanf("%d", &columns);
  int *grid;
  grid = malloc(sizeof(int)*(rows * columns));
  srand(time(NULL));
  int wampus = rand() % ((rows * columns) + 1);
  int wampusColumn = wampus % columns;
  int wampusRow = wampus/columns;
  for (int i = 0; i < rows * columns; i++) {
    int currColumn = i%columns;
    int currRow = i/columns;
    grid[i] = abs(wampusColumn - currColumn) + abs(wampusRow - currRow);
    if (grid[i] == 0 || rows * columns == 1) {
        printf("%s ", "w");
      }
      else {
        printf("%d ", grid[i]);
      }
      if (currColumn == columns - 1) {
        printf("\n");
      }
  }
  free(grid);
  return 0;
}
