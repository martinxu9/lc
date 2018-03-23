#include<iostream>
#include<vector>
using namespace std;

bool validUtf8(vector<int>& data) {
    int cnt = 0;
    for(auto d: data) {
        if(!cnt) {
            // how many bytes
            if((d>>3) == 0b11110) cnt = 3;
            else if ((d>>4) == 0b1110) cnt = 2;
            else if ((d>>5) == 0b110) cnt = 1;
            else if (d>>7) return false;
        } else {
            // decrement cnt
            if((d>>6)!=0b10) return false;
            --cnt;
        }
    }
    return cnt==0;
}

void printUTF(const vector<int>& data) {
    cout<<"\"";
    for(auto it=data.begin();it!=data.end();++it) {
        cout<<bitset<8>(*it);
        if(it+1!=data.end()) cout<<" ";
    }
    cout<<"\"";
}

int main() {
    vector<vector<int>> tests = {{250,145,145,145,145},{145},{197, 130, 1}, {235, 140, 4}, {230,136,145}};
    for(int i=0;i<tests.size();++i) {
        printUTF(tests[i]);
        cout<<" : " << (validUtf8(tests[i])?"true":"false") << endl;
    }
    return 0;
}
