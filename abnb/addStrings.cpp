#include<iostream>

using namespace std;

string addStrings(const string& num1, const string& num2) {
    if(num1.size()>num2.size()) return addStrings(num2, num1);

    // now num1 <= num2 in length
    
    // corner cases
    if(num2.empty()) return "";
    if(num1.empty()) return num2;

    list<char> buf;
    int i=num1.size()-1, j=num2.size()-1, carry = 0;
    while(j>=0) {
        int tmp = num2[j--]+(i>=0)?num1[i--]:0+carry;
        carry = tmp/10;
        buf.push_front((char)(tmp%10+'0'));
    }
    if(carry) buf.push_front(carry+'0');
    return string(buf.begin(), buf.end());
}

int main() {
    vector<string> n1 = {"0", "1", "11"};
    vector<string> n2 = {"1", "0", "234"};
    for(int i=0;i<n1.size();++i) {
        cout<<n1[i].c_str() << " + " << n2[i].c_str() << " == " << addStrings(n1[i], n2[i]).c_str() << " ;" <<endl;
    }
    return 0;
}
