#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack_with_reps(int W, vector<int>& weight, vector<int>& cell) {
    vector<int> d(W+1, 0);
    for (int w = 1; w <= W; ++w) {
        for (size_t i = 0; i < weight.size(); ++i) {
            if (weight[i] <= w) {
                d[w] = max(d[w], d[w - weight[i]] + cell[i]);
            }
        }
    }
    return d[W];
}

pair<int, vector<int>> knapsack_without_reps(int W, vector<int>& weight, vector<int>& cell) {
    vector<vector<int>> d(W+1, vector<int>(weight.size() + 1, 0));
    for (size_t i = 0; i < weight.size(); ++i) {
        for (int w = 1; w <= W; ++w) {
            d[w][i+1] = d[w][i];
            if (weight[i] <= w) {
                d[w][i+1] = max(d[w][i+1], d[w - weight[i]][i] + cell[i]);
            }
        }
    }

    vector<int> solution;
    int w = W;
    int elem = weight.size();
    for (size_t i = weight.size(); i > 0; --i) {
        if (d[w][i] == d[w - weight[i-1]][i-1] + cell[i-1]) {
            solution.push_back(1);
            w -= weight[i-1];
        } else {
            solution.push_back(0);
        }
    }
    reverse(solution.begin(), solution.end());
    return make_pair(d[W][weight.size()], solution);
}

pair<int, pair<int, vector<int>>> knapsack_bu(int W, vector<int>& weight, vector<int>& cell) {
    int with_rep = knapsack_with_reps(W, weight, cell);
    pair<int, vector<int>> without_rep = knapsack_without_reps(W, weight, cell);

    return make_pair(with_rep, without_rep);
}

int main() {
    int W = 10;
    vector<int> weight = {6, 3, 4, 2};
    vector<int> cell = {30, 14, 16, 9};
    pair<int, pair<int, vector<int>>> result = knapsack_bu(W, weight, cell);
    cout << "with_rep_bu = " << result.first << endl;
    cout << "without_rep_bu = " << result.second.first << ", solution = [";
    for (size_t i = 0; i < result.second.second.size(); ++i) {
        cout << result.second.second[i];
        if (i != result.second.second.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    return 0;
}
