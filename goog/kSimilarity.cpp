/*
LC. 854. K-Similar Strings
Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.

Given two anagrams A and B, return the smallest K for which A and B are K-similar.

Example 1:

Input: A = "ab", B = "ba"
Output: 1
Example 2:

Input: A = "abc", B = "bca"
Output: 2
Example 3:

Input: A = "abac", B = "baca"
Output: 2
Example 4:

Input: A = "aabc", B = "abca"
Output: 2
Note:


1 <= A.length == B.length <= 20
A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}
*/
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<vector>
#include<list>

using namespace std;

/* solution #1 DFS with unordered_set as next available char to swap */
/*
void dfs(string& A, const string& B, unordered_map<char, unordered_set<int>>& swaps, unordered_map<string, int>& dist, int cur) {
    int N = A.size();
    while (cur < N && A[cur] == B[cur]) {
        ++cur;
    }
    if (cur == N) return;
    // found the one needs to be swapped A[cur] ==> B[cur]
    vector<int> next(swaps[B[cur]].begin(), swaps[B[cur]].end());
    for (auto s : next) {
        int cost = dist[A];
        swaps[A[cur]].erase(cur);
        swaps[A[s]].erase(s);
        if (A[cur] != B[s]) {
            swaps[A[cur]].insert(s);
        }
        cost++;
        swap(A[cur], A[s]);
        if (dist.find(A) == dist.end() || dist[A] > cost) {
            dist[A] = cost;
            dfs(A, B, swaps, dist, cur+1);
        }
        swap(A[cur], A[s]);
        if (A[cur] != B[s]) {
            swaps[A[cur]].erase(s);
        }
        swaps[A[s]].insert(s);
        swaps[A[cur]].insert(cur);
    }

}

int kSimilarity(string& A, string& B) {
    // input is valid, A.size() == B.size()
    int N = A.size();
    if (N == 0) return 0;
    int i;
    unordered_map<char, unordered_set<int>> swaps; // the needed char from which indices
    for (i = 0; i < N; ++i) {
        if (A[i] == B[i]) continue;
        // only different chars
        swaps[A[i]].insert(i);
    }
    // two strings are identical
    if (swaps.size() == 0) return 0;
    // shortest path for graph
    // DFS?
    unordered_map<string, int> dist;
    dist[A] = 0;
    dfs(A, B, swaps, dist, 0);
    return dist[B];
}
*/

/* Solution #2, BFS, iterate through the remaining chars to find out next to swap */
int kSimilarity(string& A, string& B) {
    // input is valid, A.size() == B.size()
    int N = A.size();
    if (N == 0) return 0;
    unordered_set<string> visited;
    list<pair<string, int>> queue; // the swapped string, and which index to start scanning
    queue.push_back({A, 0});
    visited.insert(A);
    int res = 0;
    // BFS: guarantees a shortest path
    while (queue.size() > 0) {
        int k = queue.size();
        for (auto l = 0; l < k; ++l) {
            string next = move(queue.front().first);
            int i = queue.front().second;
            queue.pop_front();
            bool found = true;
            while (i < N) {
                if (next[i] != B[i]) {
                    found = false;
                    // start here
                    int j = i+1;
                    while (j < N) {
                        if (next[j] == B[i]) {
                            swap(next[i], next[j]);
                            if (!visited.count(next)) {
                                queue.push_back({next, i+1});
                                visited.insert(next);
                            }
                            swap(next[i], next[j]);
                        }
                        ++j;
                    }
                    break;
                } else {
                    ++i;
                }
            }
            if (found) return res;
        }
        ++res;
    }
    return -1; // there's guaranteed solution
}

int main() {
    vector<pair<string, string>> tests = {{"ab", "ba"}, {"ab", "ab"}, {"abcd", "cdab"}, {"abcdef", "bcdefa"}, {"", ""}, {"bca", "abc"}, {"abc", "bca"}, {"abccaacceecdeea", "bcaacceeccdeaae"}};

    for (auto t : tests) {
        printf("\"%s\", \"%s\": %d-similar\n", t.first.c_str(), t.second.c_str(), kSimilarity(t.first, t.second));
    }
    return 0;
}
