/* LC. 694
Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Count the number of distinct islands. An island is considered to be the same as another if and only if one island can be translated (and not rotated or reflected) to equal the other.

Example 1:
11000
11000
00011
00011
Given the above grid map, return 1.
Example 2:
11011
10000
00001
11011
Given the above grid map, return 3.

Notice that:
11
1
and
 1
11
are considered different island shapes, because we do not consider reflection / rotation.
Note: The length of each dimension in the given grid does not exceed 50.
*/

#include<vector>
#include<string>
#include<unordered_set>
using std::vector, std::pair, std::sort, std::unordered_set, std::string;

class Solution {
private:
    // This function is always called with valid i, j within grid boundary
    string findEncodeIsland(vector<vector<int>>& grid, int i, int j, int M, int N) {
        vector<pair<int, int>> q;
        vector<pair<int, int>> dd = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        if (!grid[i][j]) return "";
        q.push_back({0, 0});
        //printf("Finding island\n");
        grid[i][j] = 0;
        //printf("(%d, %d), ", i, j);
        int k = 0;
        while (k < q.size()) {
            int x = i + q[k].first, y = j + q[k].second;
            for (auto d : dd) {
                int nx = x + d.first, ny = y + d.second;
                if (nx < 0 || nx >= M || ny < 0 || ny >= N || grid[nx][ny] == 0) {
                    continue;
                }
                q.push_back({nx-i, ny-j});
                //printf("(%d, %d), ", nx, ny);
                grid[nx][ny] = 0;
            }
            ++k;
        }
        // printf("\n");

        // ENCODING method #1:
        // pairs in the data vector: -(M-1) <= pair.first <= M-1
        // -(N-1) <= pair.second <= N-1
        // can add 2*M and 2*N repsectively to shift them into positive numbers
        // M, N <= 50, 2*M, 2*N <= 100, can use a single byte to represent the numbers
        // 2^8 = 256, print these modified ints to individual chars
        // then sort the modified pairs
        // concatenate them into a string as the result
        for (auto &d : q) {
            d.first += 2*M;
            d.second += 2*N;
        }
        // NOTE: there is no need to sort them
        //sort(data.begin(), data.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        //    return (a.first < b.first || (a.first == b.first && a.second < b.second));});


        vector<char> res(2*q.size());
        k = 0;
        for (auto &d : q) {
            res[k++] = static_cast<char>(d.first);
            res[k++] = static_cast<char>(d.second);
        }

        // ENCODING method #2:
        // TODO

        // for debugging

        /* for encoding method #1
        printf("This island is encoded to :\n");
        for (auto &r : res) {
            printf("%d, ", static_cast<int>(r));
        }
        printf("\n");
        */
        return string(res.begin(), res.end());
    }
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int M = grid.size(), N = (M > 0)?grid[0].size():0;
        if (!M || !N) return 0;
        int i, j, res = 0;
        // instead of unordered_set<string>
        // we can use set<vector<pair<int, int>>>, set takes a more complex ds directly
        // haven't tried, not sure it's more performant
        unordered_set<string> visited;
        for (i = 0; i < M; ++i) {
            for (j = 0; j < N; ++j) {
                if (grid[i][j]) {
                    string cur = findEncodeIsland(grid, i, j, M, N);
                    if (!visited.count(cur)) {
                        ++res;
                        visited.insert(cur);
                    }
                }
            }
        }
        return res;
    }
};

void printData(const vector<vector<int>>& data) {
    for (auto &row : data) {
        for (auto &d : row) {
            printf("%d, ", d);
        }
        printf("\n");
    }
}
int main() {
    Solution s1;
    vector<vector<vector<int>>> tests = {
        {
            {1, 1, 0, 0, 0},
            {1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1},
            {0, 0, 0, 1, 1}
        },
        {
            {1, 1, 0, 1, 1},
            {1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1},
            {1, 1, 0, 1, 1}
        }
    };
    for (auto &t : tests) {
        printData(t);
        printf("The number of distinct islands: %d\n",
               s1.numDistinctIslands(t));
    }
    return 0;
}
