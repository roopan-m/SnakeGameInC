#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Values do not change after intial intialisation, keep track of constants*/
char *foodLocation;
int matrix_rows;
int matrix_columns;


void startGame(char **array, int m_rows, int m_columns, int *playerRow, int *playerCol, int *snakeRow, int *snakeCol){
    matrix_rows = m_rows;
    matrix_columns = m_columns;

    for(int i=0; i<matrix_rows; i++){
        for(int j=0; j<matrix_columns; j++){
            char ch = array[i][j];

            switch(ch){
                case 'P':
                    *playerRow = i;
                    *playerCol = j;
                    break;
                case '@':
                    foodLocation = &array[i][j];
                    break;
                case '~':
                    *snakeRow = i;
                    *snakeCol = j;
                    break;
                default:
                    break;
            }
        }
    }
}

/** Copy of the above function without dimension or food cords since those dont change when we undo */
char** undoMovement(char **array, int *playerRow, int *playerCol, int *snakeRow, int *snakeCol){
    if(array == NULL){
        return NULL;
    }

    for(int i=0; i<matrix_rows; i++){
        for(int j=0; j<matrix_columns; j++){
            char ch = array[i][j];

            switch(ch){
                case 'P':
                    *playerRow = i;
                    *playerCol = j;
                    break;
                    break;
                case '~':
                    *snakeRow = i;
                    *snakeCol = j;
                    break;
                default:
                    break;
            }
        }
    }

    return array;
}

void moveUp(char **array, int *row, int *column){
    if(*row - 1 >= 0){
        array[ *row - 1 ][ *column ] = 'P';
        array[ *row ][ *column ] = ' ';
        *row = *row - 1;
    }
    else{
        array[ *row ][ *column ] = ' ';
        array[ matrix_rows-1 ][ *column ] = 'P';
        *row = matrix_rows-1;
    }
}

void moveDown(char **array, int *row, int *column){
    if(*row + 1 < matrix_rows){
        array[ *row + 1 ][ *column ] = 'P';
        array[ *row ][ *column ] = ' ';
        *row = *row + 1;
    }
    else{
        array[ 0 ][ *column ] = 'P';
        array[ *row ][ *column ] = ' ';
        *row = 0;
    }
}

void moveRight(char **array, int *row, int *column){
    if( *column + 1 < matrix_columns){
        array[ *row ][ *column + 1 ] = 'P';
        array[ *row ][ *column ] = ' ';
        *column = *column + 1;
    }
    else{
        array[ *row ][ 0 ] = 'P';
        array[ *row ][ *column ] = ' ';
        *column = 0;
    }
}

void moveLeft(char **array, int *row, int *column){
    if( *column - 1 >= 0){
        array[ *row ][ *column - 1 ] = 'P';
        array[ *row ][ *column ] = ' ';
        *column = *column - 1;
    }
    else{
        array[ *row ][ matrix_columns-1 ] = 'P';
        array[ *row ][ *column ] = ' ';
        *column = matrix_columns-1;
    }
}

/** Snake Specific Methods */

bool updateSnake(char **array, int *row, int *column, int randomSelection){
    int tempRow = (*row);
    int tempColumn = (*column);
    bool validLocation = true;

    /* Attempt to move snake randomly in a valid direction */
    switch(randomSelection){
        case 0: tempColumn++; break;
        case 1: tempColumn--; break;
        case 2: tempRow++; break;
        case 3: tempRow--; break;
        case 4: tempColumn++; tempRow--; break;
        case 5: tempColumn--; tempRow--; break;
        case 6: tempColumn++; tempRow++; break;
        case 7: tempColumn--; tempRow++; break;
    }

    /* Check if new location is within bounds */
    if(tempRow >= matrix_rows-1){
        tempRow = 0;
    }
    else if(tempRow <= 0){
        tempRow = matrix_rows-1;
    }

    if(tempColumn >= matrix_columns){
        tempColumn = 0;
    }
    else if(tempColumn <= 0){
        tempColumn = matrix_columns-1;
    }
    
    if((array[tempRow][tempColumn] == '@')){
        validLocation = false;
    }

    /** If the snake sucessfully passed all checks, overwrite new location */
    if(validLocation){
        array[tempRow][tempColumn] = '~';
        array[ *row ][ *column ] = ' ';
        (*row) = tempRow;
        (*column) = tempColumn;
    }

    return validLocation;
}

bool checkSnakeBounds(char **array, int *snakeRow, int *snakeColumn){
    /* Check for player within step of snake */

    for(int i=0; i<8; i++){

        int tempColumn = (*snakeColumn);
        int tempRow = (*snakeRow);

        switch(i){
            case 0: tempColumn++; break;
            case 1: tempColumn--; break;
            case 2: tempRow++; break;
            case 3: tempRow--; break;
            case 4: tempColumn++; tempRow--; break;
            case 5: tempColumn--; tempRow--; break;
            case 6: tempColumn++; tempRow++; break;
            case 7: tempColumn--; tempColumn++; break;
        }

        if((tempRow <= matrix_rows-1) && (tempRow >= 0)){
            if((tempColumn <= matrix_columns-1) && (tempColumn >= 0)){
                if(array[tempRow][tempColumn] == 'P'){
                    array[ *snakeRow ][ *snakeColumn ] = ' ';
                    array[tempRow][tempColumn] = '~';
                    return true;
                }
            }
        }
    }

    return false;

}

bool checkStatus(char **array, int row, int column){
    bool status = false;

    char* playerLocation = &array[row][column];
    if(playerLocation == foodLocation){
        status = true;
    }

    return status;
}



