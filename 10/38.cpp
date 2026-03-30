//https://codeforces.com/contest/2211/problem/C1
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> a(n+1), b(n+1);
        for(int i = 1; i <= n; i++) cin >> a[i];
        for(int i = 1; i <= n; i++) cin >> b[i];
        
        bool ok = true;
        
        for(int i = 1; i <= n-k; i++){
            if(b[i] != -1 && b[i] != a[i]){
                ok = false;
                break;
            }
        }
        
        if(ok){
            for(int i = k+1; i <= n; i++){
                if(b[i] != -1 && b[i] != a[i]){
                    ok = false;
                    break;
                }
            }
        }
        
        if(ok && n-k+1 <= k){
            multiset<int> ms;
            for(int i = n-k+1; i <= k; i++) ms.insert(a[i]);
            for(int i = n-k+1; i <= k; i++){
                if(b[i] != -1){
                    auto it = ms.find(b[i]);
                    if(it == ms.end()){
                        ok = false;
                        break;
                    }
                    ms.erase(it);
                }
            }
        }
        
        cout << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}