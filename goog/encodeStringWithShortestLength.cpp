/* 471. Encode String with Shortest Length
Given a non-empty string, encode the string such that its encoded length is the shortest.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

Note:
k will be a positive integer and encoded string will not be empty or have extra space.
You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.
Example 1:

Input: "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.
Example 2:

Input: "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
Example 3:

Input: "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".
Example 4:

Input: "aabcaabcd"
Output: "2[aabc]d"
Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
Example 5:

Input: "abbbabbbcabbbabbbc"
Output: "2[2[abbb]c]"
Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
*/
#include<string>
#include<vector>

using namespace std;

class Solution {
private:
    // @return: if not a repeated pattern by itself, return 0; otherwise
    //          return the length of the pattern length
    // @argument: range from i to j, both ends inclusive
    int repeatedPattern(const string& s, int i, int j) {
        int N = j-i+1;
        vector<int> pi(N+1, 0);
        pi[0] = -1;
        int k = -1;
        for (int l = 1; l <= N; ++l) {
            while (k >= 0 && s[i+l-1] != s[i+k]) k = pi[k];
            pi[l] = (++k);
        }
        if (pi.back() > 0 && (N % (N-pi.back())) == 0) return (N-pi.back());
        else return 0;
    }
public:
    string encode(string s) {
        if (s.size() < 5) return s; // cannot be shortened by encoding

        // how to detect repetition?
        // solution #1
        // len=1, trivial
        // len=2, .., n, also 4[a]==2[aa], but of course 4[a] is shorter, so we want to get the repeated pattern
        // to maximum length? also the pattern length is the smaller the better
        // for a string ending a index i
        // we go back check one by one for len == 1,
        // check every couple of them for
        // we can use the previous results
        // e.g., for a certain len, rep[i][len] = rep[i-len][len] if s[i-j]==s[i-len-j] for 0<=j<len
        // for any string, we can check len==1 up to len(s)/2
        // solution #2
        // a bottom-up approach means, we only need to detect current [i,j] substring is a repeated pattern
        // kmp based, LC
        int N = s.size();
        vector<vector<string>> dp(N, vector<string>(N)); // dp[i][j] is encoded form or not dp[i][j] <= j-i+1

        int i, j, k;
        for (k = 1; k <= N; ++k) { // k: len of the substring being considered
            for (i = 0; i <= N-k; ++i) { // i: start of the substring
                dp[i][i+k-1] = s.substr(i, k);
                if (k < 5) { // we know that if length is smaller than 5, encoding can never shorten the length
                    continue;
                }
                for (j = i; j < i+k-1; ++j) { // j: where to split to dp[i][j] dp[j+1][i+k-1];
                    if (dp[i][j].size() + dp[j+1][i+k-1].size() < dp[i][i+k-1].size()) {
                        dp[i][i+k-1] = dp[i][j] + dp[j+1][i+k-1];
                    }
                }
                // note nested encoded forms

                // also could be the original string itself is repeated pattern
                int repeat = repeatedPattern(s, i, i+k-1), encoded_len;
                if (repeat > 0 && (encoded_len = (to_string(k/repeat).size() + 2 + repeat)) < dp[i][i+k-1].size()) {
                    dp[i][i+k-1] = (to_string(k/repeat) + "[" + dp[i][i+repeat-1] + "]");
                }
                /* anther way to see if it's repeated pattern
                string t = s.substr(i, k);
                int repeat = (t + t).find(1, t);
                if (repeat < t.size()) ...
                */
            }
        }
        // printf("dp[0][N-1] %d", dp[0][N-1]);
        // len: dp[0][N-1], string encoded 0*N+(N-1)
        return dp[0].back();
    }
};

int main() {
    Solution s1;
    vector<string> tests = {"abababaabababa", "abababaabababab"
, "abababaabababababcdefgabcdefgabcdefgabcdefgabcdefgabcdefgabcdefgabcdefgabcdefgabcdefgabcdefgabcdefgabcdefgabcdefgabcdefg", "aaaaaaaaaa", "aabcaabcd", "abbbabbbcabbbabbbc", "aaa"};
    for (auto &t : tests) {
        printf("original \"%s\" => encoded \"%s\"\n", t.c_str(), s1.encode(t).c_str());
    }
    return 0;
}
