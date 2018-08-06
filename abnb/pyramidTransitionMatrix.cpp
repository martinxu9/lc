/* LC 756. Pyramid Transition Matrix
We are stacking blocks to form a pyramid. Each block has a color which is a one letter string, like `'Z'`.

For every block of color `C` we place not in the bottom row, we are placing it on top of a left block of color `A` and right block of color `B`. We are allowed to place the block there only if `(A, B, C)` is an allowed triple.

We start with a bottom row of bottom, represented as a single string. We also start with a list of allowed triples allowed. Each allowed triple is represented as a string of length 3.

Return true if we can build the pyramid all the way to the top, otherwise false.

Example 1:
Input: bottom = "XYZ", allowed = ["XYD", "YZE", "DEA", "FFF"]
Output: true
Explanation:
We can stack the pyramid like this:
    A
   / \
  D   E
 / \ / \
X   Y   Z

This works because ('X', 'Y', 'D'), ('Y', 'Z', 'E'), and ('D', 'E', 'A') are allowed triples.
Example 2:
Input: bottom = "XXYX", allowed = ["XXX", "XXY", "XYX", "XYY", "YXZ"]
Output: false
Explanation:
We can't stack the pyramid to the top.
Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.
Note:
bottom will be a string with length in range [2, 8].
allowed will have length in range [0, 200].
Letters in all strings will be chosen from the set {'A', 'B', 'C', 'D', 'E', 'F', 'G'}.
*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cstdint>
#include<list>

using namespace std;

template<class T>
void printRow(const vector<T>& row) {
    for(auto it=row.begin();it!=row.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}

int encodeTwoInts(int a1, int a2) {
        //if(a1>a2) return encodeTwoInts(a2,a1);
    return ((1<<(a1+8)) | (1<<a2));
}

int encodeTwoChars(char a1, char a2) {
    return encodeTwoInts((a1-'A'), (a2-'A'));
}

int encodeInt(int a1) {
    return (1<<a1);
}

int encodeChar(char a1) {
    return encodeInt(a1-'A');
}

bool pyramidTransition(string bottom, vector<string>& allowed) {
    // need to handle the case where bottom is just one character?

    // assume no duplicates in the input data
    // no need to sort/remove duplicates
    unordered_map<int, int> allowed_map; // "XY"->"ABCDE" the two chars to their next state, all combined in the int
    int i, j;
    for(i=0;i<allowed.size();++i) {
        int mask = encodeTwoChars(allowed[i][0], allowed[i][1]);
        auto it = allowed_map.find(mask);
        if(it == allowed_map.end()) allowed_map[mask]=encodeChar(allowed[i][2]);
        else allowed_map[mask] |= encodeChar(allowed[i][2]);
    }
    vector<vector<int>> dp(bottom.size()); // represent the pyramid

    dp.back() = vector<int>(bottom.size());
    for(i=0;i<bottom.size();++i) {
        dp.back()[i] = encodeChar(bottom[i]);
    }
    for(i=dp.size()-2;i>=0;--i) {
        dp[i] = vector<int>(i+1, 0);
        for(j=0;j<dp[i].size();++j) {
            int dp1 = dp[i+1][j], dp2 = dp[i+1][j+1];
            int k1,k2;
            for(k1=0;k1<8;++k1) {
                if((dp1&(1<<k1))==0) continue;
                for(k2=0;k2<8;++k2) {
                    if((dp2&(1<<k2))==0) continue;
                    int mask = encodeTwoInts(k1,k2);
                    auto it = allowed_map.find(mask);
                    if(it==allowed_map.end()) continue;
                    dp[i][j] |= allowed_map[mask];
                }
            }
            if(dp[i][j]==0) return false;
        }
    }
    return (dp[0][0]>0);
}

int main() {
    vector<string> bottom_tests = {"ABC", "AABA", "CB"};
    vector<vector<string>> allowed_tests;
    vector<string> tmp = {"ABD","BCE","DEF","FFF"};
    allowed_tests.push_back(tmp);
    tmp = {"AAA", "AAB", "ABA", "ABB", "BAC"};
    allowed_tests.push_back(tmp);
    tmp = {"CDD","CBC","ACA","BDD","ADD","DCA","BAD","ADA"};
    allowed_tests.push_back(tmp);
    for(auto i=0;i<bottom_tests.size();++i) {
        cout<<"test case "<< i << " : " << pyramidTransition(bottom_tests[i], allowed_tests[i]) <<endl;
    }
    return 0;
}
