#include<iostream>
#include<string>
#include<vector>

using namespace std;

vector<string> fullJustify(vector<string>& words, int maxWidth) {
    // maxWidth is guaranteed to be no smaller than the longest word in words
    vector<string> res;
    int i=0, j=0;
    while(i<words.size()) {
        int wordWidth=0;
        j = i;
        while(j<words.size() && wordWidth+words[j].size()<=maxWidth-(j-i)) {
            wordWidth+=words[j++].size();
        }
        // now this is how many words the row can accommodate
        // corner case: last line, left justified
        // corner case: only one word, left justified
        string tmp="";
        int numSpaces = 1, left = 0;
        if(j-i>1 && j<words.size()) {
            numSpaces = (maxWidth-wordWidth)/(j-i-1);
            left = (maxWidth-wordWidth)%(j-i-1); // this many extra spaces, evenly distributed
        }
        for(int k=i;k<j;++k) {
            tmp.append(words[k]);
            tmp.append(string(((k<j-1)?numSpaces:0)+((left-->0)?1:0), ' '));
        }
        if(tmp.size()<maxWidth) tmp.append(string(maxWidth-tmp.size(), ' '));
        res.emplace_back(tmp);
        i=j;
    }
    return res;
}

void printVector(const vector<string>& data, bool newline){
    if(!newline) cout<<"\"";
    for(auto it=data.begin(); it!=data.end(); ++it) {
        if(newline) cout<<"\"";
        cout<<it->c_str();
        if(newline) cout<<"\""<<endl;
        else if(data.end()-it>1) cout<<" ";
    }
    if(!newline) cout<<"\""<<endl;
}

bool validateTest(const vector<pair<vector<string>, int> >& tests) {
    for(auto it=tests.begin();it!=tests.end();++it) {
        if(it->second<0) return false;
        for(auto it2=it->first.begin();it2!=it->first.end();++it2) {
            if(it2->size()>it->second) return false;
        }
    }
    return true;
}

int main() {
    vector<pair<vector<string>,int> > tests;
    vector<string> words;
    int len = 0;
    words = {"hello", "world"};
    len = 11;
    tests.emplace_back(make_pair(words, len));
    words = {"hello", "world"};
    len = 9;
    tests.emplace_back(make_pair(words, len));
    words = {"This", "is", "an", "example", "of", "text", "justification."};
    len = 16;
    tests.emplace_back(make_pair(words, len));
    words = {""};
    len = 0;
    tests.emplace_back(make_pair(words, len));
    words = {"What","must","be","shall","be."};
    len = 12;
    tests.emplace_back(make_pair(words, len));
    words = {"Listen","to","many,","speak","to","a","few."};
    len = 6;
    tests.emplace_back(make_pair(words, len));

    if(!validateTest(tests)) return 1;

    for(auto it=tests.begin();it!=tests.end();++it) {
        printVector(it->first, false);
        cout<<">>>>>>>>>>"<<endl;
        printVector(fullJustify(it->first, it->second), true);
        cout<<endl;
    }
    return 0;
}
