#include <stdio.h>

int main(int argc, char *argv[]){

    if (argc == 1){
        printf("There were no arguments passed! This program is only for displaying CL-Arguments, so please give me some arguments!!!\n");
        return 0;
    }
    for (int i=1; i < argc; i++){
        printf("%d. Aufrufparameter: %s", i, argv[i]);
        printf("\n");
    }

    return 0;

}
