#include<iostream>
#include<list>
#include<string>
#include<vector>
using namespace std;

string licenseKeyFormatting(string S, int K) {
    string buf="";
    int i;
    for(i=(int)S.size()-1;i>=0;--i) {
        if(S[i]=='-') continue;
        buf.push_back(toupper(S[i]));
        if(buf.size()%(K+1)==K)
            buf.push_back('-');
    }
    while(buf.back()=='-') buf.pop_back();
    string res(buf.rbegin(), buf.rend());
    return res;
}

int main() {
    vector<pair<string, int>> tests = {{"5F3Z-2e-9-w", 4}, {"2-5g-3-J", 2}};
    for(int i=0;i<tests.size();++i) {
        cout<<"original key: " << tests[i].first.c_str() << endl;
        cout<<"reformatted: " << licenseKeyFormatting(tests[i].first, tests[i].second) << endl;
    }
    return 0;
}
