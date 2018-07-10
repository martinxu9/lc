/*
 * 803. Bricks Falling When Hit
 * We have a grid of 1s and 0s; the 1s in a cell represent bricks.  A brick will not drop if and only if it is directly connected to the top of the grid, or at least one of its (4-way) adjacent bricks will not drop.

We will do some erasures sequentially. Each time we want to do the erasure at the location (i, j), the brick (if it exists) on that location will disappear, and then some other bricks may drop because of that erasure.

Return an array representing the number of bricks that will drop after each erasure in sequence.

Example 1:
Input:
grid = [[1,0,0,0],[1,1,1,0]]
hits = [[1,0]]
Output: [2]
Explanation:
If we erase the brick at (1, 0), the brick at (1, 1) and (1, 2) will drop. So we should return 2.
Example 2:
Input:
grid = [[1,0,0,0],[1,1,0,0]]
hits = [[1,1],[1,0]]
Output: [0,0]
Explanation:
When we erase the brick at (1, 0), the brick at (1, 1) has already disappeared due to the last move. So each erasure will cause no bricks dropping.  Note that the erased brick (1, 0) will not be counted as a dropped brick.


Note:

The number of rows and columns in the grid will be in the range [1, 200].
The number of erasures will not exceed the area of the grid.
It is guaranteed that each erasure will be different from any other erasure, and located inside the grid.
An erasure may refer to a location with no brick - if it does, no bricks drop.

*/
#include<iostream>
#include<vector>
#include<unordered_set>
#include<list>
using namespace std;

int unionFind(vector<int>& parents, int i) {
    if (parents[i] > 0 && parents[i] != i) {
        parents[i] = unionFind(parents, parents[i]);
    }
    return parents[i];
}

int helper(const vector<vector<int>>& grid, vector<int>& parents, vector<int>& cc_size, int i, int j) {
    int M = grid.size(), N = grid[0].size(); // M x N grid
    vector<vector<int>> dij = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
    int d = 0; // record the change
    int r1 = unionFind(parents, i*N + j), r2;
    for (auto dd : dij) {
        int ni = i + dd[0], nj = j + dd[1];
        if (ni >=0 && ni < M && nj >= 0 && nj < N && grid[ni][nj]) {
            r2 = unionFind(parents, ni*N+nj);
            // if r1==r2, already joined together
            if (r1 < r2) {
                if (r2 >= N && r1 < N) d+= cc_size[r2];
                cc_size[r1] += cc_size[r2];
                parents[r2] = r1;
                cc_size[r2] = 0;
            } else if (r2 < r1){
                if (r2 < N && r1 >= N) d+= cc_size[r1];
                parents[r1] = r2;
                cc_size[r2] += cc_size[r1];
                cc_size[r1] = 0;
                r1 = r2;
            }
        }
    }
    return d;
}
vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
    // reverse union-find
    // hits erase the bricks
    // we can erase them first as specified in hits. note that if erasing an empty one
    // do not add it back
    // don't need to erase the ones that would fall
    // but need to keep count of such
    // the number of bricks falling after a certain erasure is the ones inside
    // the connected component, but does not connect to a top row brick
    // until adding this erasure back

    vector<int> res(hits.size(), 0);

    if (grid.size()<=1 || grid[0].size()==0) return res;

    int M = grid.size(), N = grid[0].size(); // M x N grid
    vector<int> cc_size(M*N, 0); // for a certain i*N+j, if it is the root, it carries the size of CC
    int i, j;
    // remove the hits, also mark a certain hit as no-check if it's erasing an empty spot

    for (auto &h : hits) {
        if (grid[h[0]][h[1]]) {
            grid[h[0]][h[1]] = 0;
        } else {
            h[0] = -1; // mark it as skipped when we add the hits back in reverse order
        }
    }
    // this is the starting state
    // union find gets the root of a brick, we use i*N+j to compress the 2D into 1D

    vector<int> parents(M*N, -1);
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            if (grid[i][j]) {
                int tmp = i*N + j;
                parents[tmp] = tmp;
                cc_size[tmp] = 1;
            }
        }
    }
    vector<vector<int>> dij = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

    // first process the current connected component (CC)
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            // check the neighbors on the left and above
            if (grid[i][j]) {
                helper(grid, parents, cc_size, i, j);
            }
        }
    }

    // now put the hits back
    for (i = hits.size()-1; i >= 0; --i) {
        if (hits[i][0]<0) continue;
        int d = 0;
        int r1 = hits[i][0]*N+hits[i][1];
        parents[r1] = r1;
        d = helper(grid, parents, cc_size, hits[i][0], hits[i][1]);
        grid[hits[i][0]][hits[i][1]] = 1;
        if (d == 0) cc_size[unionFind(parents, r1)] += 1;
        res[i] = d;
    }
    return res;
}

