/*Lesen Sie die Vor- und Nachnamen der Personen in Ihrem Programm aus einer
ASCII-Datei mit Namen "quelle" ein und schreiben Sie diese wie in Aufgabe 3 in
umgekehrter Reihenfolge in eine andere ASCII-Datei mit Namen
"umgekehrte-reihenfolge" heraus.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 10

int main(int argc, char **argv) {
  
  // get the input and output file name from the command line arguments (assuming first input, then output)
  char *input_filename = argv[1];
  char *output_filename = argv[2];

  // check if user passed command line arguments
  if (!input_filename || !output_filename) {
    printf("You need to specify the input filename as the first and the output "
           "filename as the second argument!\n");
    return -1;
  }
  
  // get filestreams of input and output files
  FILE *input_file = fopen(input_filename, "r");
  FILE *output_file = fopen(output_filename, "w");

  // check if files could be read
  if (!input_file) {
    printf("Could not read input filename %s\n", input_filename);
    return -1;
  }

  if (!output_file) {
    printf("Could not read output filename %s\n", output_filename);
    return -1;
  }

  // read and write data
  char **names = (char **)malloc(INIT_CAPACITY * sizeof(char*));
  char line[128];
  int line_count = 0;
  int current_capacity = INIT_CAPACITY;

  while (fgets(line, sizeof(line), input_file) != NULL) {

    if (line_count >= current_capacity) {
      current_capacity *= 2;
      char **temp = (char **)realloc(names, current_capacity * sizeof(char *)); // throws error invalid next size

      // check if realloc failed
      if (!temp) {
        printf("Memoroy reallocation failed, aborting...");
        for (int i = 0; i < line_count; i++) {
          free(names[i]);
        }
        free(names);
        return -1;
      }
      names = temp;
    }

    names[line_count] = malloc(strlen(line) + 1);
    strcpy(names[line_count], line);
    // names[line_count] = line;
    line_count++;
  }

  // print to stdout (optional for debugging)
  int count = 1;
  for (int i = line_count - 1; i >= 0; i--) {
    printf("%d. Name is: %s", count,
           names[i]); // no new line char because it was already contained in
                      // the input_file
    count++;
  }

  // write to output file
  for (int i = line_count - 1; i >= 0; i--) {
    fprintf(output_file, "%s", names[i]);
    free(names[i]);
  }

  // close files and free memory
  fclose(input_file);
  fclose(output_file);
  free(names);

  return 0;
}
