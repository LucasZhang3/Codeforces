//https://codeforces.com/contest/2211/problem/A
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        int n; cin>>n;
        for(int i=0;i<n;i++){int x;cin>>x;}
        int ans=(n==1)?1:2;
        for(int i=0;i<n;i++){
            cout<<ans<<" \n"[i==n-1];
        }
    }
}