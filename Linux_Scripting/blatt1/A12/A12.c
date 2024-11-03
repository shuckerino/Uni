#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    int num_args = atoi(argv[1]);
    char** all_names = (char**)malloc(num_args * sizeof(char*));

    if (argc != 2){
	    printf("Invalid CLI arguments...Please only specify one argument with the number of parameters that should be read in!\n");
        return -1;
    }

    for (int i=0; i < num_args; i++){
	    // allocate memory for pointers
	    char buffer[15];
	    printf("Enter %d. name: ", i+1);
	    fflush(stdout);

	    // read input
	    if (fgets(buffer, sizeof(buffer), stdin) == NULL){
            printf("Error reading input!!");
            return -1;
        };
            
	    // allocate memory and copy buffer into array of pointers
	    all_names[i] = (char*)malloc(strlen(buffer) + 1);
	    strcpy(all_names[i], buffer);
    }
    
    // output in reverse order
    int count = 2;
    for (int i = num_args-1; i >= 0; i--){
	printf("%d. name: %s\n", count, all_names[i]);
        count++; 
    }
    
    // free memory
    for (int i =0; i < num_args; i++){
	free(all_names[i]);
    }



    return 0;
}
