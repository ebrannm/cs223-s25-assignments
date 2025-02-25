/*----------------------------------------------
 * Author: Elisabeth Brann 
 * Date: 02/28/25
 * Description: Builds a binary search tree of a given set of files. 
 * After building the tree, gives the user a prompt to list the processed files in alphabetical order
 * and query the dependencies of a file by giving the filename.
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

void dependencyPrintHelper(struct tree_node* root, char* rootName) {
  if (root != NULL) {
    dependencyPrintHelper(root->left, rootName);
    if (strcmp(rootName, root->data.name) != 0) {
      printf("  %s\n", root->data.name);
    }
    dependencyPrintHelper(root->right, rootName);
  }
}

void dependencyPrint(struct tree_node* rootFile) {
  printf("%s has the following dependencies:\n", rootFile->data.name);
  dependencyPrintHelper(rootFile, rootFile->data.name);
}

void list(struct tree_node* fileList[], int numFiles) {
  for (int i = 0; i < numFiles; i++) {
    printf("%s\n", fileList[i]->data.name);
  }
}

int findFile(struct tree_node* fileList[], char* target, int numFiles) {
  for (int i = 0; i < numFiles; i++) {
    if (strcmp(fileList[i]->data.name, target) == 0) {
      return i;
    }
  }
  return -1; //not found
}

int compareStrings(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Please enter a file!\n");
    return 1;
  }
  qsort(argv + 1, argc - 1, sizeof(char *), compareStrings);
  printf("Processing %d files\n", argc - 1);
  clock_t start, end;
  double elapsedTime;
  start = clock();
  struct tree_node* files[20];
  for (int i = 1; i < argc; i++) {
    FILE *filePointer;
    char* fileName = argv[i];
    filePointer = fopen(fileName, "r");
    if (filePointer == NULL) {
      printf("%s can't be opened \n", fileName);
      continue;
    }
    struct tree_node* file = malloc(sizeof(struct tree_node));
    strcpy(file->data.name, fileName);
    file->left = NULL;
    file->right = NULL;
    files[i-1] = file;
    char line[256];
    while (fgets(line, sizeof(line), filePointer)) {
      if (strstr(line, "#include")) {
        char *start = strstr(line, "#include");
        if (start) {
          start += 8; 
          while (*start == ' ' || *start == '\t') {
            start++;
          }
          char dependency[256];
          if (*start == '<') {
            char *end = strchr(start, '>');
            if (end) {
              strncpy(dependency, start + 1, end - start - 1);
              dependency[end - start - 1] = '\0';
              insert(dependency, file);
            } 
          }
          else if (*start == '"') {
            char *end = strchr(start + 1, '"');
            if (end) {
              strncpy(dependency, start + 1, end - start - 1);
              dependency[end - start - 1] = '\0';
              insert(dependency, file);
            }
          }
        }
        else {
          continue;
        }
      }
    }
    fclose(filePointer);
  }
  end = clock();
  elapsedTime = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Elapsed time is %f\n", elapsedTime);
  int cont = 1;
  while (cont == 1) {
    char command[256];
    fgets(command, sizeof(command), stdin);
    strtok(command, "\n");
    if (strcmp(command, "list") == 0) {
      list(files, argc-1);
    }
    else if (strcmp(command, "quit") == 0) {
      cont = 0;
    }
    else {
      int fileIndex = findFile(files, command, argc-1);
      if (fileIndex == -1) {
        printf("%s not found\n", command);
      }
      else {
        dependencyPrint(files[fileIndex]);
      }
    }
  }
  for (int i = 0; i < argc - 1; i++) {
    clear(files[i]);
  }
  return 0;
}
