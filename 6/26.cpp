//https://codeforces.com/contest/2206/problem/J
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 200001;
int n, d;
int a[MAXN], b[MAXN], pos_a[MAXN], pos_b[MAXN], p[MAXN];
ll C;

int is_asc(int i) {
    if (i < 0 || i+1 > n) return 0;
    return p[i+1] > p[i] ? 1 : 0;
}

void swap_p(int j, int k) {
    if (j == k) return;
    int ids[4] = {j-1, j, k-1, k}, uniq[4]; int cnt = 0;
    for (int x : ids) {
        if (x < 0 || x+1 > n) continue;
        bool dup = false;
        for (int i = 0; i < cnt; i++) if (uniq[i] == x) { dup = true; break; }
        if (!dup) uniq[cnt++] = x;
    }
    for (int i = 0; i < cnt; i++) C -= is_asc(uniq[i]);
    swap(p[j], p[k]);
    for (int i = 0; i < cnt; i++) C += is_asc(uniq[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    for (int i = 1; i <= n; i++) { cin >> a[i]; pos_a[a[i]] = i; }
    for (int i = 1; i <= n; i++) { cin >> b[i]; pos_b[b[i]] = i; }

    p[0] = 0;
    for (int i = 1; i <= n; i++) p[i] = pos_a[b[i]];

    C = 0;
    for (int i = 1; i <= n; i++) if (p[i] > p[i-1]) C++;

    auto answer = [&]() -> ll {
        return (ll)p[n] + (ll)n * (n - 1 - C);
    };

    cout << answer() << "\n";

    for (int q = 0; q < d-1; q++) {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 1) {
            int u = a[x], v = a[y];
            int j = pos_b[u], k = pos_b[v];
            swap_p(j, k);
            pos_a[u] = y; pos_a[v] = x;
            swap(a[x], a[y]);
        } else {
            int u = b[x], v = b[y];
            swap_p(x, y);
            pos_b[u] = y; pos_b[v] = x;
            swap(b[x], b[y]);
        }
        cout << answer() << "\n";
    }
}