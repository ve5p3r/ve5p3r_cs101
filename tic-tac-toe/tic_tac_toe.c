#include <stdio.h>

#define BOARD_SIZE 3

// labels the empty spaces from 1 to 9
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE])
{
    int row;
    int column;
    char position = '1';

    for (row = 0; row < BOARD_SIZE; row++) {
        for (column = 0; column < BOARD_SIZE; column++) {
            board[row][column] = position;
            position++;
        }
    }
}

// shows the current board
void printBoard(char board[BOARD_SIZE][BOARD_SIZE])
{
    int row;

    printf("\n");
    for (row = 0; row < BOARD_SIZE; row++) {
        printf(" %c | %c | %c \n", board[row][0], board[row][1], board[row][2]);
        if (row < BOARD_SIZE - 1) {
            printf("---+---+---\n");
        }
    }
    printf("\n");
}

// checks rows, columns and diagonals
int hasWinner(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    int i;

    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player &&
            board[i][2] == player) {
            return 1;
        }
        if (board[0][i] == player && board[1][i] == player &&
            board[2][i] == player) {
            return 1;
        }
    }

    if (board[0][0] == player && board[1][1] == player &&
        board[2][2] == player) {
        return 1;
    }
    if (board[0][2] == player && board[1][1] == player &&
        board[2][0] == player) {
        return 1;
    }

    return 0;
}

int makeMove(char board[BOARD_SIZE][BOARD_SIZE], int position, char player)
{
    int row;
    int column;

    if (position < 1 || position > 9) {
        return 0;
    }

    // turns chosen number into a row and column
    row = (position - 1) / BOARD_SIZE;
    column = (position - 1) % BOARD_SIZE;

    // leaves spaces that are already taken alone
    if (board[row][column] == 'X' || board[row][column] == 'O') {
        return 0;
    }

    board[row][column] = player;
    return 1;
}

int main(void)
{
    char board[BOARD_SIZE][BOARD_SIZE];
    char player = 'X';
    int position;
    int moves = 0;

    initializeBoard(board);
    printf("Tic-Tac-Toe\n");

    // nine valid moves fill board
    while (moves < 9) {
        printBoard(board);
        printf("Player %c, choose a position (1-9): ", player);

        if (scanf("%d", &position) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        if (!makeMove(board, position, player)) {
            printf("That position is not available.\n");
            continue;
        }

        moves++;
        if (hasWinner(board, player)) {
            printBoard(board);
            printf("Player %c wins!\n", player);
            return 0;
        }

        // switches to other player
        player = (player == 'X') ? 'O' : 'X';
    }

    printBoard(board);
    printf("The game is a draw.\n");
    return 0;
}
