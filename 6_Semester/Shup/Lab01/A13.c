#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]){

    char* all_names[argc];

    if (argc != 2){
	    printf("Invalid CLI arguments...Please only specify one argument with the number of parameters that should be read in!\n");
    return -1;
    }

    int num_args = atoi(argv[1]);

    for (int i=0; i < num_args; i++){
	    // allocate memory for pointers
	    char buffer[15];
	    printf("Enter %d. parameter: ", i+1);
	    fflush(stdout);

	    // read input
	    fgets(buffer, sizeof(buffer), stdin);
            
	    // allocate memory and copy buffer into array of pointers
	    all_names[i] = (char*)malloc(strlen(buffer) + 1);
	    strcpy(all_names[i], buffer);
    }
    
    // output in reverse order
    int count = 1;
    for (int i = num_args-1; i >= 0; i--){
	printf("%d. Parameter is: %s\n", count, all_names[i]);
        count++; 
    }
    
    // free memory
    for (int i =0; i < num_args; i++){
	free(all_names[i]);
    }



    return 0;
}
