#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<cstdint>
using namespace std;

uint32_t ipToUint32(const string& ip) {
    istringstream istring(ip);
    uint32_t num = 0;
    string tmp;
    while(getline(istring, tmp, '.')) {
        num = ((num << 8) | (stoi(tmp)));
    }
    cout<<"IP " << ip.c_str() << " -> " << num << endl;
    return num;
}

string uint32ToIP(uint32_t ip_value) {
    string res = to_string((ip_value&0xFF000000)>>24) + "." + to_string((ip_value&0xFF0000)>>16) + "." + to_string((ip_value&0xFF00)>>8) + "." + to_string((ip_value&0xFF));
    cout<<"uint32_t " << ip_value << " -> " << res.c_str() << endl;
    return res;
}

// range is [1,1000]
// ip + range is still a valid IP address
vector<string> ipToCIDR(string ip, int range) {
    vector<string> res;
    if(range==0) return res;
    // basically, see the least significant 1 in the binary representation
    // how many in the range
    // e.g. x x x x x 1 0 0 0 should accommodate 8, ending 1000 to 1111
    // then we find the next set 10000 if we need this many
    uint32_t ip_value = ipToUint32(ip);

    while(range>0){
        int cnt = 0;
        uint32_t i = 1;
        // how many needed, range
        // how many a 1000000 format can accommodate
        // how many zeros after the 1 in the starting IP
        while((i&ip_value)==0 && i<=range && (i<<1)<=range){
            i=i<<1;
            cnt++;
        }
        res.push_back(uint32ToIP(ip_value)+"/"+to_string(32-cnt));
        ip_value+=i;
        range-=i;
    }
    return res;
}

template<class T>
void printVector(vector<T> data) {
    if(data.empty()) cout<<"It is empty!";
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
