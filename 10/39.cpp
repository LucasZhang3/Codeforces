//https://codeforces.com/contest/2211/problem/C2
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
int par[MAXN], rnk[MAXN];
int cfix[MAXN], cgiven[MAXN];
int freq[MAXN];

int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

void unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    if (rnk[x] < rnk[y]) swap(x, y);
    par[y] = x;
    if (rnk[x] == rnk[y]) rnk[x]++;
    if (cfix[y] != -1) cfix[x] = cfix[y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n+1), b(n+1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];

        for (int i = 1; i <= n; i++) {
            par[i] = i; rnk[i] = 0;
            cfix[i] = -1; cgiven[i] = -1;
        }

        for (int j = 1; j <= n - k; j++) {
            if (a[j] == a[j+k]) {
                unite(j, j+k);
            } else {
                cfix[find(j)]   = a[j];
                cfix[find(j+k)] = a[j+k];
            }
        }

        bool ok = true;

        for (int i = 1; i <= n && ok; i++) {
            if (b[i] == -1) continue;
            int r = find(i);
            int v = cfix[r] != -1 ? cfix[r] : cgiven[r];
            if (v != -1) {
                if (b[i] != v) ok = false;
            } else {
                cgiven[r] = b[i];
            }
        }

        if (!ok) { cout << "NO\n"; continue; }

        for (int i = 1; i <= k; i++) freq[a[i]]++;

        for (int i = 1; i <= k && ok; i++) {
            int r = find(i);
            int v = cfix[r] != -1 ? cfix[r] : cgiven[r];
            if (v != -1) {
                if (freq[v] == 0) ok = false;
                else freq[v]--;
            }
        }

        for (int i = 1; i <= k; i++) freq[a[i]] = 0;

        cout << (ok ? "YES" : "NO") << "\n";
    }
}