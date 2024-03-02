#include "solver.h"
#include <stdio.h>

int tileValue(char board[9][9], int row, int col) {
    /* get the integer value of a tile
    return -1 if the tile is empty */
    if (board[row][col] == '.') {
        return -1;
    } else {
        return board[row][col] - '1';
    }
}

char intToChar(int value) {
    /* convert an integer into a sudoku number (0 -> '1', 1 -> '2', etc.)*/
    return '1' + value;
}

int getSquare(int row, int col) {
    /* calculate a tile's sqaure based on its row and column */
    return ((row / 3) * 3) + (col / 3);
}

bool prepare(char board[9][9], int rows[9], int cols[9], int squares[9]) {
    /* prepopulate the rows, cols, and squares arrays with every value that's
    already on the board 
    return false if the board is invalid */
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int square = getSquare(row, col);
            int intValue = tileValue(board, row, col);
            int candidateBits = rows[row] | cols[col] | squares[square];
            if ((candidateBits >> intValue & 1) == 1) {
                return false;
            }
            if (intValue != -1) {
                rows[row] |= (1 << intValue);
                cols[col] |= (1 << intValue);
                squares[square] |= (1 << intValue);
            }
        }
    }
    return true;
}

bool solveRecur(char board[9][9], int rows[9], int cols[9], int squares[9], int row, int col) {
    /* recursively solve the entire board */
    if (row == 9) {
        return true;
    }
    int nextrow = (col == 8 ? row + 1 : row);
    int nextcol = (col == 8 ? 0 : col + 1);

    int square = getSquare(row, col);

    int intValue = tileValue(board, row, col);

    if (intValue != -1) { // skip tiles that already have numbers
        return solveRecur(board, rows, cols, squares, nextrow, nextcol);
    }
    // get the possible values for the tile's row, column and square
    int rowBits = rows[row];
    int colBits = cols[col];

    int squareBits = squares[square];

    // OR them all together to get the final candidates
    int candidateBits = rowBits | colBits | squareBits;

    for (int i = 0; i < 9; i++) {
        // iterate through each bit and only attempt the 0 bits 
        if ((candidateBits >> i & 1) == 0) { 
            // set the bit to 1
            rows[row] |= (1 << i);
            cols[col] |= (1 << i);
            squares[square] |= (1 << i);
            board[row][col] = intToChar(i);
            if (solveRecur(board, rows, cols, squares, nextrow, nextcol)) {
                return true;
            }
            // if the bit didn't work out, reset it to 0
            rows[row] &= ~(1 << i);
            cols[col] &= ~(1 << i);
            squares[square] &= ~(1 << i);
        }
    }

    board[row][col] = '.';
    return false;
}

bool solve(char board[9][9]) {
    /* set up the recursion function and run it 
    return false if the board is unsolvable */
    int rows[9] = {0};
    int cols[9] = {0};
    int squares[9] = {0};
    if (!prepare(board, rows, cols, squares)) {
        return false;
    }
    return solveRecur(board, rows, cols, squares, 0, 0);
}
