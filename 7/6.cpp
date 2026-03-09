//https://codeforces.com/contest/2193/problem/D
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    if(!(cin >> t)) return 0;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i=0;i<n;i++) cin >> a[i];
        vector<ll> b(n);
        for(int i=0;i<n;i++) cin >> b[i];
        vector<ll> pref(n+1,0);
        for(int i=1;i<=n;i++) pref[i]=pref[i-1]+b[i-1];
        sort(a.begin(), a.end());
        ll ans = 0;
        
        for(int i=0;i<n;i++){
            if(i>0 && a[i]==a[i-1]) continue;
            int usable = n - i;
            int completed = int(upper_bound(pref.begin(), pref.end(), usable) - pref.begin() - 1);
            ll score = a[i] * 1LL * completed;
            if(score > ans) ans = score;
        }
        cout << ans << '\n';
    }
    return 0;
}