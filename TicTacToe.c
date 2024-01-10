#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

char board[3][3];

char player;
char computer;

int toss();
int checkFreeSpaces();
char checkWinner();
void setPawn();
void getPlayerMove();
void getComputerMove();
void showBoard();
void clearBoard();

int main(){
    
    int counter = 1;  //counter variable to alternate between the player and computer moves
    int t;
    int blankSpace;
    int x = 1;
    char w;

    printf("\n***WELCOME TO TIC-TAC-TOE***\n");
    printf("\nA Toss will be performed to decide who will go first !\n\n"); 

    clearBoard();
    t = toss();
    setPawn();
    printf("\n");
    
    if(t == 1){
        printf("You have won the toss and will go first!\n\n");
        showBoard();
        getPlayerMove();
        counter++;
        printf("\n\n");
    }
    else{
        printf("Computer has won the toss and will go first!");
        getComputerMove();
        printf("\n\n");
        showBoard(); 
    }

    while(x > 0){
        if(counter % 2 == 0){
            getComputerMove();
            showBoard();
            printf("\n");
            counter--;
        }
        else{
            getPlayerMove();
            printf("\n");
            counter++;
        }

        blankSpace = checkFreeSpaces();
        w = checkWinner();

        if(w != ' '){
            if(w == player){        //show board only if tbe winner is player; This ensures that the board is not shown 2 times in a row
                showBoard();        //since if the winner is computer then it will show the board twice 
            }
            printf("\nThe winner is: %c\n", w);
            break;
        }
        else if(blankSpace == 0){
            if(counter == 2){       //show board if the last move is by the player
                showBoard();        //if the last move is by the computer the counter value will be incremented and the if condition returns false
            }
            printf("\nIts a DRAW !!!\n");
            break;
        }
        
    }
    
    return 0;
}

int toss(){
    srand(time(NULL));
    int i = rand() % 2 + 1;
    return i;
}

void setPawn(){

    fflush(stdin);
    printf("SELECT (X / O): ");
    scanf("%c", &player);
    player = toupper(player);

    if(player != 'O' && player != 'X'){
        printf("Invalid Pawn Chosen!\nTry Again !\n\n");
        setPawn();
    }

    if(player == 'O'){
        computer = 'X';
    }
    else if(player == 'X'){
        computer = 'O';
    }
}

void getPlayerMove(){

    label:
    int row, column;

    printf("\nYour move:");
    printf("\nEnter the row number #(1-3): ");
    scanf("%d", &row);
    row--;

    printf("Enter the column number #(1-3): ");
    scanf("%d", &column);
    column--;

    //checks for invalid inputs
    if(row > 2 || column > 2 || row < 0 || column < 0){  
        printf("\nInvalid Space !!!\nTry Again!\n\n");
        showBoard();
        goto label;
    }

    //places pawn in desired place
    else if(board[row][column] == ' '){
        board[row][column] = player;
    }

    //checks if space is already occupied or not
    else{
        printf("\nSpace Already Occupied !!!\nTry Again!\n\n");
        showBoard();
        goto label;
    }
}

void getComputerMove(){

    int row, column;
    srand(time(NULL));

    if(checkFreeSpaces() > 0){
 
        do{
            row = rand() % 3;
            column = rand() % 3;
        }while(board[row][column] != ' ');
        
    }

    board[row][column] = computer;

}

char checkWinner(){

    //checks the rows
    for(int row = 0; row < 3; row++){
        if(board[row][0] == board[row][1] && board[row][0] == board[row][2]){
            return board[row][0];
        }
    }

    //checks the columns
    for(int column = 0; column < 3; column++){
        if(board[0][column] == board[1][column] && board[0][column] == board[2][column]){
            return board[0][column];
        }
    }

    //checks diagonals
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[1][1];
    }
    else if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return board[1][1];
    }
    return ' ';

}

void showBoard(){
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0],board[2][1],board[2][2]);
}

void clearBoard(){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            board[x][y] = ' ';
        }
    }
}

int checkFreeSpaces(){
    int count = 9;

    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            if(board[x][y] != ' '){
                count--;
            }
        }
    }
    return count;
}
