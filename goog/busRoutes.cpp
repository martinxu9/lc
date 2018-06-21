/*
 * We have a list of bus routes. Each routes[i] is a bus route that the i-th bus repeats forever. For example if routes[0] = [1, 5, 7], this means that the first bus (0-th indexed) travels in the sequence 1->5->7->1->5->7->1->... forever.
 *
 * We start at bus stop S (initially not on a bus), and we want to go to bus stop T. Travelling by buses only, what is the least number of buses we must take to reach our destination? Return -1 if it is not possible.
 *
 * Example:
 * Input:
 * routes = [[1, 2, 7], [3, 6, 7]]
 * S = 1
 * T = 6
 * Output: 2
 * Explanation:
 * The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
 * Note:
 *
 * 1 <= routes.length <= 500.
 * 1 <= routes[i].length <= 500.
 * 0 <= routes[i][j] < 10 ^ 6.
 *
 */

#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using std::vector;
using std::cout;
using std::unordered_map;
using std::unordered_set;
using std::endl;

int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
    if (S == T) return 0;
    // construct mapping: bus stop -> all buse routes that has this stop
    unordered_map<int, unordered_set<int>> stop_buses;
    int i, j;
    for (i = 0; i < routes.size(); ++i) {
        for (j = 0; j < routes[i].size(); ++j) {
            stop_buses[routes[i][j]].insert(i);
        }
    }
    int res = 0;
    unordered_set<int> reachable, next, buses_taken;
    reachable.insert(S);
    // loop while we haven't tried all buses
    while (reachable.size() > 0) {
        // found it
        if (reachable.count(T)) {
            return res;
        }
        // see if we can go anywhere from any of the current stops
        for (auto it = reachable.begin(); it != reachable.end(); ++it) {
            for (auto jt = stop_buses[*it].begin(); jt != stop_buses[*it].end(); ++jt) {
                if (buses_taken.count(*jt) == 0) {
                    buses_taken.insert(*jt);
                    for (i = 0; i < routes[*jt].size(); ++i) {
                        if (reachable.count(routes[*jt][i]) == 0) {
                            next.insert(routes[*jt][i]);
                        }
                    }
                }
            }
        }
        reachable = next;
        next.clear();
        ++res;
    }
    return -1;
}

int main() {
    vector<vector<int>> routes = {{1, 2, 7}, {3, 6, 7}};
    int S = 1, T = 6;
    int res = numBusesToDestination(routes, S, T);
    cout << "The minimum number of buses needed to take from " << S << " to "
        << T << " is : " << res << endl;
    return 0;
}
