/*
 * According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."
 *
 * Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):
 *
 * Any live cell with fewer than two live neighbors dies, as if caused by under-population.
 * Any live cell with two or three live neighbors lives on to the next generation.
 * Any live cell with more than three live neighbors dies, as if by over-population..
 * Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 * Write a function to compute the next state (after one update) of the board given its current state. The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously.
 *
 * Example:
 *
 * Input:
 * [
 *   [0,1,0],
 *   [0,0,1],
 *   [1,1,1],
 *   [0,0,0]
 * ]
 * Output:
 * [
 *   [0,0,0],
 *   [1,0,1],
 *   [0,1,1],
 *   [0,1,0]
 * ]
 * Follow up:
 *
 * Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
 * In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?
 */
#include<vector>
#include<iostream>
#include<algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::min;
using std::max;

void gameOfLife(vector<vector<int>>& board) {
    // how about just store the current and update both in the board, two bits?
    // then need to scan twice of entire board
    int i, j; // traverse the board
    int r, c; // neighbors
    for (i = 0; i < board.size(); ++i) {
        for (j = 0; j < board[i].size(); ++j) {
            int cnt = 0;
            for (r = max(0, i-1); r <= min((int)board.size()-1, i+1); ++r) {
                for (c = max(0, j-1); c <= min((int)board[i].size()-1, j+1); ++c) {
                    if (i == r && j == c) {
                        continue;
                    }
                    if ((0x1 & board[r][c])) {
                        ++cnt;
                    }
                }
            }
            if ((board[i][j] > 0 && cnt >=2 && cnt <=3) || (board[i][j] == 0 && cnt == 3)) {
                board[i][j] = (board[i][j] | (0x1 << 1));
            }
        }
    }
    for (i = 0; i < board.size(); ++i) {
        for (j = 0; j < board[i].size(); ++j) {
            board[i][j] = (board[i][j] >> 1);
        }
    }
}

void printBoard(const vector<vector<int>>& b) {
    int i, j;
    cout << "[ " << endl;
    for (i = 0; i < b.size(); ++i) {
        cout << "[ ";
        for (j = 0; j < b[i].size(); ++j) {
            cout << b[i][j];
            if (j < b[i].size()-1) {
                cout << ", ";
            }
        }
        cout << " ]" << endl;
    }
    cout << "]" << endl;
}

int main() {
    vector<vector<int>> board = {{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}};
    cout << "Current state: " << endl;
    printBoard(board);
    cout << "After update: " << endl;
    gameOfLife(board);
    printBoard(board);

    return 0;
}
