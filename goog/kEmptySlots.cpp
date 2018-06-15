/**
 * There is a garden with N slots. In each slot, there is a flower. The N flowers will bloom one by one in N days. In each day, there will be exactly one flower blooming and it will be in the status of blooming since then.
 *
 * Given an array flowers consists of number from 1 to N. Each number in the array represents the place where the flower will open in that day.
 *
 * For example, flowers[i] = x means that the unique flower that blooms at day i will be at position x, where i and x will be in the range from 1 to N.
 *
 * Also given an integer k, you need to output in which day there exists two flowers in the status of blooming, and also the number of flowers between them is k and these flowers are not blooming.
 *
 * If there isn't such day, output -1.
 *
 * Example 1:
 * Input:
 * flowers: [1,3,2]
 * k: 1
 * Output: 2
 * Explanation: In the second day, the first and the third flower have become blooming.
 * Example 2:
 * Input:
 * flowers: [1,2,3]
 * k: 1
 * Output: -1
 * Note:
 * The given array will be in the range [1, 20000].
 */
#include<iostream>
#include<vector>
#include<unordered_map>
#include<list>

using namespace std;
/* Solution 1:
int kEmptySlots(vector<int>& flowers, int k) {
    vector<int> blooming;
    if (flowers.size() < 2) return -1;
    blooming.push_back(flowers[0]);
    int i = 1;
    while (i < flowers.size()) {
        vector<int>::iterator it = lower_bound(blooming.begin(), blooming.end(), flowers[i]);
        if (it != blooming.end()) {
            if (*it - flowers[i] - 1 == k) {
                return i + 1;
            }
        }
        if (it != blooming.begin()) {
            --it;
            if (flowers[i] - *it - 1 == k) {
                return i + 1;
            }
        }
        if (*it > flowers[i]) {
            blooming.insert(it, flowers[i]);
        } else {
            blooming.insert(it+1, flowers[i]);
        }
        ++i;
    }
    return -1;
}
*/
/* Solution #2 */
// within a window of k slots in flower bed, the earliest/smallest date of bloom
// is larger than the left and right neighbors
// in other words, when the neighbors slots have bloomed, the k slots in between
// have not yet
// also note that, if a window [i1, j1] is a candidate
// and i1 < i2 < j1 < j2, window [i2, j2] cannot be a candidate
// because dates[i2] > dates[j1] and a candidate has dates[j1] > dates[i2] or dates[j2]

int kEmptySlots(vector<int>& flowers, int k) {
    // convert flowers (index start from 1) to dates (index start from 0) by slot
    vector<int> dates(flowers.size());
    int i, j, m;
    for (i = 0; i < flowers.size(); ++i) {
        dates[flowers[i]-1] = i;
    }
    int res = -1;

    // do a sliding window of size k
    // i is left neighbor, j is right neighbor
    i = 0;
    j = i + k + 1;
    bool cont;
    while (j < dates.size()) {
        m = i + 1;
        cont = true;
        while (m < j) {
            if (dates[m] < dates[i] || dates[m] < dates[j]) {
                // this window cannot be a candidate
                // previous iterations pass without coming in here,
                // which means, in between dates[i] and dates[m]
                // all are larger than dates[i]
                // so they cannot be the start of a candidate window
                // the window contains dates[m] that is earlier than them
                i = m;
                j = i + k + 1;
                cont = false;
                break;
            }
            ++m;
        }
        if (cont) {
            // this means the above window is a candidate
            if (res == -1 || res > max(dates[i], dates[j]) + 1){
                res = max(dates[i], dates[j]) + 1;
            }
            i = j;
            j = i + k + 1;
        }
    }
    return res;
}

int main() {
    vector<pair<vector<int>, int>> tests = {{{1, 3, 2}, 1}, {{1, 2, 3}, 1}, {{1, 2, 3, 4, 5, 7, 6}, 1}, {{6,5,8,9,7,1,10,2,3,4}, 2}};
    for (auto t : tests) {
        cout << "the flower bloom sequence: ";
        for (auto f : t.first) {
            cout << f << " ";
        }
        cout << endl;
        int res = kEmptySlots(t.first, t.second);
        if (res == -1) {
            cout << "any given day none of two blooming flowers have " << t.second << " slots between them" << endl;
        } else {
            cout << "on day #" << res << " two blooming flowers have " << t.second << " slots between them" << endl;
        }
    }
    return 0;
}
