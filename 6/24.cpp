//https://codeforces.com/contest/2206/problem/K
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        vector<int> cnt(10,0);
        for (char c: s) cnt[c-'0']++;
        int maxk = n/4;
        auto feasible = [&](int k)->bool {
            if (4*k > n) return false;
            int low_x = max(0, k - cnt[0]);
            int high_x = min(k, cnt[1]);
            if (low_x > high_x) return false;
            for (int x = low_x; x <= high_x; ++x) {
                int rem[10];
                for (int d=0;d<10;++d) rem[d]=cnt[d];
                rem[1] -= x;
                rem[0] -= (k - x);
                if (rem[1] < 0 || rem[0] < 0) continue;
                int mt_need = k;
                for (int d = 2; d <= 5 && mt_need > 0; ++d) {
                    int take = min(rem[d], mt_need);
                    rem[d] -= take;
                    mt_need -= take;
                }
                for (int d = 0; d <= 1 && mt_need > 0; ++d) {
                    int take = min(rem[d], mt_need);
                    rem[d] -= take;
                    mt_need -= take;
                }
                if (mt_need > 0) continue;
                int total_rem = 0;
                for (int d=0;d<10;++d) total_rem += rem[d];
                if (total_rem < 2*k) continue;
                if (rem[0] + rem[1] < x) continue;
                return true;
            }
            return false;
        };
        int l = 0, r = maxk;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (feasible(mid)) l = mid; else r = mid - 1;
        }
        cout << l << '\n';
    }
    return 0;
}