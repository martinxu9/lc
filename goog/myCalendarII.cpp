/* LC 731. My Calendar II

 Implement a MyCalendarTwo class to store your events. A new event can be added if adding the event will not cause a triple booking.

 Your class will have one method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.

 A triple booking happens when three events have some non-empty intersection (ie., there is some time that is common to all 3 events.)

 For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a triple booking. Otherwise, return false and do not add the event to the calendar.

 Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
 Example 1:
 MyCalendar();
 MyCalendar.book(10, 20); // returns true
 MyCalendar.book(50, 60); // returns true
 MyCalendar.book(10, 40); // returns true
 MyCalendar.book(5, 15); // returns false
 MyCalendar.book(5, 10); // returns true
 MyCalendar.book(25, 55); // returns true
 Explanation:
 The first two events can be booked.  The third event can be double booked.
 The fourth event (5, 15) can't be booked, because it would result in a triple booking.
 The fifth event (5, 10) can be booked, as it does not use time 10 which is already double booked.
 The sixth event (25, 55) can be booked, as the time in [25, 40) will be double booked with the third event;
 the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.
 Note:

 The number of calls to MyCalendar.book per test case will be at most 1000.
 In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].
 */

#include<map>
#include<vector>
#include<string>

using namespace std;

/* Only need to check the boundaries, start and end, use +1 and -1 to indicate those
   any overlapping start/end cancel out, so the neighboring intervals with equal weights
   are joined together naturally
*/
class MyCalendarTwo {
private:
    struct CalendarEntry{
    };
    map<int, int> booking; // start/end ->  how many times: if start: ++, if end: --
    int limit;
public:
    MyCalendarTwo() {
        this->limit = 2;
    }

    bool book(int start, int end) {
        map<int, int>::iterator it;
        if ((it = booking.find(start)) == booking.end()) {
            it = booking.insert({start, 0}).first;
        }
        it->second++;
        if ((it = booking.find(end)) == booking.end()) {
            it = booking.insert({end, 0}).first;
        }
        it->second--;
        int times = 0;
        for (it = booking.begin(); it != booking.end(); ++it) {
            times += it->second;
            if (times > this->limit) {
                // not bookable, reverse the insert and return false
                booking[start]--;
                booking[end]++;
                return false;
            }
        }
        return true;
    }
};

/* Solution #2, too complicated to write
   memory O(n)
   time: between O(nlog) and O(n^2)
*/
/*
class MyCalendarTwo {
private:
    struct CalendarEntry{
        int end; // end of an interval [start, end)
        int times; // how many times it has been booked;
        CalendarEntry(int e, int t): end(e), times(t) {}
        CalendarEntry(): end(0), times(0) {}
    };
    int limit;
    map<int, CalendarEntry> booking; // start -> end, how many times [start, end) booked
public:
    MyCalendarTwo() {
        limit = 2;
    }

    bool book(int start, int end) {
        // assume we never have the case of start==end, or simply return true;
        if (start==end) return true;

        map<int, CalendarEntry>::iterator left = booking.end(), right, right_end, it;
        right = booking.lower_bound(start); // first key in map not smaller than start
        // end could potentially cover right or even beyond, i.e. end > right.
        if (right != booking.end()) {
            right_end = booking.upper_bound(end);
            it = right;
            while (it != right_end) {
                if (end > it->first && it->second.times >= this->limit) {
                    return false;
                }
                ++it;
            }

        }
        if (right != booking.begin()) {
            left = right;
            --left;
            if (left->second.end > start && left->second.times >= this->limit) return false;
        }
        // add the new reservation into the system
        // consider overlaps; left->first < start because of the lower_bound if left exits
        //   left               right (*n) could be multiple
        // |___________|      |__________| |_| |_|
        //   start  end           end                 end
        //     |____|..__________..|__..............__|
        // update any intervals overlapped
        if (right != booking.end() && end > right->first) {
            int n_end = min(right->first, end);
            it = right;
            int r_start = start, r_end = end, r_times; // may need to append a new element after merging
            while (it != right_end && r_end > it->first) {
                r_start = min(it->second.end, end);
                r_end = max(it->second.end, end);
                r_times = ((end < it->second.end)?(it->second.times):(1));
                it->second.end = r_start;
                it->second.times++;
                ++it;
            }
            if (r_start < r_end) booking[r_start] = CalendarEntry(r_end, r_times);
            end = n_end;
        }
        if (left != booking.end()) {
            if (left->second.end == start && left->second.times == 1) {
                // instead of a new one, merge into it
                left->second.end = end;
                start = end;
            } else if (left->second.end > start) {
                int n_start = min(left->second.end, end), n_end = max(left->second.end, end);
                int nl_end = n_start, nl_start = start;
                booking[nl_start] = CalendarEntry(nl_end, left->second.times+1);
                left->second.end = nl_start;
                start = n_start;
                end = n_end;
            }
        }
        if (start < end) {
            booking[start] = CalendarEntry(end, 1);
            it = booking.find(start);
            auto lit = it;
            if (it != booking.begin()) {
                --lit;
            } else {
                ++it;
            }
            auto rit = it;
            if (it != booking.end()) {
                ++rit;
            }
            while (lit != rit && it != booking.end()) {
                // see if lit and it need to be merged
                if (lit->second.end == it->first && lit->second.times == it->second.times) {
                    lit->second.end = it->second.end;
                    booking.erase(it);
                    break;
                }
                ++it;
                ++lit;
            }
        }
        return true;
    }
};
*/
/*
 ["MyCalendarTwo","book","book","book","book","book","book","book","book","book","book"]
 [[],[24,40],[43,50],[27,43],[5,21],[30,40],[14,29],[3,19],[3,14],[25,39],[6,19]]
 */
/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo obj = new MyCalendarTwo();
 * bool param_1 = obj.book(start,end);
 */
int main() {

    vector<vector<pair<int, int>>> tests = {
        {{24,40},{43,50},{27,43},{5,21},{30,40},{14,29},{3,19},{3,14},{25,39},{6,19}}
    };
    for (auto t : tests) {
        // t is a vector of pairs
        MyCalendarTwo obj;
        printf("New calendar\n");
        for (auto p : t) {
            string res = (obj.book(p.first, p.second)?(""):("not "));
            printf("[%d, %d] is %sbookable\n", p.first, p.second, res.c_str());
        }
    }
    return 0;
}
