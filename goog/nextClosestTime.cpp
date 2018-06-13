/*
 * Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no limit on how many times a digit can be reused.
 *
 * You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.
 *
 * Example 1:
 *
 * Input: "19:34"
 * Output: "19:39"
 * Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours and 59 minutes later.
 * Example 2:
 *
 * Input: "23:59"
 * Output: "22:22"
 * Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22. It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.
 *
 */

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

string nextClosestTime(string time) {
    // assume the input time is all valid HH:MM
    vector<char> digits;
    for (auto t : time) {
        if (isdigit(t)) {
            digits.push_back(t);
        }
    }
    sort(digits.begin(), digits.end());
    //cout<<"the sorted digits are " << string(digits.begin(), digits.end()) << endl;

    // hard coded bounds for fixed format
    char bounds[5] = {'2', '3', ':', '5', '9'};
    if (time[0] < '2') {
        bounds[1] = '9';
    }

    int i;
    for (i = (int)time.size() - 1; i >= 0; --i) {
        if (!isdigit(time[i])) {
            continue;
        }
        if (time[i] < bounds[i]) {
            // get the very next digit larger than current
            auto it = upper_bound(digits.begin(), digits.end(), time[i]);
            if (it != digits.end() && *it <= bounds[i]) {
                time[i] = *it;
                break;
            }
        }
        time[i] = digits.front();
    }
    return time;
}

int main() {
    vector<string> tests = {"19:34", "23:59", "02:42", "13:55", "20:48"};
    for (auto t : tests) {
        cout << "current time: " << t << endl;
        cout << "next time slot: " << nextClosestTime(t) << endl;
        cout << endl;
    }
    return 0;
}
