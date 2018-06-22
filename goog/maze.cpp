/*
 * There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
 *
 * Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.
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
 * Output: true
 * Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.
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
 * Output: false
 * Explanation: There is no way for the ball to stop at the destination.
 *
 * Note:
 * There is only one ball and one destination in the maze.
 * Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
 * The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
 * The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.
 *
*/
#include<iostream>
#include<vector>
#include<list>
#include<unordered_set>

using std::unordered_set;
using std::pair;
using std::list;
using std::vector;
using std::cout;
using std::endl;
using std::make_pair;

/* BFS

bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {

    // assume the input is valid ?
    unordered_set<int> visited; // unordered_set doesn't support pair
                                // combine them by shifting 8, row/col size < 100
    list<pair<int, int>> queue;
    vector<pair<int, int>> next = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // U,D,L,R

    queue.push_back(make_pair(start[0], start[1]));
    visited.insert((start[0]<<8)|(start[1]));
    while (queue.size() > 0) {
        pair<int, int> tmp =  queue.front();
        queue.pop_front();
        if (tmp.first == destination[0] && tmp.second == destination[1])
            return true;
        // now add the possible next stops
        // optmize below (it has tried to go back to last spot so many times)
        for (auto n : next) {
            int i = tmp.first, j = tmp.second;
            i += n.first;
            j += n.second;
            while (i >= 0 && i < maze.size() && j >= 0 && j < maze[i].size() && maze[i][j] == 0) {
                i += n.first;
                j += n.second;
            }
            i -= n.first;
            j -= n.second;
            if (visited.count((i<<8)|j) == 0) {
                queue.push_back(make_pair(i, j));
                visited.insert((i<<8)|j);
            }
        }
    }
    return false;
}
*/

/* DFS */
bool helper(const vector<vector<int>>& maze, unordered_set<int>& visited, int i0, int j0, const vector<int>& destination) {
    if (i0 < 0 || i0 >= maze.size() || j0 < 0 || j0 > maze[i0].size())
        return false;
    if (i0 == destination[0] && j0 == destination[1])
        return true;
    visited.insert((i0<<8)|j0);
    vector<pair<int, int>> next = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // U,D,L,R
    // now add the possible next stops
    // optmize below (it has tried to go back to last spot so many times)
    for (auto n : next) {
        int i = i0 + n.first, j = j0 + n.second;
        while (i >= 0 && i < maze.size() && j >= 0 && j < maze[i].size() && maze[i][j] == 0) {
            i += n.first;
            j += n.second;
        }
        i -= n.first;
        j -= n.second;
        if (i == i0 && j == j0) continue;
        if (visited.count((i<<8)|j) == 0) {
            if (helper(maze, visited, i, j, destination))
                return true;
        }
    }
    return false;
}

bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {

    // assume the input is valid ?
    unordered_set<int> visited; // unordered_set doesn't support pair
                                // combine them by shifting 8, row/col size < 100
    return helper(maze, visited, start[0], start[1], destination);
}
int main() {
    vector<vector<int>> maze = {{0, 0, 1, 0, 0}, {0, 0, 0, 0, 0},
                                {0, 0, 0, 1, 0}, {1, 1, 0, 1, 1},
                                {0, 0, 0, 0, 0}};
    vector<int> start = {0, 4};
    vector<int> destination = {4, 4};
    bool res = hasPath(maze, start, destination);
    cout << "Can the ball go from [" << start[0] << ", " << start[1] << "] to ["
        << destination[0] << ", " << destination[1] << "] : "
        << ((res)?("yes"):("no")) << endl;
    return 0;
}
