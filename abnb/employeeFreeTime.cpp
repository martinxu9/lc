#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Interval{
    int start;
    int end;
    Interval(): start(0), end(0) {}
    Interval(int s, int e): start(s), end(e) {}
    void print(){
        cout<<"["<<start<<","<<end<<"]";
    }
};

struct QueueNode {
    int i; //which employee
    int j; //which interval
    Interval slot;
    QueueNode(const int i1, const int j1, const Interval& s1): i(i1), j(j1), slot(s1) {}
};

class NodeComparison{
public:
    bool operator()(const QueueNode& a, const QueueNode& b) {
        return a.slot.start>b.slot.start;
    }
};

vector<Interval> employeeFreeTime(vector<vector<Interval>>& avails){
    vector<Interval> res;
    // this is similar to merge intervals?
    if(avails.empty()) return res;
    priority_queue<QueueNode, vector<QueueNode>, NodeComparison> queue;
    int i;
    for(i=0;i<(int)avails.size();++i) {
        if(avails[i].empty()) continue;
        queue.push(QueueNode(i, 0, avails[i][0]));
    }
    // merging all the intervals
    // when a new Interval popped from the priority queue
    // it should have an equal or later start time
    // see if can be merged with previous ones
    // if cannot be merged, we have the free time
    Interval *last = NULL;
    while(!queue.empty()) {
        QueueNode tmp = queue.top();
        queue.pop();
        if(tmp.j<(int)avails[tmp.i].size()-1) queue.push(QueueNode(tmp.i, tmp.j+1, avails[tmp.i][tmp.j+1]));

        if(!last) {
            last = new Interval(tmp.slot);
        } else {
            if(tmp.slot.start<=last->end) {
                last->end = max(last->end, tmp.slot.end);
            } else {
                res.emplace_back(Interval(last->end, tmp.slot.start));
                last->start = tmp.slot.start;
                last->end = tmp.slot.end;
            }
        }
     }
    return res;
}


typedef vector<vector<Interval>> Data;


void print1D(vector<Interval> data) {
    for(int i=0;i<data.size();++i) {
        data[i].print();
        if(i<data.size()-1) cout<<",";
    }
    cout<<endl;
}
void print2D(Data d) {
    for(int i=0;i<d.size();++i) {
        cout<<"employee " << i << ":" << endl;
        print1D(d[i]);
    }
}

int main() {
    vector<Data> tests;
    Data d = {{Interval(1,2), Interval(5,6)}, {Interval(1,3)}, {Interval(4,10)}};
    tests.emplace_back(d);
    for(int i=0;i<tests.size();++i) {
        cout<<"input:"<<endl;
        print2D(tests[i]);
        cout<<"result:"<<endl;
        print1D(employeeFreeTime(tests[i]));
    }


    return 0;
}
