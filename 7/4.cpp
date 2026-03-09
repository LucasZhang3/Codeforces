//https://codeforces.com/contest/2193/problem/B
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
        }

        vector<int> smax(n), sidx(n);
        smax[n - 1] = p[n - 1];
        sidx[n - 1] = n - 1;
        for (int i = n - 2; i >= 0; --i) {
            if (p[i] > smax[i + 1]) {
                smax[i] = p[i];
                sidx[i] = i;
            } else {
                smax[i] = smax[i + 1];
                sidx[i] = sidx[i + 1];
            }
        }

        int i = 0;
        while (i < n && p[i] == smax[i]) {
            ++i;
        }
        if (i < n) {
            int j = sidx[i];
            reverse(p.begin() + i, p.begin() + j + 1);
        }

        for (int k = 0; k < n; ++k) {
            cout << p[k] << " \n"[k == n - 1];
        }
    }
    return 0;
}