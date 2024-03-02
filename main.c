#include "interface.h"
#include "solver.h"

void initBlankBoard(char board[9][9]) {
    /* set every tile in the board to "blank" */
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            board[row][col] = '.';
        }
    }
}
int main() {
    char board[9][9];
    initBlankBoard(board);
    inputBoard(board);

    if (solve(board)) {
        printBoard(board);
        waitForExit();
    } else {
        printf("ERROR: This board is not solvable!");
    }
    return 1;
}