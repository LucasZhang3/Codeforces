//https://codeforces.com/contest/2206/problem/B
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        children[p].push_back(i);
    }

    vector<int> L(n + 1), H(n + 1);
    for (int v = n; v >= 1; --v) {
        if (children[v].empty()) {
            L[v] = H[v] = v;
        } else {
            vector<int> vals;
            for (int u : children[v]) {
                vals.push_back(L[u]);
                vals.push_back(H[u]);
            }
            sort(vals.begin(), vals.end());
            int m = vals.size();
            L[v] = vals[(m - 1) / 2];
            H[v] = vals[m / 2];
        }
    }
    cout << L[1] << '\n';
    return 0;
}