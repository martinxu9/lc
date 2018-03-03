#include<iostream>
#include<vector>
#include<string>
#include<cstdint>
using namespace std;

uint32_t ipToUint(const string& ip) {
    istringstream istring(ip);
    uint32_t num = 0;
    string tmp;
    while(istring.getline(tmp, '.')) {
        num = ((num << 4) & (stoi(tmp)));
    }
    cout<<"IP " << ip.c_str() << " -> " << num << endl;
    return num;
}

// range is [1,1000]
// ip + range is still a valid IP address
vector<string> ipToCIDR(string ip, int range) {
    vector<string> res;
    if(range==0) return res;
    // see if this case below can be covered
    if(range==1) {
        res.push_back(ip+"/32");
        return res;
    }
    // basically, see the least significant 1 in the binary representation
    // how many in the range
    // e.g. x x x x x 1 0 0 0 should accommodate 8, ending 1000 to 1111
    // then we find the next set 10000 if we need this many
    uint32_t i = 1;
    int cnt = 0;

    return res;
}

template<class T>
void printVector(vector<T> data) {
    for(auto it=data.begin();it!=data.end();++it) {
        cout<<*it<<" ";
    }
    cout<<endl;
}

int main() {
    vector<pair<string, int> > tests;
    tests.push_back(make_pair("255.0.0.7", 10));
    for(auto it=tests.begin();it!=tests.end();++it) {
        cout<<"Next " << it->second << " IP addresses from " << it->first << " : "<<endl;
        printVector<string>(ipToCIDR(it->first, it->second));
    }
    return 0;
}
