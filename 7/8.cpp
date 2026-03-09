//https://codeforces.com/contest/2193/problem/F
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

struct Group {
    ll x, L, R;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n, Ax, Ay, Bx, By;
        cin >> n >> Ax >> Ay >> Bx >> By;
        vector<ll> xs(n), ys(n);
        for (int i = 0; i < n; i++) cin >> xs[i];
        for (int i = 0; i < n; i++) cin >> ys[i];

        map<ll, vector<ll>> mp;
        for (int i = 0; i < n; i++) {
            mp[xs[i]].push_back(ys[i]);
        }

        vector<Group> groups;
        for (auto &p : mp) {
            ll x = p.first;
            auto &vec = p.second;
            ll L = *min_element(vec.begin(), vec.end());
            ll R = *max_element(vec.begin(), vec.end());
            groups.push_back({x, L, R});
        }

        if (groups.empty()) {
            ll ans = (Bx - Ax) + abs(Ay - By);
            cout << ans << '\n';
            continue;
        }

        int k = groups.size();
        vector<ll> dp(2);
        Group &g0 = groups[0];
        dp[0] = (g0.x - Ax) + abs(Ay - g0.L) + (g0.R - g0.L);
        dp[1] = (g0.x - Ax) + abs(Ay - g0.R) + (g0.R - g0.L);

        for (int i = 1; i < k; i++) {
            Group &prev = groups[i - 1];
            Group &cur = groups[i];
            ll dx = cur.x - prev.x;
            ll new0 = min(dp[0] + dx + abs(prev.R - cur.L),
                          dp[1] + dx + abs(prev.L - cur.L)) + (cur.R - cur.L);
            ll new1 = min(dp[0] + dx + abs(prev.R - cur.R),
                          dp[1] + dx + abs(prev.L - cur.R)) + (cur.R - cur.L);
            dp[0] = new0;
            dp[1] = new1;
        }

        Group &last = groups.back();
        ll ans0 = dp[0] + (Bx - last.x) + abs(last.R - By);
        ll ans1 = dp[1] + (Bx - last.x) + abs(last.L - By);
        ll ans = min(ans0, ans1);
        cout << ans << '\n';
    }
    return 0;
}