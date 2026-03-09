//https://codeforces.com/contest/2193/problem/E
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin >> T)) return 0;
    while(T--){
        int n;
        cin >> n;
        vector<int> a(n+1);
        vector<int> present(n+1,0);
        for(int i=1;i<=n;i++){
            cin >> a[i];
            if(a[i] <= n) present[a[i]] = 1;
        }
        vector<vector<int>> divs(n+1);
        for(int d=1; d<=n; ++d){
            for(int m=d; m<=n; m+=d) divs[m].push_back(d);
        }
        vector<int> dp(n+1, INF);
        dp[1] = 0;
        for(int m=1; m<=n; ++m){
            for(int d : divs[m]){
                if(d == 1) continue;
                if(d <= n && present[d]){
                    int k = m / d;
                    dp[m] = min(dp[m], (k>=1? dp[k] : INF) + 1);
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(i==1){
                if(present[1]) cout << 1;
                else cout << -1;
            } else {
                if(dp[i] >= INF) cout << -1;
                else cout << dp[i];
            }
            if(i==n) cout << '\n'; else cout << ' ';
        }
    }
    return 0;
}