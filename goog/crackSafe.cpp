/*
 * LC 753. Cracking the Safe

 * There is a box protected by a password. The password is n digits, where each letter can be one of the first k digits 0, 1, ..., k-1.

 * You can keep inputting the password, the password will automatically be matched against the last n digits entered.
 *
 * For example, assuming the password is "345", I can open it when I type "012345", but I enter a total of 6 digits.
 *
 * Please return any string of minimum length that is guaranteed to open the box after the entire string is inputted.
 *
 * Example 1:
 * Input: n = 1, k = 2
 * Output: "01"
 * Note: "10" will be accepted too.
 * Example 2:
 * Input: n = 2, k = 2
 * Output: "00110"
 * Note: "01100", "10011", "11001" will be accepted too.
 * Note:
 * n will be in the range [1, 4].
 * k will be in the range [1, 10].
 * k^n will be at most 4096.
 */

#include<iostream>
#include<unordered_set>
#include<string>

using std::string;
using std::cout;
using std::endl;
using std::unordered_set;

// alternative #1:
// model (n digits passcode) as a node, each node goes to next node by
// [1:] + new digit, the problem is traversing all nodes exactly once
// or finding hamilton circuit, which is NP complete problem
//
// alternative #2:
// model (first n-1 digtits of a passcode), each edge connecting two vertices
// is the last digit of this passcode
// there are (n-1)^k vertices, each has k outgoing edges
// the problem becomes finding the eulerian circuit, i.e., visting all the edges
// exactly once. There is a fleury/Hierholzer's algorithm

// during traversal, mark the complete passcode as visited when first seen
// but record the answer after the sub-traversals
// record it first, might get stuck prematurely
// if record last, although during the traversal, we can get stuck prematurely
// but the result is recorded last as if we pick the one ending prematurely last
//
void traverse(string& path, unordered_set<string>& visited, string current, int k){
    for (char i = '0'; i < (char)('0' + k); ++i) {
        string tmp = current + i;
        if (visited.count(tmp) == 0) {
            visited.insert(tmp);
            traverse(path, visited, tmp.substr(1), k);
            path += i;
        }
    }
}

string crackSafe(int n, int k) {
    // assumes k >= 1, n >= 1
    string res = "";
    if (k < 1 || n < 1) return res;

    unordered_set<string> visited;
    string start = string(n - 1, '0');
    traverse(res, visited, start, k);
    res += start;
    return res;
}

int main() {
    int n, k;

    n = 1;
    k = 2;
    cout << "n = " << n << ", k = " << k << ", password is " << (crackSafe(n, k).c_str()) << endl;
    n = 2;
    k = 2;
    cout << "n = " << n << ", k = " << k << ", password is " << (crackSafe(n, k).c_str()) << endl;
    n = 3;
    k = 2;
    cout << "n = " << n << ", k = " << k << ", password is " << (crackSafe(n, k).c_str()) << endl;
    return 0;
}
