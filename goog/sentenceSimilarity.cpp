/* 
 * Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.
 * 
 * For example, "great acting skills" and "fine drama talent" are similar, if the similar word pairs are pairs = [["great", "fine"], ["acting","drama"], ["skills","talent"]].
 * 
 * Note that the similarity relation is not transitive. For example, if "great" and "fine" are similar, and "fine" and "good" are similar, "great" and "good" are not necessarily similar.
 * 
 * However, similarity is symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.
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
#include<unordered_set>

using namespace std;

bool areSentencesSimilar(vector<string>& words1, vector<string>& words2,
        vector<pair<string, string>> pairs) {
    if (words1.size() != words2.size()) return false;
    // put the pairs into a dictionary of sets for fast retrieval
    // do we assume no conflicts?
    unordered_set<string> similars;
    for (auto p : pairs) {
        similars.insert(p.first+"#"+p.second);
    }
    int i;
    for (i = 0; i < words1.size(); ++i) {
        if ((words1[i] == words2[i]) ||
                similars.count(words1[i] + "#" + words2[i]) ||
                similars.count(words2[i] + "#" + words1[i])) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    vector<string> words1 = {"this","summer","thomas","get","actually","actually","rich","and","possess","the","actually","great","and","fine","vehicle","every","morning","he","drives","one","nice","car","around","one","great","city","to","have","single","super","excellent","super","as","his","brunch","but","he","only","eat","single","few","fine","food","as","some","fruits","he","wants","to","eat","an","unique","and","actually","healthy","life"};
    vector<string> words2 = {"this","summer","thomas","get","very","very","rich","and","possess","the","very","fine","and","well","car","every","morning","he","drives","a","fine","car","around","unique","great","city","to","take","any","really","wonderful","fruits","as","his","breakfast","but","he","only","drink","an","few","excellent","breakfast","as","a","super","he","wants","to","drink","the","some","and","extremely","healthy","life"};
    vector<pair<string, string>> pairs = {{"good","nice"},{"good","excellent"},{"good","well"},{"good","great"},{"fine","nice"},{"fine","excellent"},{"fine","well"},{"fine","great"},{"wonderful","nice"},{"wonderful","excellent"},{"wonderful","well"},{"wonderful","great"},{"extraordinary","nice"},{"extraordinary","excellent"},{"extraordinary","well"},{"extraordinary","great"},{"one","a"},{"one","an"},{"one","unique"},{"one","any"},{"single","a"},{"single","an"},{"single","unique"},{"single","any"},{"the","a"},{"the","an"},{"the","unique"},{"the","any"},{"some","a"},{"some","an"},{"some","unique"},{"some","any"},{"car","vehicle"},{"car","automobile"},{"car","truck"},{"auto","vehicle"},{"auto","automobile"},{"auto","truck"},{"wagon","vehicle"},{"wagon","automobile"},{"wagon","truck"},{"have","take"},{"have","drink"},{"eat","take"},{"eat","drink"},{"entertain","take"},{"entertain","drink"},{"meal","lunch"},{"meal","dinner"},{"meal","breakfast"},{"meal","fruits"},{"super","lunch"},{"super","dinner"},{"super","breakfast"},{"super","fruits"},{"food","lunch"},{"food","dinner"},{"food","breakfast"},{"food","fruits"},{"brunch","lunch"},{"brunch","dinner"},{"brunch","breakfast"},{"brunch","fruits"},{"own","have"},{"own","possess"},{"keep","have"},{"keep","possess"},{"very","super"},{"very","actually"},{"really","super"},{"really","actually"},{"extremely","super"},{"extremely","actually"}};
    bool isSimilar = areSentencesSimilar(words1, words2, pairs);
    cout << "the sentences are " << (isSimilar?"similar":"different") << endl;
}
