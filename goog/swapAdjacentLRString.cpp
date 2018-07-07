/* 777. Swap Adjacent in LR String
 *
 In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR". Given the starting string start and the ending string end, return True if and only if there exists a sequence of moves to transform one string to the other.

Example:

Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
Output: True
Explanation:
We can transform start to end following these steps:
RXXLRXRXL ->
XRXLRXRXL ->
XRLXRXRXL ->
XRLXXRRXL ->
XRLXXRRLX
Note:

1 <= len(start) = len(end) <= 10000.
Both start and end will only consist of characters in {'L', 'R', 'X'}.

*
*/
#include<iostream>
using namespace std;

bool canTransform(string start, string end) {
    if (start.size() != end.size())
        return false;
    // swap only happens with L,X pair and R,X pair, not L,R pairs
    // so L and R stay the same positions relative to each other
    // also since only RX -> XR and XL -> LX are valid
    // XXXR cannot transform to RXXX
    // can transform them both
    // move all R to their right possible positions
    // BFS still works
    // what's a better solution?
    // scan both, if both are L, R, X, OK
    int i = 0, j = 0;
    while (i < start.size() && j < end.size()) {
        // start of this iteration, i == j
        while(i < start.size() && start[i] == 'X') ++i;
        while(j < end.size() && end[j] == 'X') ++j;
        if ((i == start.size()) ^ (j == end.size())) {
            return false;
        }
        // LR/RL; L cannot move right; R cannot move left
        if (start[i] != end[j] || (i < j && start[i] == 'L') || (j < i && start[i] == 'R')) {
            return false;
        }
        ++i;
        ++j;
    }
    return true;
}

int main() {
    string start = "XLXRRXXRXX", end = "LXXXXXXRRR";
    cout << start << endl;
    cout << ((canTransform(start, end))?("can"):("cannot")) << " transform to " << endl;
    cout << end << endl;
    return 0;
}
