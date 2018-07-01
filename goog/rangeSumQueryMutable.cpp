/* LC 308. Range Sum Query 2D - Mutable
 *
 * Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
Note:
The matrix is only modifiable by the update function.
You may assume the number of calls to update and sumRegion function is distributed evenly.
You may assume that row1 ≤ row2 and col1 ≤ col2.

*/

#include<vector>
#include<iostream>

using std::vector;
using std::cout;
using std::endl;

// solution: to use quad tree or binary index tree
// query (get sum): O(log(n)), update: O(log(n))
// if only calcated a sum matrix, query O(1), but update: O(n)
class NumMatrix {
private:
    vector<vector<int>> bit; // 2D binary index tree
    vector<vector<int>> matrix;
    int queryInternal(int row, int col) {
        int res = 0;
        int i = row, j;
        while (i > 0) {
            j = col;
            while (j > 0) {
                res += bit[i][j];
                j = j - (j & (-j));
            }
            i = i - (i & (-i));
        }
        return res;
    }

    void updateInternal(int row, int col, int val) {
        int i = row, j;
        while (i < bit.size()) {
            j = col;
            while (j < bit[i].size()) {
                bit[i][j] += val;
                j = j + (j & (-j));
            }
            i = i + (i & (-i));
        }
    }

public:
    NumMatrix(vector<vector<int>> matrix) {
        this->matrix = matrix;
        // handle the same if matrix is empty, how to get the col size
        bit = vector<vector<int>>(matrix.size()+1, vector<int>(((matrix.size())?(matrix[0].size()):0)+1, 0));
        int i, j;
        for (i = 0; i < matrix.size(); ++i) {
            for (j = 0; j < matrix[i].size(); ++j) {
                updateInternal(i + 1, j + 1, matrix[i][j]);
            }
        }
    }

    void update(int row, int col, int val) {
        int i, j;
        int diff = val - matrix[row][col];
        if (diff == 0) return;

        matrix[row][col] = val;
        updateInternal(row + 1, col + 1, diff);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        // assume the input is valid
        return (queryInternal(row2+1, col2+1) - queryInternal(row2+1, col1)
            - queryInternal(row1, col2+1) + queryInternal(row1, col1));
    }
};

int main() {
    //vector<vector<int>> matrix;
    vector<vector<int>> matrix = {{3,0,1,4,2},{5,6,3,2,1},{1,2,0,1,5},{4,1,0,1,7},{1,0,3,0,5}};
    int row1 = 2, col1 = 1, row2 = 4, col2 = 3;
    NumMatrix *obj = new NumMatrix(matrix);
    int res = obj->sumRegion(row1, col1, row2, col2);
    cout << res << endl;
}
