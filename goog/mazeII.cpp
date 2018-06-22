/*
 * There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
 *
 * Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.
 *
 * The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.
 *
 * Example 1
 *
 * Input 1: a maze represented by a 2D array
 *
 * 0 0 1 0 0
 * 0 0 0 0 0
 * 0 0 0 1 0
 * 1 1 0 1 1
 * 0 0 0 0 0
 *
 * Input 2: start coordinate (rowStart, colStart) = (0, 4)
 * Input 3: destination coordinate (rowDest, colDest) = (4, 4)
 *
 * Output: 12
 * Explanation: One shortest way is : left -> down -> left -> down -> right -> down -> right.
 * The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.
 *
 * Example 2
 *
 * Input 1: a maze represented by a 2D array
 *
 * 0 0 1 0 0
 * 0 0 0 0 0
 * 0 0 0 1 0
 * 1 1 0 1 1
 * 0 0 0 0 0
 *
 * Input 2: start coordinate (rowStart, colStart) = (0, 4)
 * Input 3: destination coordinate (rowDest, colDest) = (3, 2)
 *
 * Output: -1
 * Explanation: There is no way for the ball to stop at the destination.
 * Note:
 * There is only one ball and one destination in the maze.
 * Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
 * The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
 * The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.
*/
#include<iostream>
#include<vector>
#include<list>
#include<unordered_set>
#include<queue>


using std::pair;
using std::list;
using std::vector;
using std::cout;
using std::endl;
using std::make_pair;
using std::priority_queue;

/* BFS

int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {

    // assume the input is valid, skip the exception handling here

    // the shortest distance from start to [i,j] so far
    // -1: not visited
    vector<vector<int>> visited(maze.size(), vector<int>(maze[0].size(), -1));

    list<pair<int, int>> queue;
    vector<pair<int, int>> next = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // U,D,L,R

    int res = 0;
    int dist = -1;
    queue.push_back(make_pair(start[0], start[1]));
    visited[start[0]][start[1]] = res;

    while (queue.size() > 0) {
        pair<int, int> tmp =  queue.front();
        queue.pop_front();
        if (tmp.first == destination[0] && tmp.second == destination[1]) {
            if (dist < 0 || dist > visited[tmp.first][tmp.second]) {
                dist = visited[tmp.first][tmp.second];
            }
        }
        // now add the possible next stops
        // if discovered a shorter way to reach a particular node, put the node
        // back in queue
        for (auto n : next) {
            int i = tmp.first + n.first, j = tmp.second + n.second;
            res = visited[tmp.first][tmp.second];
            while (i >= 0 && i < maze.size() && j >= 0 && j < maze[i].size() && maze[i][j] == 0) {
                i += n.first;
                j += n.second;
            }
            i -= n.first;
            j -= n.second;
            res += (((i > tmp.first)?(i - tmp.first):(tmp.first - i))
                + ((j > tmp.second)?(j - tmp.second):(tmp.second - j)));
            // if this reaches the destination, it'll be longer path than
            // what's already found, no need to continue
            if (dist > 0 && res > dist)
                continue;
            if (visited[i][j] < 0 || visited[i][j] > res) {
                queue.push_back(make_pair(i, j));
                visited[i][j] = res;
            }
        }
    }
    return dist;
}
*/

/* Dijkstra's algorithm, implemented by min heap (priority queue) */

struct qnode {
    int i, j, dist;
    qnode(int i0, int j0, int dist0):i(i0), j(j0), dist(dist0) {}

};

struct qnodeCompare {
    bool operator()(const qnode& a, const qnode& b) {
        return a.dist > b.dist;
    }
};

int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {

    // assume the input is valid, skip the exception handling here

    // the shortest distance from start to [i,j] so far
    // -1: not visited
    vector<vector<int>> visited(maze.size(), vector<int>(maze[0].size(), -1));

    priority_queue<qnode, vector<qnode>, qnodeCompare> queue;
    vector<pair<int, int>> next = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // U,D,L,R

    int res = 0;
    int dist = -1;
    queue.push(qnode(start[0], start[1], res));
    visited[start[0]][start[1]] = res;

    while (queue.size() > 0) {
        qnode tmp =  queue.top();
        queue.pop();
        if (tmp.i == destination[0] && tmp.j == destination[1]) {
            if (dist < 0 || dist > visited[tmp.i][tmp.j]) {
                dist = visited[tmp.i][tmp.j];
            }
        }
        // now add the possible next stops
        // if discovered a shorter way to reach a particular node, put the node
        // back in queue
        for (auto n : next) {
            int i = tmp.i + n.first, j = tmp.j + n.second;
            res = visited[tmp.i][tmp.j];
            while (i >= 0 && i < maze.size() && j >= 0 && j < maze[i].size() && maze[i][j] == 0) {
                i += n.first;
                j += n.second;
            }
            i -= n.first;
            j -= n.second;
            res += (((i > tmp.i)?(i - tmp.i):(tmp.i - i))
                + ((j > tmp.j)?(j - tmp.j):(tmp.j - j)));
            // if this reaches the destination, it'll be longer path than
            // what's already found, no need to continue
            if (dist > 0 && res > dist)
                continue;
            if (visited[i][j] < 0 || visited[i][j] > res) {
                queue.push(qnode(i, j, res));
                visited[i][j] = res;
            }
        }
    }
    return dist;
}

int main() {
    vector<vector<int>> maze = {{0, 0, 1, 0, 0}, {0, 0, 0, 0, 0},
                                {0, 0, 0, 1, 0}, {1, 1, 0, 1, 1},
                                {0, 0, 0, 0, 0}};
    vector<int> start = {0, 4};
    vector<int> destination = {4, 4};
    int res = shortestDistance(maze, start, destination);
    cout << "Can the ball go from [" << start[0] << ", " << start[1] << "] to ["
        << destination[0] << ", " << destination[1] << "] : "
        << ((res > 0)?("yes"):("no")) << endl;
    if (res > 0)
        cout << "The shortest distance is : " << res << endl;
    return 0;
}