int main() {


    vector<vector<int>> grid = {{1,0,0,0},{1,1,0,0}};
    vector<vector<int>> hits = {{1, 1}, {1, 0}};
    vector<int> res = hitBricks(grid, hits);
    for (auto r : res) {
        cout << r << ", ";
    }
    cout << endl;

    grid = {{1,0,0,0},{1,1,1,0}};
    hits = {{1, 0}};
    res = hitBricks(grid, hits);
    for (auto r : res) {
        cout << r << ", ";
    }
    cout << endl;

    grid = {{1},{1},{1},{1},{1}};
    hits = {{3,0},{4,0},{1,0},{2,0},{0,0}};
    res = hitBricks(grid, hits);
    for (auto r : res) {
        cout << r << ", ";
    }
    cout << endl;

    grid = {{1,0,1},{1,1,1}};
    hits = {{0,0},{0,2},{1,1}};
    res = hitBricks(grid, hits);
    for (auto r : res) {
        cout << r << ", ";
    }
    cout << endl;

    grid = {{1,1,1},{0,1,0},{0,0,0}};
    hits = {{0,2},{2,0},{0,1},{1,2}};
    res = hitBricks(grid, hits);
    for (auto r : res) {
        cout << r << ", ";
    }
    cout << endl;

    grid = {{0,1,1,1,1},{1,1,1,1,0},{1,1,1,1,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
    hits = {{6,0},{1,0},{4,3},{1,2},{7,1},{6,3},{5,2},{5,1},{2,4},{4,4},{7,3}};
    res = hitBricks(grid, hits);
    for (auto r : res) {
        cout << r << ", ";
    }
    cout << endl;

    grid = {{1,1,1,0,1,1,1,1},{1,0,0,0,0,1,1,1},{1,1,1,0,0,0,1,1},{1,1,0,0,0,0,0,0},{1,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0}};
    hits = {{4,6},{3,0},{2,3},{2,6},{4,1},{5,2},{2,1}};
    res = hitBricks(grid, hits);
    for (auto r : res) {
        cout << r << ", ";
    }
    cout << endl;

    grid = {{0,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{0,0,0,1,0,0,1,1,1},{0,0,1,1,0,1,1,1,0},{0,0,0,0,0,1,1,1,1},{0,0,0,0,0,0,0,1,0}};
    hits = {{1,8},{2,1},{1,4},{3,0},{3,4},{0,7},{1,6},{0,8},{2,5},{3,2},{2,0},{0,2},{0,5},{0,1},{4,8},{3,7},{0,6},{5,7},{5,3},{2,6},{2,2},{5,8},{2,8},{4,0},{3,3},{1,1},{0,0},{4,7},{0,3},{2,4},{3,1},{1,0},{5,2},{3,8},{4,2},{5,0},{1,2},{1,7},{3,6},{4,1},{5,6},{0,4},{5,5},{5,4},{1,5},{4,4},{3,5},{4,6},{2,3},{2,7}};
    res = hitBricks(grid, hits);
    for (auto r : res) {
        cout << r << ", ";
    }
    cout << endl;
    return 0;
}
