#ifndef ARRAY
#define ARRAY


char** createArray(int rows, int columns);

void printArray(int rows, int columns, char** array);

void freeArray(char **array, int rows, int columns);

char** saveArray(char **array, int rows, int columns);

char** readArray(char* fileName, int *rows, int *columns);


#endif