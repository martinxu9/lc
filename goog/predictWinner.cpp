/* LC 486. Predict the Winner
Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.

Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.

Example 1:
Input: [1, 5, 2]
Output: False
Explanation: Initially, player 1 can choose between 1 and 2.
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2).
So, final score of player 1 is 1 + 2 = 3, and player 2 is 5.
Hence, player 1 will never be the winner and you need to return False.
Example 2:
Input: [1, 5, 233, 7]
Output: True
Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
Note:
1 <= length of the array <= 20.
Any scores in the given array are non-negative integers and will not exceed 10,000,000.
If the scores of both players are equal, then player 1 is still the winner.
 */

#include<iostream>
#include<vector>
using namespace std;

/* solution #1: recursion with memorization
   one optimization below, don't need the exact score, but difference
*/
/*
int score(const vector<int>& nums, int i, int j, vector<vector<int>>& visited, const vector<int>& sums) {
    if (j > i) return 0; // invalid input

    if (visited[i][j] > 0)
        return visited[i][j];

    if (i == j) {
        visited[i][j] = nums[i];
    } else {
        int chooseLeft = nums[i] + (sums[j+1] - sums[i+1] - score(nums, i+1, j, visited, sums));
        int chooseRight = nums[j] + (sums[j] - sums[i] - score(nums, i, j-1, visited, sums));
        visited[i][j] = max(chooseLeft, chooseRight);
    }
    return visited[i][j];
}

bool PredictTheWinner(vector<int>& nums) {
    if (nums.size() <= 2) return true; // player 1 goes first, when two or less numbers, always player 1
    vector<vector<int>> visited(nums.size(), vector<int>(nums.size(), 1));
    vector<int> sums(nums.size() + 1, 0);
    int i;
    for (i = 0; i < nums.size(); ++i) {
        sums[i+1] = sums[i] + nums[i];
    }

    if (score(nums, 0, nums.size()-1, visited, sums)*2 >= (sums[nums.size()] - sums[0])) return true;
    else return false;
}
*/

/*  Solution #2: 1D DP
    state trasition, d[i][j] only depends on d[i+1][j] and d[i][j-1]
    the 2D DP goes reverse traversal for rows (i), then forward for columns (j)
    once a row is traversed, it is no longer used, so we can only keep one row
*/

bool PredictTheWinner(vector<int>& nums) {
    vector<int> dp(nums.size(), 0);
    int i, j;
    for (i = nums.size()-1; i >= 0; --i) {
        for (j = i; j < nums.size(); ++j) {
            if (i == j) {
                dp[i] = nums[i];
            } else {
                int l = nums[i] - dp[j];
                int r = nums[j] - dp[j-1];
                dp[j] = max(l, r);
            }
        }
    }
    return (dp.back() >= 0);
}

int main() {
    vector<int> nums = {1,5,2};
    if (PredictTheWinner(nums)) {
        cout << "Player 1 is the winner" << endl;
    } else {
        cout << "Player 2 is the winner" << endl;
    }
    nums = {1,5,233,7};
    if (PredictTheWinner(nums)) {
        cout << "Player 1 is the winner" << endl;
    } else {
        cout << "Player 2 is the winner" << endl;
    }
    return 0;
}
