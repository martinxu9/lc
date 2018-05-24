#include<iostream>
#include<vector>
#include<string>
#include<cctype>
#include<unordered_set>
#include<unordered_map>

using namespace std;


template<typename T>
void printVector(const vector<T>& data, const string& delim) {
  for(int i=0;i<data.size();++i) {
    cout<<data[i];
    if(i<data.size()-1) cout<<delim.c_str();
  }
  cout<<endl;
}

vector<string> splitData(const string& data) {
  vector<string> res;
  if(data.empty()) return res;
  int i=0, j=0;
  while(j<data.size()) {
    while(i<data.size()&&(!isalpha(data[i]))) {
      ++i;
    }
    j=i;
    while(j<data.size()&&isalpha(data[j])) {
      ++j;
    }
    if(j>=i&&i<data.size()) res.emplace_back(data.substr(i, j-i));
    i=j;
  }
  return res;
}

vector<string> mostFreq(const string& data, const vector<string>& excl) {
  vector<string> words=splitData(data);
  //cout<<"words found in this sentence:"<<endl;
  //printVector<string>(words, "\n");
  unordered_set<string> excludes(excl.begin(), excl.end());

  int most = -1, i;
  unordered_map<string, int> count;
  unordered_set<string> res;

  for(i=0;i<words.size();++i) {
    if(excludes.count(words[i])) continue;
    if(count.find(words[i])==count.end()) {
      count[words[i]]=1;
    } else {
      count[words[i]]++;
    }
    if(count[words[i]]>most) {
      most = count[words[i]];
    }
  }
  for(i=0;i<words.size();++i) {
    if(res.count(words[i])==0 && count[words[i]]==most) res.insert(words[i]);
  }
  return vector<string>(res.begin(), res.end());
}

int main() {
  vector<pair<string, vector<string>>> tests = {{"Jimmy has an apple, it is on the table", {"an", "a", "is", "the"}}};
  for(int i=0;i<tests.size();++i) {
    cout<<"The sentence is :"<<endl;
    cout<<tests[i].first.c_str()<<endl;
    cout<<"not including the following:"<<endl;
    printVector<string>(tests[i].second, " ");
    cout<<"most frequest words in sentence:"<<endl;
    printVector<string>(mostFreq(tests[i].first, tests[i].second), " ");
  }
  return 0;
}
