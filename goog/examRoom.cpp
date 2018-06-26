/*
 855. Exam Room

 In an exam room, there are N seats in a single row, numbered 0, 1, 2, ..., N-1.

 When a student enters the room, they must sit in the seat that maximizes the distance to the closest person.  If there are multiple such seats, they sit in the seat with the lowest number.  (Also, if no one is in the room, then the student sits at seat number 0.)

 Return a class ExamRoom(int N) that exposes two functions: ExamRoom.seat() returning an int representing what seat the student sat in, and ExamRoom.leave(int p) representing that the student in seat number p now leaves the room.  It is guaranteed that any calls to ExamRoom.leave(p) have a student sitting in seat p.



 Example 1:

 Input: ["ExamRoom","seat","seat","seat","seat","leave","seat"], [[10],[],[],[],[],[4],[]]
 Output: [null,0,9,4,2,null,5]
 Explanation:
 ExamRoom(10) -> null
 seat() -> 0, no one is in the room, then the student sits at seat number 0.
 seat() -> 9, the student sits at the last seat number 9.
 seat() -> 4, the student sits at the last seat number 4.
 seat() -> 2, the student sits at the last seat number 2.
 leave(4) -> null
 seat() -> 5, the student​​​​​​​ sits at the last seat number 5.
 */
#include<iostream>
#include<set>

using std::set;
using std::cout;
using std::endl;

class ExamRoom {
private:
    int N;
    set<int> seated; // a sorted set to store the seat taken so far
public:
    ExamRoom(int N) {
        this->N = N;
    }

    int seat() {
        int next_seat = 0;

        // compute the distances between each pair of seated students,
        // also consider sitting at either end of the row
        if (seated.size() == 0) {
            seated.insert(next_seat);
            return next_seat;
        }

        set<int>::reverse_iterator it;
        // j: tracks previous iterated larger of the pair
        int j, dist = -1;  // i: tracks the selected smaller of the pair

        for (it = seated.rbegin(); it != seated.rend(); ++it) {
            if (it == seated.rbegin()) {
                j = *it;
                continue;
            }
            int tmp = (j - (*it) - 1);
            if (tmp > 0 && (tmp - 1 )/2 >= dist) {
                dist = ((tmp - 1)/2);
                next_seat = (*it) + dist + 1;
            }
            j = *it;
        }
        // checks the right end of the row if it's not already taken
        it = seated.rbegin();
        j = N - 1;
        if (j - *it - 1 > dist) { // note > not >= because we want the smaller seat number
            next_seat = j;
            dist = (j - (*it) -1);
        }
        // checks the left end of the row if it's not already taken
        j = (*seated.begin());
        if (j > 0 && (j - 1) >= dist) {
            next_seat = 0;
        }

        seated.insert(next_seat);
        return next_seat;;
    }

    void leave(int p) {
        // assumes p is valid, i.e., has been seated previously
        seated.erase(p);
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom obj = new ExamRoom(N);
 * int param_1 = obj.seat();
 * obj.leave(p);
 */
int main() {
    const int N = 10;
    cout << "Exam room size : " << N << endl;
    ExamRoom obj(N);
    int p = 0;
    cout << "Seat: " << obj.seat() << endl;
    cout << "Seat: " << obj.seat() << endl;
    p = 0;
    obj.leave(p);
    cout << "Leave: " << p << endl;

    p = 9;
    obj.leave(p);
    cout << "Leave: " << p << endl;

    cout << "Seat: " << obj.seat() << endl;
    cout << "Seat: " << obj.seat() << endl;
    cout << "Seat: " << obj.seat() << endl;
    cout << "Seat: " << obj.seat() << endl;
    cout << "Seat: " << obj.seat() << endl;
    cout << "Seat: " << obj.seat() << endl;
    cout << "Seat: " << obj.seat() << endl;
    cout << "Seat: " << obj.seat() << endl;
    cout << "Seat: " << obj.seat() << endl;
    return 0;
}
