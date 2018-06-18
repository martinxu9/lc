/**
 * In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.
 *
 * Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.  More specifically, there exists a natural number K so that for any choice of where to walk, we must have stopped at a terminal node in less than K steps.
 *
 * Which nodes are eventually safe?  Return them as an array in sorted order.
 *
 * The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.
 *
 * Example:
 * Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
 * Output: [2,4,5,6]
 * Here is a diagram of the above graph.
 *
 */
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<list>

using namespace std;

/* Solution #1, DFS, how to ensure early termination in the recursion
 * 3 colors: once started on a node, mark it as gray == 1
 * if it reaches a point of no outgoing edges, we know is safe, so mark as black == 2
 * so for a certain node, if all of the neighbors are known safe, it'll be marked safe
 * in this case, when a gray node is visited by another traversal, we know it is unsafe
*/
// @return: if current node is safe
bool traverse(const vector<vector<int>>& graph, vector<int>& safes, int current) {
    if (safes[current] == 2) {
        return true;
    } else if (safes[current] == 1) {
        return false;
    }
    safes[current] = 1;
    for (auto g : graph[current]) {
        if (safes[g] == 2) {
            continue;
        }
        if (safes[g] == 1 || !traverse(graph, safes, g)) {
            return false;
        }
    }
    safes[current] = 2;
    return true;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    vector<int> safes(graph.size(), 0); // states: 0: not visited, 1: gray, 2: black == safe
    // unordered_set<int> path; // no need for a path variable if marked 3 colors
    vector<int> res;
    for (int i = 0; i < graph.size(); ++i) {
        if (traverse(graph, safes, i)) {
            res.push_back(i);
        }
    }
    return res;
}


/* Solution #2: reverse the edges, safe nodes have no outgoing edges, so the any
nodes that are only connected to such nodes are also safe


vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    vector<unordered_set<int>> outgoing(graph.size());
    vector<vector<int>> incoming(graph.size());
    list<int> q;
    vector<bool> safes(graph.size(), false);
    vector<int> res;
    int i, j;
    for (i = 0; i < graph.size(); ++i) {
        if (graph[i].size() == 0) {
            q.push_back(i);
            continue;
        }
        for (j = 0; j < graph[i].size(); ++j) {
            outgoing[i].insert(graph[i][j]);
            incoming[graph[i][j]].push_back(i);
        }
    }

    while(!q.empty()) {
        int s = q.front();
        q.pop_front();
        safes[s] = true;
        for (i = 0; i < incoming[s].size(); ++i) {
            outgoing[incoming[s][i]].erase(s);
            if (outgoing[incoming[s][i]].size() == 0) {
                q.push_back(incoming[s][i]);
            }
        }
    }

    for (i = 0; i < graph.size(); ++i) {
        if (safes[i]) {
            res.push_back(i);
        }
    }
    return res;
}
*/
void printGraph(const vector<vector<int>>& g) {
    int i;
    for (i = 0; i < g.size(); ++i) {
        cout << i << " => ";
        for (auto nei : g[i]) {
            cout << nei << ", ";
        }
        cout << endl;
    }
}
int main() {
    vector<vector<vector<int>>> tests = {{{1,2},{2,3},{5},{0},{5},{},{}}, };
    int i;
    for (auto t : tests) {
        cout << "graph is: " << endl;
        printGraph(t);
        cout << "safe nodes are: " << endl;
        vector<int> res = eventualSafeNodes(t);
        for (i = 0; i < res.size(); ++i) {
            cout << res[i];
            if (i < res.size()-1) {
                cout << ", ";
            } else {
                cout << endl;
            }
        }
    }
    return 0;
}
