#include <stdio.h>
#include <string.h>


int main(int argc, char** argv) {
  if (argc < 2) {
    printf("usage: ./message_writer filename");
    return(1);
  }
  FILE *filePointer;
  filePointer = fopen(argv[1], "wb");
  if (!filePointer) {
    printf("File could not be opened\n");
    return(1);
  }
  char* comment = "# Carl Sagan\n";
  float version = 0.10;
  int year = 1990;
  char* data = "Look again at that dot. That's here. That's home. That's us. On it is everyone you love, everyone you know.";
  int length = strlen(data);
  fwrite(comment, strlen(comment), 1, filePointer);
  fwrite(&version, sizeof(float), 1, filePointer);
  fwrite(&year, sizeof(int), 1, filePointer);
  fwrite(&length, sizeof(int), 1, filePointer);
  fwrite(data, strlen(data) + 1, 1, filePointer);
  return 0;
}
