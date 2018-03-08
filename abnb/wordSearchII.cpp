#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct TrieNode {
    bool isWord;
    TrieNode* next[26]; // support only lower cases
    TrieNode() {
        isWord = false;
        for(int i=0;i<26;++i) next[i] = NULL;
    }
};

TrieNode* buildTrie(const vector<string>& words) {
    TrieNode* root = new TrieNode();
    int i, j;
    for(i = 0; i < words.size(); ++i) {
        TrieNode *p=root;
        for(j=0;j<words[i].size();++j) {
            int idx = words[i][j]-'a';
            if(idx<0 || idx>25) {
                // this shouldn't happen
                cout<<"skipping invalid input"<<endl;
                break;
            }
            if(!p->next[idx]) p->next[idx] = new TrieNode();
            p = p->next[idx];
        }
        if(j==words[i].size()) p->isWord = true;
    }

    return root;
}
// we use the board to indicate if letter in a certain box has been used before by marking it as '\0'
// then restore the original value when backtracking
void findHelper(const TrieNode* root, vector<string>& res, vector<vector<char>>& board, int i, int j, string& prefix) {
    if(i<0||i>=board.size()||j<0||j>=board[i].size()||board[i][j]<'a'||board[i][j]>'z'||!root||!root->next[board[i][j]-'a']) return; // out of the board or already visited
    prefix.push_back(board[i][j]);
    int idx = board[i][j]-'a';
    if(root->next[idx]->isWord){
        res.push_back(prefix);
        // mark it not a word anymore, so that no duplicates are added to res
        root->next[idx]->isWord = false;
    }
    board[i][j] = 0;
    findHelper(root->next[idx], res, board, i+1, j, prefix);
    findHelper(root->next[idx], res, board, i-1, j, prefix);
    findHelper(root->next[idx], res, board, i, j-1, prefix);
    findHelper(root->next[idx], res, board, i, j+1, prefix);
    board[i][j]=prefix.back();
    prefix.pop_back();
}

// assume all input are lower cases
vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    vector<string> res;
    if(board.empty() || board[0].empty() || words.empty()) return res;
    TrieNode* root = buildTrie(words);
    string buf = "";
    int i, j;
    for(i=0;i<board.size();++i) {
        for(j=0;j<board[i].size();++j) {
            int idx = board[i][j]-'a';
            if(idx<26&&idx>=0&&root->next[idx]) {
                findHelper(root, res, board, i, j, buf);
            }
        }
    }
    return res;
}

template<class T>
void print1D(const vector<T>& data) {
    for(auto it=data.begin();it!=data.end();++it) {
        cout<<*it;
        if(data.end()-it>1) cout<<" ";
    }
    cout<<endl;
}
template<class T>
void print2D(const vector<vector<T>>& data) {
    for(auto it=data.begin();it!=data.end();++it) {
        print1D(*it);
    }
}

int main() {
    vector<string> words = {};
    vector<vector<char>> board = {{'a', 'e', 'o'}, {'b', 'c', 't'}};
    vector<pair<vector<vector<char>>, vector<string>>> tests;
    tests.emplace_back(make_pair(board, words));
    words = {"oath","pea","eat","rain"};
    board = {{'o', 'a', 'a', 'n'}, {'e', 't', 'a', 'e'}, {'i', 'h', 'k', 'r'}, {'i', 'f', 'l', 'v'}};
    tests.emplace_back(make_pair(board, words));
    words = {"a"};
    board = {{'a', 'a'}};
    tests.emplace_back(make_pair(board, words));

    for(int i=0;i<tests.size();++i) {
        cout<<"words are:"<<endl;
        print1D<string>(tests[i].second);
        cout<<"The board:"<<endl;
        print2D<char>(tests[i].first);
        cout<<"found words:"<<endl;
        print1D<string>(findWords(tests[i].first, tests[i].second));
    }
    return 0;
}
