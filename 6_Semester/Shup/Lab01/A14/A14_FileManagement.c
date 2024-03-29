/*Lesen Sie die Vor- und Nachnamen der Personen in Ihrem Programm aus einer
ASCII-Datei mit Namen "quelle" ein und schreiben Sie diese wie in Aufgabe 3 in
umgekehrter Reihenfolge in eine andere ASCII-Datei mit Namen
"umgekehrte-reihenfolge" heraus.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  char *filename = argv[1];

  if (!filename) {
    printf("You need to specify the filename that should be read as the first "
           "command line argument!\n");
    return -1;
  }

  FILE *file = fopen(filename, "r");

  if (!file) {
    printf("Could not read file %s\n", filename);
    return -1;
  }

  // printf("After opening file");
  //  do stuff
  char **names = (char **)malloc(10 * sizeof(char));
  char line[128];
  int line_count = 0;
  // printf("Before while loop");

  while (fgets(line, sizeof(line), file) != NULL) {
    names[line_count] = malloc(strlen(line) + 1);
    strcpy(names[line_count], line);
    //names[line_count] = line;
    line_count++;
  }

  //fclose(file); // throws error, even when calling at end of program
    
  int count = 1;
  for (int i = line_count - 1; i >= 0; i--) {
    printf("%d. Name is: %s", count, names[i]); // no new line char because it was already contained in the file
    count++;
    free(names[i]);
  }

  free(names);

  return 0;
}
