#include<iostream>
#include<vector>

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

vector<Interval> employeeFreeTime(vector<vector<Interval>>& avails){
    vector<Interval> res;
    // this is similar to merge intervals?
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
