#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdio.h>
#include <ncurses.h>
void printBoard(char board[9][9]);
void inputBoard(char board[9][9]);
void waitForExit();
#endif