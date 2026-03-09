//https://codeforces.com/contest/2206/problem/H
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;
    
    ll G = 0, sumD = 0;
    for (int i = 0; i + 1 < n; i++) {
        ll d = abs(a[i+1] - a[i]);
        G = __gcd(G, d);
        sumD += d;
    }
    
    ll a1 = a[0];
    ll min_a1 = (G == 0) ? a1 : (a1 - 1) % (2*G) + 1;
    cout << min_a1 + sumD << "\n";
}