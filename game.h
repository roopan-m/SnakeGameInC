#ifndef GAME
#define GAME

//void startGame(char** array, int randomX, int randomY, int row, int column);
void startGame(char **array, int m_rows, int m_columns, int *playerRow, int *playerCol, int *snakeRow, int *snakeCol);

void moveUp(char **array, int *row, int *column);

void moveDown(char **array, int *row, int *column);

void moveRight(char **array, int *row, int *column);

void moveLeft(char **array, int *row, int *column);

bool updateSnake(char **array, int *row, int *column, int randomSelection);

bool checkStatus(char **array, int playerRow, int playerColumn);

bool checkSnakeBounds(char **array, int *snakeRow, int *snakeColumn);

char** undoMovement(char **array, int *playerRow, int *playerCol, int *snakeRow, int *snakeCol);

#endif