//https://codeforces.com/contest/2206/problem/E
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Q{int l,r,i;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    if(!(cin>>n>>m)) return 0;
    int k = n - m + 1;
    vector<ll> s(max(0,k)+2);
    for(int i=1;i<=k;i++) cin>>s[i];
    int q; cin>>q;
    vector<pair<int,int>> queries(q);
    for(int i=0;i<q;i++) cin>>queries[i].first>>queries[i].second;

    vector<ll> diff(n+2,0), d(n+2,0);
    for(int j=m+1;j<=n;j++){
        int idx1 = j-m+1;
        int idx0 = j-m;
        ll v1 = (idx1>=1 && idx1<=k) ? s[idx1] : 0;
        ll v0 = (idx0>=1 && idx0<=k) ? s[idx0] : 0;
        diff[j] = v1 - v0;
    }
    for(int j=1;j<=n;j++){
        if(j<=m) d[j]=0;
        else d[j] = d[j-m] + diff[j];
    }
    ll T1 = (m<=n? accumulate(d.begin()+1, d.begin()+m+1, 0LL) : 0LL);
    ll C = (k>=1? s[1] : 0) - T1;

    ll minD = LLONG_MAX;
    for(int i=1;i<=n;i++) if(d[i]<minD) minD=d[i];
    ll SHIFT = 0;
    if(minD<0) SHIFT = -minD;
    vector<ll> d2(n+1);
    for(int i=1;i<=n;i++) d2[i]=d[i]+SHIFT;

    vector<string> ans(q);
    vector<Q> useful;
    useful.reserve(q);
    for(int i=0;i<q;i++){
        int l=queries[i].first, r=queries[i].second;
        if(r-l+1 < m) ans[i]="unbounded";
        else useful.push_back({l,r,i});
    }
    if(!useful.empty()){
        int B = max(1, (int)(n / max(1.0, sqrt((double)q))));
        int blocks = (n + B - 1) / B;
        vector<vector<Q>> by(blocks);
        for(auto &qu: useful){
            int b = (qu.l-1)/B;
            by[b].push_back(qu);
        }
        vector<ll> bigMax(m);
        vector<int> stamp(m,0);
        vector<ll> smallMax(m);
        int curStamp = 1;
        for(int b=0;b<blocks;b++){
            if(by[b].empty()) continue;
            int Lb = b*B + 1;
            int Rb = min(n, (b+1)*B);
            for(int i=0;i<m;i++) bigMax[i]=0;
            ll sumBig = 0;
            int curR = Rb;
            sort(by[b].begin(), by[b].end(), [](const Q&a,const Q&b){ return a.r < b.r; });
            for(auto &qu: by[b]){
                int L = qu.l, R = qu.r;
                while(curR < R){
                    ++curR;
                    int res = (curR-1) % m;
                    ll val = d2[curR];
                    if(val > bigMax[res]){
                        sumBig += val - bigMax[res];
                        bigMax[res] = val;
                    }
                }
                int left = L;
                int right = min(R, Rb);
                vector<int> touched;
                touched.reserve(Rb - L + 1);
                curStamp++;
                for(int pos=left; pos<=right; ++pos){
                    int ridx = (pos-1) % m;
                    if(stamp[ridx] != curStamp){
                        stamp[ridx] = curStamp;
                        smallMax[ridx] = d2[pos];
                        touched.push_back(ridx);
                    } else {
                        if(d2[pos] > smallMax[ridx]) smallMax[ridx] = d2[pos];
                    }
                }
                ll total = sumBig;
                for(int rid: touched){
                    if(smallMax[rid] > bigMax[rid]) total += smallMax[rid] - bigMax[rid];
                }
                ll Sprime = C + total;
                ll t;
                if(Sprime >= 0) t = (Sprime + m - 1) / m;
                else t = Sprime / m;
                t -= SHIFT;
                ans[qu.i] = to_string(t);
            }
        }
    }

    for(int i=0;i<q;i++) cout<<ans[i]<<"\n";
    return 0;
}