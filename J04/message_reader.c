#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct meta_data {
  float version;
  unsigned int year;
  unsigned int length;
};

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Error: Please enter a file");
    exit(1);
  }
  FILE *filePointer;
  char header[1024];
  filePointer = fopen(argv[1], "rb");
  if (!filePointer) {
    printf("File could not be opened\n");
    exit(1);
  }
  fgets(header, 20, filePointer);
  printf("Comment: %s\n", header);
  struct meta_data* data = (struct meta_data*)malloc(sizeof(struct meta_data));
  fread(data, 4, 3, filePointer);
  printf("Version: %.2f \n", data->version);
  printf("Year: %d \n", data->year);
  printf("Length: %d \n", data->length);
  fgets(header, 1024, filePointer);
  printf("Message: %s", header);
  if (data->length > 1024) {
    printf("... etc");
  }
  else {
    printf("\n");
  }
  free(data);
  fclose(filePointer);
  return 0;
}
