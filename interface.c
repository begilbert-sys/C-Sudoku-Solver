#include "interface.h"

#define BLANK_TILE ACS_BULLET

void printRow(int leftPiece, int betweenPiece, int dividingPiece, int rightPiece) {
    /* 
    draw one row of the board
    the args represent the symbols used to draw the row
    */
    addch(leftPiece);
    for (int i = 0; i < 23; i++) {
        if (i == 7 || i == 15) {
            addch(dividingPiece);
        } else {
            addch(betweenPiece);
        }
    }
    addch(rightPiece);
}

void printBoard(char board[9][9]) {
    /*
    print the sudoku board
    the ACS variables are just constants representing the symbols used to draw 
    */
    refresh();
    move(0, 0);
    // top row
    printRow(ACS_ULCORNER, ACS_HLINE, ACS_TTEE, ACS_URCORNER);
    int row = 0;
    for (int y = 1; y < 12; y++) {
        move(y, 0);
        if (y == 4 || y == 8) {
            // dividing row
            printRow(ACS_LTEE, ACS_HLINE, ACS_PLUS, ACS_RTEE);
        } else {
            // row with numbers 
            printRow(ACS_VLINE, ' ', ACS_VLINE, ACS_VLINE);
            int col = 0;
            for (int x = 2; x < 24; x += 2) {
                if (x % 8 != 0) { // skip the dividing columns
                    move(y, x);
                    if (board[row][col] == '.') {
                        addch(BLANK_TILE);
                    } else {
                        addch(board[row][col]);
                    }
                    col++;
                }
            }
            row++;
        }
    }
    // bottom row
    move(12, 0);
    printRow(ACS_LLCORNER, ACS_HLINE, ACS_BTEE, ACS_LRCORNER);
}

void inputBoard(char board[9][9]) {
    /*
    initialize ncurses, and wait for the user to enter their sudoku board 
    */
    initscr();
    keypad(stdscr, TRUE);
    printBoard(board);
    int cursorY = 1;
    int cursorX = 2;
    int row = 0;
    int col = 0;
    bool done = false;
    while (!done) {
        move(0, 0);
        move(cursorY, cursorX);
        int ch = getch();
        switch (ch) {
            case KEY_DOWN:
                if (cursorY < 11) {
                    // skip over dividng rows
                    (cursorY + 1) % 4 == 0 ? (cursorY += 2) : (cursorY++);
                    row++;
                }
                break;
            case KEY_UP:
                if (cursorY > 1) {
                    (cursorY - 1) % 4 == 0 ? (cursorY -= 2) : (cursorY--);
                    row--;
                }
                break;
            case KEY_RIGHT:
                if (cursorX < 22) {
                    (cursorX + 2) % 8 == 0 ? (cursorX += 4) : (cursorX += 2);
                    col++;
                }
                break;
            case KEY_LEFT:
                if (cursorX > 2) {
                    (cursorX - 2) % 8 == 0 ? (cursorX -= 4) : (cursorX -= 2);
                    col--;
                }
                break;

            case KEY_BACKSPACE:
            case KEY_DC:
            case 127: // 127 is the backspace key on my computer
                board[row][col] = '.';
                printBoard(board);
                break;

            case KEY_ENTER:
            case 10: // 10 is the enter key on my computer
                done = true;
                break;

            default: 
                if ('0' < ch && ch <= '9') {
                    board[row][col] = ch;
                    printBoard(board);
                }
                printBoard(board);
                break;
        }
    }
}

void waitForExit() {
    /* 
    wait for the user to press "enter" 
    */
    move(13, 0);
    printw("Press [ENTER] key to exit");
    bool done = false;
    while (!done) {
        int ch = getch();
        switch (ch) {
            case KEY_ENTER:
            case 10:
                done = true;
        }
    }
}