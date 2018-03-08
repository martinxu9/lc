#include<iostream>
#include<vector>

using namespace std;

vector<int> pourWater(vector<int>& heights, int V, int K) {
    if(heights.empty()||V==0) return heights;
    int i, j;
    while(V>0) {
        // try left first
        i = K;
        j = i;
        while(i>0&&heights[i]>=heights[i-1]){
            if(heights[i]>heights[i-1]) j=i-1;
            --i;
        }
        if(!(j<K && heights[j]<heights[K])) {
            // try go right
            i = K;
            while(i<(int)heights.size()-1&&heights[i]>=heights[i+1]){
                if(heights[i]>heights[i+1]) j=i+1;
                ++i;
            }
        }
        heights[j]++;
        --V;
    }
    return heights;
}

struct Data{
    int V;
    int K;
    vector<int> heights;
};

template<class T>
void printVector(vector<T> data) {
    for(int i=0;i<(int)data.size();++i) {
        cout<<data[i];
        if(i<(int)data.size()-1) cout<<" ";
    }
    cout<<endl;
}

int main(){
    vector<Data> tests;
    Data d;
    d.V=4;
    d.K=3;
    d.heights = {2,1,1,2,1,2,2};
    tests.emplace_back(d);
    d.V=2;
    d.K=2;
    d.heights = {1,2,3,4};
    tests.emplace_back(d);
    d.V = 5;
    d.K = 1;
    d.heights = {3,1,3};
    tests.emplace_back(d);
    d.V = 10;
    d.K = 0;
    d.heights = {2};
    tests.emplace_back(d);

    for(int i=0;i<(int)tests.size();++i) {
        cout<<"V="<<tests[i].V<<", K="<<tests[i].K<<endl;
        cout<<"heights:"<<endl;
        printVector<int>(tests[i].heights);
        cout<<"results:"<<endl;
        printVector<int>(pourWater(tests[i].heights, tests[i].V, tests[i].K));
        cout<<endl;
    }
    return 0;
}
