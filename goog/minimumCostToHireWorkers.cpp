/*
857. Minimum Cost to Hire K Workers
There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].

Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers, we must pay them according to the following rules:

Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
Every worker in the paid group must be paid at least their minimum wage expectation.
Return the least amount of money needed to form a paid group satisfying the above conditions.



Example 1:

Input: quality = [10,20,5], wage = [70,50,30], K = 2
Output: 105.00000
Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
Example 2:

Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
Output: 30.66667
Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately.


Note:

1 <= K <= N <= 10000, where N = quality.length = wage.length
1 <= quality[i] <= 10000
1 <= wage[i] <= 10000
Answers within 10^-5 of the correct answer will be considered correct.
*/
#include<vector>
#include<queue>

using namespace std;
/* wrong solution, not sure why, but this is not efficient either */
/*
struct DPNode {
    double total;
    double pay_unit; // wage / quality
    DPNode(): total(0), pay_unit(0) {}
    DPNode(double t, double p): total(t), pay_unit(p) {}
};

// assume the input are valid, no ZERO quality in the vector
double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
    int N = quality.size();
    if (!N || wage.size() !=N || K <= 0 || K > N) return 0.0;
    double res = -1.0;
    vector<vector<DPNode>> dp(K, vector<DPNode>(N, DPNode())); // dp[i, j]: choose i out of N, the last chosen is j
    int i, j, m;
    // sort the input based on quality, ascending order
    vector<pair<int, int>> pairs(N);
    for (j = 0; j < N; ++j) {
        pairs[j] = {quality[j], wage[j]};
    }
    sort(pairs.begin(), pairs.end());
    for (j = 0; j < N; ++j) {
        quality[j] = pairs[j].first;
        wage[j] = pairs[j].second;
    }
    // initialize to choose one
    for (j = 0; j < N; ++j) {
        dp[0][j] = DPNode(wage[j], ((double)wage[j])/((double)quality[j]));
        if (res < 0 || dp[0][j].total < res) res = dp[0][j].total;
        //printf("Choosing 1, last work is %d, min wage: %f, pay/quality: %f\n", j, dp[0][j].total, dp[0][j].pay_unit);
    }
    // from choosing 2 to choosing K
    // choose i ==> dp[i-1]
    for (i = 2; i <= K; ++i) {
        res = -1.0;
        // when choose i out of N, the last chosen cannot be smaller than i-1
        for (j = i-1; j < N; ++j) {
            dp[i-1][j] = DPNode(-1.0, -1.0);
            // look at any of the previous min of choosing i-1 and ends before j
            for (m = j-1; m >=i-2; --m) {
                // two scenarios:
                // (1) if applying previous pay/quality to this wormer
                // and it meets minimum expectation, then meep it
                // (2) if not, raise the wages by the new ratio for all previous
                // wormers
                double tmp_total, tmp_unit;
                if (dp[i-2][m].pay_unit * (double)quality[j] >= (double)wage[j]) {
                    tmp_total = dp[i-2][m].total + dp[i-2][m].pay_unit * quality[j];
                    tmp_unit = dp[i-2][m].pay_unit;
                } else {
                    tmp_unit = ((double)wage[j])/((double)quality[j]);
                    // printf("dp[%d][%d] total = %f, pay/quality = %f\n", i-2, m, dp[i-2][m].total, dp[i-2][m].pay_unit);
                    tmp_total = dp[i-2][m].total/dp[i-2][m].pay_unit * tmp_unit + (double)wage[j];
                }
                if (dp[i-1][j].total < 0 || tmp_total < dp[i-1][j].total) {
                    if (res < 0 || tmp_total < res)
                        res = tmp_total;
                    dp[i-1][j] = DPNode(tmp_total, tmp_unit);
                }
            }
            //printf("Choosing %d, last work is %d, dp[%d][%d] total = %f, pay/quality = %f\n", i, j, i-1, j, dp[i-1][j].total, dp[i-1][j].pay_unit);
        }
    }
    return res;
}
*/

/* solution #2
 * basically, for any selection of workers, the max ratio of wage/quality decides
 * the final total pay, because rule #2, pay workers per ratio of their quality
 * total pay = sum(k qualities) * max(wage[i]/quality[i])
 */
struct Worker {
    double quality;
    double wage;
    Worker(): quality(0.0), wage(0.0) {}
    Worker(double q, double w): quality(q), wage(w) {}
};

struct WorkerCompare {
    bool operator()(const Worker& a, const Worker& b) {
        return (a.wage/a.quality) < (b.wage/b.quality);
    }
};

double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
    int N = quality.size();
    if (N <= 0 || wage.size() != N || K <= 0) return 0.0;
    vector<Worker> workers(N);
    int i;
    for (i = 0; i < N; ++i) {
        workers[i] = Worker((double)quality[i], (double)wage[i]);
    }
    // sort the workers so the ratio of wage/quality in ascending order
    sort(workers.begin(), workers.end(), WorkerCompare());

    // maintain a max heap of the qualities of current worker
    priority_queue<double, vector<double>, less<double>> maxheap;
    double qsum = 0.0; // sum of quality
    double res = -1.0;
    for (auto w : workers) {
        qsum += w.quality;
        // we want to eliminte the worker with highest quality already in the heap
        if (maxheap.size() > K-1) {
            qsum -= maxheap.top();
            maxheap.pop();
        }
        maxheap.push(w.quality);
        // after poping, if there's exactly K workers, calculate the total wages
        // because the workers are sorted in wage/quality ratio
        // the current worker w has the max ratio
        // remove any previously selected worker does not lower the max ratio
        if (maxheap.size() == K && (res < 0 || qsum * (w.wage/w.quality) < res)) {
            res = qsum * (w.wage/w.quality);
        }
    }
    return res;
}

int main() {
    vector<vector<int>> wages = {{70, 50, 30}, {4,8,2,2,7},};
    vector<vector<int>> qualities = {{10, 20, 5}, {3,1,10,10,1},};
    vector<int> Ks = {2, 3,};
    assert(wages.size() == qualities.size());
    assert(wages.size() == Ks.size());

    int i;
    for (i = 0; i < wages.size(); ++i) {
        printf("Work quality:\n");
        printf("{ ");
        for (auto q : qualities[i]) {
            printf("%d, ", q);
        }
        printf("}\n");

        printf("Expected wage:\n");
        printf("{ ");
        for (auto w : wages[i]) {
            printf("%d, ", w);
        }
        printf("}\n");

        printf("Minimum wages of choosing %d is %f\n\n", Ks[i],
                mincostToHireWorkers(qualities[i], wages[i], Ks[i]));
    }
    return 0;
}
