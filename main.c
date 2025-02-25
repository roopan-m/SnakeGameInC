#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "array.h"
#include "random.h"
#include "game.h"
#include "terminal.h"
#include "newSleep.h"
#include "List.h"


#define IS_ODD(a) ((a) % 2 != 0)


/**
 * @brief Assignment 2 for C and Unix Programming 
 * 
 * @author Roopan Marimuthu
 * ID: 21489965
 * 
 * @param argc 
 * @param argv 
 * @return ** int 
 */

int main(int argc, char *argv[]){

    initRandom(); 

    int rows;
    int columns;

    if(argc != 2){
        printf("Argument Error: ./eat {fileName}");
    }

    /**
     * Linked List to hold the arrays as we progress through the game, when we undo, we are simply removing last node and returning it so the
     * game can continue from that state.
     */

    char **mainArray = readArray(argv[1], &rows, &columns);

    if(mainArray == NULL){
        return 0;
    }

    LinkedList* list = createList();

    int playerRow;
    int playerColumn;
    int snakeRow;
    int snakeColumn;
    bool snakeCaught = false;
    bool foodFound = false;
    char choice;

    startGame(mainArray, rows, columns, &playerRow, &playerColumn, &snakeRow, &snakeColumn);

    system("clear");

    char **copyCurArray;

    while(!foodFound && !snakeCaught){
        /** Save array for undo function */
        copyCurArray = saveArray(mainArray, rows, columns); 
        bool validLocation = false;
        bool undo = false;

        system("tput cup 0 0");    /* This command moves the cursor to top left corner */
        newSleep(0.05);
        printArray(rows, columns, mainArray);
        printf("w) Upwards a) Left d) Right s) Downwards u) Undo\n");

        printf("\nSNAKE LOCATION: (%d, %d), PLAYER LOCATION: (%d, %d)\n", snakeRow, snakeColumn, playerRow, playerColumn);

        disableBuffer();
        scanf("%c", &choice);
        enableBuffer();


        switch(choice){
            case 'w':
                moveUp(mainArray, &playerRow, &playerColumn);
                break;
            case 'a':
                moveLeft(mainArray, &playerRow, &playerColumn);
                break;
            case 'd':
                moveRight(mainArray, &playerRow, &playerColumn);
                break;
            case 's':
                moveDown(mainArray, &playerRow, &playerColumn);
                break;
            case 'u':
                undo = true;
                char **prevArray = removeLast(list);

                if(prevArray == NULL){
                    break;
                }

                freeArray(mainArray, rows, columns);
                mainArray = prevArray;
                undoMovement(mainArray, &playerRow, &playerColumn, &snakeRow, &snakeColumn);
                
                break;

            default:
                validLocation = true;
        }


        foodFound = checkStatus(mainArray, playerRow, playerColumn);


        if(!undo){
            while(!validLocation){
                validLocation = updateSnake(mainArray, &snakeRow, &snakeColumn, randomUCP(0, 7));
            }
        }

        snakeCaught = checkSnakeBounds(mainArray, &snakeRow, &snakeColumn);

        system("clear");
        printArray(rows, columns, mainArray);

        if(snakeCaught){
            printf("You Lost!, Caught by the snake!\n");
        }
        else if(foodFound){
            printf("You Won!, Found the Food\n");
        }
        else if(!undo){
            insertLast(list, copyCurArray); 
        }
    }

    freeArray(mainArray, rows, columns);

    return 1;
}