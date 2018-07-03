/*
 * 418. Sentence Screen Fitting
 * Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.

Note:

A word cannot be split into two lines.
The order of words in the sentence must remain unchanged.
Two consecutive words in a line must be separated by a single space.
Total words in the sentence won't exceed 100.
Length of each word is greater than 0 and won't exceed 10.
1 ≤ rows, cols ≤ 20,000.
Example 1:

Input:
rows = 2, cols = 8, sentence = ["hello", "world"]

Output:
1

Explanation:
hello---
world---

The character '-' signifies an empty space on the screen.
Example 2:

Input:
rows = 3, cols = 6, sentence = ["a", "bcd", "e"]

Output:
2

Explanation:
a-bcd-
e-a---
bcd-e-

The character '-' signifies an empty space on the screen.
Example 3:

Input:
rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]

Output:
1

Explanation:
I-had
apple
pie-I
had--

The character '-' signifies an empty space on the screen.

*/

#include<iostream>
#include<vector>
using namespace std;

int wordsTyping(vector<string>& sentence, int rows, int cols) {
    // sentence is not empty, with non empty words
    string all = "";
    // precalcuate the combined sentence with spaces
    for (auto s : sentence) {
        all += (s + " ");
    }
    int res = 0, N = all.size();
    int i = 0;
    // then greedily, try with cols for fitting
    // if not fit, we go backwards to give back the over counted sentence length
    for (i = 0; i < rows; ++i) {
        res += cols;
        while (res > 0 && all[(res % N)] != ' ') {
            --res;
        }
        ++res; // the while loop above gives back the trailing space, add it back
    }
    // result is the sentence length devided by the window width
    return (res / N);
}

struct data {
    vector<string> sentence;
    int rows;
    int cols;
};

int main() {
    vector<data> tests = {{{"Hello", "World"}, 2, 8}, {{"a", "bcd", "e"}, 3, 6},
                        {{"I", "had", "apple", "pie"}, 4, 5}};
    for (auto t : tests) {
        for (auto s : t.sentence) {
            cout << s << ", ";
        }
        cout << endl;
        printf("Screen size %d by %d, can fit %d times\n", t.rows, t.cols,
            wordsTyping(t.sentence, t.rows, t.cols));
    }
    return 0;
}
