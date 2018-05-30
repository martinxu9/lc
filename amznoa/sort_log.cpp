#include<iostream>
#include<string>
#include<vector>
#include<cctype>


using namespace std;

// solution #1, parsing at runtime, lots of dup processsing
// shortest code
// solution #2, save the "metadata" somewhere, then it's difficult to use std::sort, may have to write own quick sort
// longest code
// solution #3, convert the string vector to a metadata vector containing the original string as well, then use std::sort and copy the end result
// middle of the road

// this is a case insensitive version of the string::compare
// which 0==equal, -1 ==> a in front of b, 1 ==> b in front of a
int compareCaseInsensitive(const string& a, const string& b) {
    // assuming all of them are english letters
    int i=0, j=0;
    while(i<a.size()&&j<b.size()) {
        if(tolower(a[i])!=tolower(b[j])) {
            return (tolower(a[i]) > tolower(b[j]))*2-1;
        }
        ++i;
        ++j;
    }
    if(i==a.size()&&j==b.size()) return 0; // equal
    else
        return (i<a.size())*2-1; // 1 -> a is in front of b
}

struct LineMetadata {
    bool isNumeric;
    string log;
    string id;
    int idx;
    LineMetadata(): isNumeric(false), log(""), id(""), idx(-1) {}
    // return true for ascending order, if a in front of b
    bool operator()(const LineMetadata& a, const LineMetadata& b) {
        if((!a.isNumeric) && (!b.isNumeric)) {
            int cmp = 0;
            if((cmp=compareCaseInsensitive(a.log, b.log))==0) {
                return (a.id.compare(b.id)<0);
            } else {
                return (cmp<0);
            }
        } else return false;
    }
} MyObject;


void parseLine(LineMetadata& res, const string& line, const int& idx){
    res.idx = idx;
    // skip exception handling for illegal strings
    int i=0;
    while(i<line.size()&&isalnum(line[i])) ++i;
    res.id = line.substr(0, i);
    while(i<line.size()&&isspace(line[i])) ++i;
    res.log = line.substr(i, line.size()-i+1);
    res.isNumeric = isdigit(res.log[0]);
}

vector<string> sortLog(vector<string>& logLines, int logFileSize) {
    // no need to sort, early return
    if(logFileSize<=1) return logLines;

    // first pass
    // to get the identifier and if it is numeric into the class
    vector<LineMetadata> metas(logLines.size());
    int i, j;
    for(i=0;i<logLines.size();++i) {
        parseLine(metas[i], logLines[i], i);
    }

    // second pass
    // move all the numeric logs to the end
    // note that we need to maintain the original order of these, so reverse traversal
    i=metas.size()-1;
    j=i;
    while(i>=0) {
        if(metas[i].isNumeric){
            if(i<j)
                swap(metas[i], metas[j]);
            --j;
        }
        --i;
    }

    // third pass
    // now j marks the end of the segment needs to be sorted
    // 0 through j inclusive
    sort(metas.begin(), metas.begin()+j+1, MyObject);

    // copy the result back into logLines
    for(i=0;i<logLines.size();++i) {
        logLines[i] = metas[i].id + " " + metas[i].log;
    }
    return logLines;
}

int main() {
    vector<pair<vector<string>, int>> tests = {{{"a1 9 2 3 1", "g1 Act car", "zo4 4 7", "b9 act zoo", "ab1 off KEY dog", "a8 act zoo"}, 6},
    {{"min jog mid pet", "wz3 34 54 398", "a1 alps cow bar", "x4 45 21 7"}, 4},
    {{"t2 13 121 98", "r1 box ape bit", "b4 xi me nu", "br8 eat nim did", "w1 has uni gry", "f3 52 54 31"}, 6},
    {{"a1 9 2 3 1", "g1 Act car","g0 Act car", "g1 Act car more", "1g Act car more", "zo4 4 7", "ab1 off KEY dog",
        "a8 act zoo"}, 8},
    {{"fhie bdf8 sfds", "fdsf adef sees", "fdse adef sees", "efe2 12345 5555", "asd1 12355 5555", "123 act car", "124 a c t c a r"}, 7}};
    for(int i=0;i<tests.size();++i) {
        cout<<"## the log has "<<tests[i].second<< " lines:"<<endl;
        for(int j=0;j<tests[i].second;++j) {
            cout<<tests[i].first[j].c_str()<<endl;
        }
        cout<<endl;
        cout<<"## the sorted log is :"<<endl;
        vector<string> res = sortLog(tests[i].first, tests[i].second);
        for(int j=0;j<res.size();++j) {
            cout<<res[j].c_str()<<endl;
        }
        cout<<endl;
        cout<<endl;
    }
    return 0;
}
