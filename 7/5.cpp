//https://codeforces.com/contest/2193/problem/C
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];

        vector<int> M(n);
        M[n - 1] = max(a[n - 1], b[n - 1]);
        for (int i = n - 2; i >= 0; --i) {
            M[i] = max({a[i], b[i], M[i + 1]});
        }

        vector<ll> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + M[i];
        }

        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            --l; --r;
            ll ans = pref[r + 1] - pref[l];
            cout << ans << " \n"[i == q - 1];
        }
    }
    return 0;
}