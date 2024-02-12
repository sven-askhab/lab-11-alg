#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int list_bottom_up(const vector<int>& a) {
    int n = a.size();
    vector<int> D(n, 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i] && D[j] + 1 > D[i]) {
                D[i] = D[j] + 1;
            }
        }
    }

    return *max_element(D.begin(), D.end());
}

vector<int> using_prev(const vector<int>& prev, int m_index) {
    vector<int> l;
    while (true) {
        l.push_back(m_index);
        if (prev[m_index] == -1) {
            break;
        }
        m_index = prev[m_index];
    }
    reverse(l.begin(), l.end());
    return l;
}

vector<int> without_prev(const vector<int>& d, int ans, int m_index, const vector<int>& a) {
    vector<int> l;
    while (true) {
        l.push_back(m_index);
        if (ans == 1) {
            break;
        }
        ans -= 1;
        while (true) {
            m_index -= 1;
            if (d[m_index] == ans && a[m_index] < a[l.back()]) {
                break;
            }
        }
    }
    reverse(l.begin(), l.end());
    return l;
}

pair<int, pair<vector<int>, vector<int>>> list_bottom_up_2(const vector<int>& a) {
    int n = a.size();
    vector<int> d(n, 1);
    vector<int> prev(n, -1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i] && d[j] + 1 > d[i]) {
                d[i] = d[j] + 1;
                prev[i] = j;
            }
        }
    }

    int ans = 0, max_index = 0;
    for (int i = 0; i < n; ++i) {
        if (ans < d[i]) {
            ans = d[i];
            max_index = i;
        }
    }

    vector<int> list_using_prev = using_prev(prev, max_index);
    vector<int> list_without_prev = without_prev(d, ans, max_index, a);

    return make_pair(ans, make_pair(list_using_prev, list_without_prev));
}

int main() {
    vector<int> a = {7, 2, 1, 3, 8, 4, 9, 1, 2, 6, 5, 9, 3, 8, 1};
    cout << list_bottom_up(a) << endl;
    auto result = list_bottom_up_2(a);
    cout << result.first << endl;
    cout << "Using prev: [";
    for (size_t i = 0; i < result.second.first.size(); ++i) {
        cout << result.second.first[i];
        if (i != result.second.first.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    cout << "Without prev: [";
    for (size_t i = 0; i < result.second.second.size(); ++i) {
        cout << result.second.second[i];
        if (i != result.second.second.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    return 0;
}
