/* LC 751

Given a start IP address ip and a number of ips we need to cover n, return a representation of the range as a list (of smallest possible length) of CIDR blocks.

A CIDR block is a string consisting of an IP, followed by a slash, and then the prefix length. For example: "123.45.67.89/20". That prefix length "20" represents the number of common prefix bits in the specified range.

Example 1:
Input: ip = "255.0.0.7", n = 10
Output: ["255.0.0.7/32","255.0.0.8/29","255.0.0.16/32"]
Explanation:
The initial ip address, when converted to binary, looks like this (spaces added for clarity):
255.0.0.7 -> 11111111 00000000 00000000 00000111
The address "255.0.0.7/32" specifies all addresses with a common prefix of 32 bits to the given address,
ie. just this one address.

The address "255.0.0.8/29" specifies all addresses with a common prefix of 29 bits to the given address:
255.0.0.8 -> 11111111 00000000 00000000 00001000
Addresses with common prefix of 29 bits are:
11111111 00000000 00000000 00001000
11111111 00000000 00000000 00001001
11111111 00000000 00000000 00001010
11111111 00000000 00000000 00001011
11111111 00000000 00000000 00001100
11111111 00000000 00000000 00001101
11111111 00000000 00000000 00001110
11111111 00000000 00000000 00001111

The address "255.0.0.16/32" specifies all addresses with a common prefix of 32 bits to the given address,
ie. just 11111111 00000000 00000000 00010000.

In total, the answer specifies the range of 10 ips starting with the address 255.0.0.7 .

There were other representations, such as:
["255.0.0.7/32","255.0.0.8/30", "255.0.0.12/30", "255.0.0.16/32"],
but our answer was the shortest possible.

Also note that a representation beginning with say, "255.0.0.7/30" would be incorrect,
because it includes addresses like 255.0.0.4 = 11111111 00000000 00000000 00000100
that are outside the specified range.
Note:
ip will be a valid IPv4 address.
Every implied address ip + x (for x < n) will be a valid IPv4 address.
n will be an integer in the range [1, 1000].

*/

#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<cstdint>
#include<boost/algorithm/string.hpp>

using std::string, std::vector, std::istringstream, std::cout, std::endl, std::pair, std::to_string;
using boost::split;

/*
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
*/

/* boost version */
uint32_t ipToUint32(const string& ip) {
    vector<string> res;
    split(res, ip, [](char c) { return c == '.'; });
    uint32_t num = 0;
    for (auto &n : res) {
        num = ((num << 8) | (stoi(n)));
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
    vector<pair<string, int>> tests = {{"255.0.0.7", 10}, {"192.168.0.22", 29}};
    for(auto &t : tests) {
        cout<<"Next " << t.second << " IP addresses from " << t.first << " : "<<endl;
        printVector<string>(ipToCIDR(t.first, t.second));
        printf("\n");
    }
    return 0;
}
