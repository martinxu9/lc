#include<iostream>
#include<vector>
#include<cstdint>
#include<list>
#include<unordered_set>

using namespace std;

typedef vector<vector<int>> board_t;
#define ROW 2
#define COL 3

uint16_t encodeBoard(const vector<vector<int>>& board) {
    // always 2 by 3
    // encode 5 digits is enough
    return ((board[0][0]&0x7)<<(3*4)) | ((board[0][1]&0x7)<<(3*3)) |
        ((board[0][2]&0x7)<<(3*2)) | ((board[1][0]&0x7)<<(3)) | (board[1][1]&0x7);
}

int slidingPuzzle(vector<vector<int>>& board) {
    int res = -1;
    list<board_t> queue; // do a BFS from the beginning state
    unordered_set<uint16_t> visited; // save the encoded value of a board
    board_t target = {{1,2,3},{4,5,0}};
    uint16_t t = encodeBoard(target);
    res = 0;
    queue.emplace_back(board);
    while(!queue.empty()) {
        int i, num = queue.size();
        for(i=0;i<num;++i) {
            board_t b = queue.front();
            queue.pop_front();
            uint16_t e = encodeBoard(b);
            if((e^t)==0) return res;
            visited.insert(e);
            int j;
            for(j=0;j<ROW*COL;++j){
                if(b[j/COL][j%COL]==0) break;
            }
            int r = j/COL, c = j%COL;
            vector<pair<int, int>> next = {{-1,0}, {1, 0}, {0, 1}, {0,-1}};
            for(j=0;j<next.size();++j) {
                if((r+next[j].first<ROW) && (r+next[j].first>=0) && (c+next[j].second>=0) && (c+next[j].second<COL)) {
                    swap(b[r][c], b[r+next[j].first][c+next[j].second]);
                    if(visited.count(encodeBoard(b))==0) {
                        queue.emplace_back(b);
                    }
                    swap(b[r][c], b[r+next[j].first][c+next[j].second]);
                }
            }
        }
        ++res;
    }
    // not found
    return -1;
}


void printBoard(const vector<vector<int>>& board) {
    for(int i=0;i<(int)board.size();++i) {
        for(int j=0;j<(int)board[i].size();++j) {
            cout<<board[i][j];
            if(j<board[i].size()-1) cout<<" ";
        }
        cout<<endl;
    }
}

int main() {
    vector<board_t> tests;
    vector<vector<int>> board = {{1,2,3}, {4,0,5}};
    tests.emplace_back(board);
    board = {{1,2,3}, {5,4,0}};
    tests.emplace_back(board);
    board = {{4,1,2}, {5,0,3}};
    tests.emplace_back(board);
    board = {{3,2,4}, {1,5,0}};
    tests.emplace_back(board);
    for(int i=0;i<(int)tests.size();++i) {
        printBoard(tests[i]);
        cout<<"least number of moves: "<<slidingPuzzle(tests[i])<<endl;
    }
    return 0;
}
