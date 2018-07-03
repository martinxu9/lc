/* LC 399. Evaluate Division
 * Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.
 *
 * Example:
 * Given a / b = 2.0, b / c = 3.0.
 * queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
 * return [6.0, 0.5, -1.0, 1.0, -1.0 ].
 *
 * The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.
 *
 * According to the example above:
 *
 * equations = [ ["a", "b"], ["b", "c"] ],
 * values = [2.0, 3.0],
 * queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].
 * The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.
 *
 */

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::pair;
using std::unordered_map;

struct parent {
    string node; // child/parent = val
    double val;
    parent(): node(""), val(0.0) {}
    parent(string n, double v): node(n), val(v) {}
};

// path compression?
parent findParent(const string a, unordered_map<string, parent>& roots) {
    parent p;
    if (roots.find(a) != roots.end() && roots[a].node == a) {
        p = roots[a];
    } else {
        string node = roots[a].node;
        double val = roots[a].val;
        p = findParent(roots[a].node, roots);
        p.val *= val;
    }
    return p;
}

vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
    // basically construct a graph,
    // if a/b is available, then a is connected to b in the graph
    // for any equation x / y, if we find a path from x to y,
    // x -> a1 -> a2 -> y, then the result can be calculated as
    // (x/a1) * (a1/a2) * (a2/y)
    // don't need to consider this special cases below
    // if a/b == 0, b is not zero, a is zero
    vector<double> res(queries.size(), 0.0);
    if (equations.size() == 0 || queries.size() == 0) {
        return res;
    }
    // process the existing equations
    unordered_map<string, parent> roots;
    // assume the size of equations is the same as values
    int i;
    for (i = 0; i < equations.size(); ++i) {
        string a = equations[i].first, b = equations[i].second;
        if (roots.find(a) == roots.end()) {
            roots[a] = {a, 1.0};
        }
        if (roots.find(b) == roots.end()) {
            roots[b] = {b, 1.0};
        }
    }
    for (i = 0; i < equations.size(); ++i) {
        string &a = equations[i].first, &b = equations[i].second;
        parent pa = findParent(a, roots), pb = findParent(b, roots);
        roots[pa.node] = {pb.node, values[i]/pa.val*pb.val};
    }
    for (i = 0; i < queries.size(); ++i) {
        string &a = queries[i].first, &b = queries[i].second;
        parent pa = findParent(a, roots), pb = findParent(b, roots);
        if (pa.node == pb.node && pa.node.size() > 0) {
            res[i] = (pa.val / pb. val);
        } else {
                res[i] = -1;
        }
    }
    return res;
}

int main() {
    vector<pair<string, string>> equations = {{"a", "b"}, {"b", "c"}};
    vector<double> values = {2.0, 3.0};
    vector<pair<string, string>> queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x2", "x9"}, {"x9", "x9"}};
    vector<double> res = calcEquation(equations, values, queries);
    cout << "Results are : " << endl;
    for (auto r : res) {
        cout << r << ", ";
    }
    cout << endl;
    return 0;
}
