#include <stdlib.h>
#include <stdio.h>

char formatChar(char ch);

char** createArray(int rows, int columns){

    char** array = (char**)malloc(rows * sizeof(char*));

    for(int i=0; i<rows; i++){
        array[i] = (char*)malloc(columns * sizeof(char));
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            array[i][j] = ' ';
        }
    }

    return array;
}

void printArray(int rows, int columns, char** array){
    /** Prints Borders, the matrix values, and more borders */

    printf("\n");

    for(int i=-1; i<(columns); i++){
        printf("**");
    }
    printf("*\n");
    
    for(int i=0; i<rows; i++){
        printf("* ");
        for(int j=0; j<columns; j++){
            printf("%c ", array[i][j]);
        }
        printf("*\n");
    }

    for(int i=-1; i<(columns); i++){
        printf("**");
    }
    printf("*\n\n");

}

void freeArray(char **array, int rows, int columns){
    for(int i=0; i<rows; i++){
        free(array[i]);
    }
    free(array);
}

/** Deep copy the array to save for the LinkedList */
char** saveArray(char **array, int rows, int columns){
    char **copiedArray = (char**)malloc(rows * sizeof(char*));

    for(int i=0; i<rows; i++){
        copiedArray[i] = (char*)malloc(columns * sizeof(char));
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            copiedArray[i][j] = array[i][j];
        }
    }

    return copiedArray;
}

char** readArray(char *fileName, int *rows, int *columns){
    FILE *f;
    f = fopen(fileName, "r");

    char **array;

    if(f == NULL){
        perror("Error opening file.");
    }
    else{
        if(ferror(f)){
            perror("Error reading from file");
        }

        fscanf(f, "%d %d", rows, columns);

        /** Create Empty Array full of whitespace */
        array = createArray(*rows, *columns);

        char ch;

        for(int i=0; i<*rows; i++){
            for(int j=0; j<*columns; j++){

                ch = fgetc(f);
                if(ch == EOF){
                    printf("Error: File not formated correctly");
                    return NULL;
                }
                else{
                    ch = formatChar(ch);
                    if(ch != '/'){
                        array[i][j] = ch;
                    }
                    else{
                        j--;
                    }
                }
            }
            fseek(f, 1, SEEK_CUR);
        }
    }
    return array;
}

char formatChar(char ch){
    switch(ch){
        case '1':
            return 'P';
        case '2':
            return '@';
        case '3':
            return '~';
        case '0':
            return ' ';
        default:
            return '/';
    }
}




