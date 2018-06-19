/*
 * Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.
 * 
 * For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].
 * 
 * Note that the similarity relation is transitive. For example, if "great" and "good" are similar, and "fine" and "good" are similar, then "great" and "fine" are similar.
 * 
 * Similarity is also symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.
 * 
 * Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.
 * 
 * Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].
 * 
 * Note:
 * 
 * The length of words1 and words2 will not exceed 1000.
 * The length of pairs will not exceed 2000.
 * The length of each pairs[i] will be 2.
 * The length of each words[i] and pairs[i][j] will be in the range [1, 20].
 */


#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
    // union find: in any pair, the smaller in lexigraphical order is the root
    if ( words1.size() != words2.size() ) {
        return false;
    }

    // use directionary for keeping "roots"
    unordered_map<string, string> roots; // word -> root of the similar word chain
    for (auto p : pairs) {
        string x = p.first, y = p.second;
        unordered_map<string, string>::iterator it;
        while ((it=roots.find(x)) != roots.end()) {
            x = it->second;
            // TODO: shorten the chain while traversing
        }
        while ((it=roots.find(y)) != roots.end()) {
            y = it->second;
            // TODO: shorten the chain while traversing
        }
        string newRoot = x;
        if (x.compare(y) < 0) {
            roots[y] = x;
        } else if (x.compare(y) > 0) {
            roots[x] = y;
            newRoot = y;
        }
        if (p.first != newRoot) {
            roots[p.first] = newRoot;
        }
        if (p.second != newRoot) {
            roots[p.second] = newRoot;
        }
    }
    
    for (int i = 0; i < words1.size(); ++i) {
        if (words1[i] == words2[i]) {
            continue;
        }
        string x = words1[i], y = words2[i];
        unordered_map<string, string>::iterator it;
        while ((it = roots.find(x)) != roots.end()) {
            x = roots[x];
        }
        while ((it = roots.find(y)) != roots.end()) {
            y = roots[y];
        }
        if (x != y) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<string> words1 = {"this","summer","thomas","get","actually","actually","rich","and","possess","the","actually","great","and","fine","vehicle","every","morning","he","drives","one","nice","car","around","one","great","city","to","have","single","super","excellent","super","as","his","brunch","but","he","only","eat","single","few","fine","food","as","some","fruits","he","wants","to","eat","an","unique","and","actually","healthy","life"};
    vector<string> words2 = {"this","summer","thomas","get","very","very","rich","and","possess","the","very","fine","and","well","car","every","morning","he","drives","a","fine","car","around","unique","great","city","to","take","any","really","wonderful","fruits","as","his","breakfast","but","he","only","drink","an","few","excellent","breakfast","as","a","super","he","wants","to","drink","the","some","and","extremely","healthy","life"};
    vector<pair<string, string>> pairs = {{"good","nice"},{"good","excellent"},{"good","well"},{"good","great"},{"fine","nice"},{"fine","excellent"},{"fine","well"},{"fine","great"},{"wonderful","nice"},{"wonderful","excellent"},{"wonderful","well"},{"wonderful","great"},{"extraordinary","nice"},{"extraordinary","excellent"},{"extraordinary","well"},{"extraordinary","great"},{"one","a"},{"one","an"},{"one","unique"},{"one","any"},{"single","a"},{"single","an"},{"single","unique"},{"single","any"},{"the","a"},{"the","an"},{"the","unique"},{"the","any"},{"some","a"},{"some","an"},{"some","unique"},{"some","any"},{"car","vehicle"},{"car","automobile"},{"car","truck"},{"auto","vehicle"},{"auto","automobile"},{"auto","truck"},{"wagon","vehicle"},{"wagon","automobile"},{"wagon","truck"},{"have","take"},{"have","drink"},{"eat","take"},{"eat","drink"},{"entertain","take"},{"entertain","drink"},{"meal","lunch"},{"meal","dinner"},{"meal","breakfast"},{"meal","fruits"},{"super","lunch"},{"super","dinner"},{"super","breakfast"},{"super","fruits"},{"food","lunch"},{"food","dinner"},{"food","breakfast"},{"food","fruits"},{"brunch","lunch"},{"brunch","dinner"},{"brunch","breakfast"},{"brunch","fruits"},{"own","have"},{"own","possess"},{"keep","have"},{"keep","possess"},{"very","super"},{"very","actually"},{"really","super"},{"really","actually"},{"extremely","super"},{"extremely","actually"}};
    bool isSimilar = areSentencesSimilarTwo(words1, words2, pairs);
    cout << "the sentences are " << (isSimilar?"similar":"different") << endl;
}
