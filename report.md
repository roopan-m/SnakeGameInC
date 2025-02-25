GAME.C

-- GLOBAL VARIABLES --
global variables are used to prevent certain variables that DO NOT CHANGE from repetitevely being included as parameters

startGame()
looks the given array, and sets up the variables for the player, snake and food.

readArray()
given a filename, it sets up an array based an contents of the file, format is displayed in Map.txt

moveUp/moveDown/moveRight/moveLeft()
checks if player is attempting to move out of bounds, and simply swaps characters in the array is a valid location is given

updateSnake()
is called until the snake has a valid location to move to, 8 selections in switch statement

checkSnakeBounds()
Checks if player is one step from the snake by going through 8 locations around the snake and checks for a 'P' character

checkStatus()
check is player is at food, returns true 


MAIN.C

the while loop runs until either food is found or the snake caught. 

while loop calls updateSnake until the location given is valid. 


