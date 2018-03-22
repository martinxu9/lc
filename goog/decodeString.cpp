#include<iostream>
#include<list>
#include<vector>
#include<string>

using namespace std;

string decodeString(string s) {
    if(s.empty()) return s;
    // assume stirng s is always the right format?
    list<pair<int, string>> stk;
    string res = "";
    int i;
    int num = 0;
    string prefix = "";
    for(i=0;i<s.size();++i) {
        if(isdigit(s[i])) {
            num = num*10+(s[i]-'0');
        } else if (s[i]=='[') {
            stk.push_front({num, ""});
            num = 0;
        } else if (s[i]==']') {
            while(stk.front().first) {
                prefix += stk.front().second;
                stk.front().first--;
            }
            stk.pop_front();
            if(stk.empty()) {
                res += prefix;
            } else {
                stk.front().second.append(prefix);
            }
            prefix = "";
        } else if (isalpha(s[i])) {
            if(!stk.empty()) {
                stk.front().second.push_back(s[i]);
            } else {
                // no repeat for this character
                res.push_back(s[i]);
            }
        } else {
            return "invalid input";
        }
    }
    return res;
}

int main() {
    vector<string> tests = {"3[a]2[bc]", "3[a2[c]]", "2[abc]3[cd]ef"};
    for(int i=0;i<tests.size();++i) {
        cout<<"encoded string: " << tests[i].c_str() << endl;
        cout<<"decoded string: " << decodeString(tests[i]).c_str() << endl;
    }
    return 0;
}
