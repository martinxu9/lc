class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        string res = "";
        if(paragraph.size()==0) return res;

        unordered_set<string> banned_set;
        for(auto b: banned) banned_set.insert(b);
        int res_cnt = -1;

        unordered_map<string, int> counts;

        int i=0, j=0;
        while(j<paragraph.size()) {
            while(j<paragraph.size() && (!isalpha(paragraph[j]))){
                ++j;
            }
            i=j;
            while(j<paragraph.size() && isalpha(paragraph[j])) {
                ++j;
            }
            string tmp = "";
            for(; i<j;++i) tmp.push_back(tolower(paragraph[i]));
            if(banned_set.count(tmp)) continue;
            unordered_map<string, int>::iterator it=counts.find(tmp);
            if(it==counts.end()) counts[tmp]=1;
            else counts[tmp]++;
            if(counts[tmp]> res_cnt) {
                res_cnt = counts[tmp];
                res = tmp;
            }
        }
        return res;
    }
};
