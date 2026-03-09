//https://codeforces.com/contest/2206/problem/F
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool inv) {
    int n = a.size();
    for (int i=1,j=0;i<n;i++){
        int bit = n>>1;
        for (; j&bit; bit>>=1) j ^= bit;
        j ^= bit;
        if (i<j) swap(a[i], a[j]);
    }
    for (int len=2; len<=n; len<<=1){
        double ang = 2*PI/len*(inv?-1:1);
        cd wlen(cos(ang), sin(ang));
        for (int i=0;i<n;i+=len){
            cd w(1);
            for (int j=0;j<len/2;j++){
                cd u = a[i+j];
                cd v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if (inv){
        for (cd & x: a) x /= n;
    }
}

vector<ll> convolution(const vector<ll>& a, const vector<ll>& b){
    int n = a.size(), m = b.size();
    if (!n || !m) return {};
    int sz = 1;
    while (sz < n+m-1) sz <<= 1;
    vector<cd> fa(sz);
    for (int i=0;i<n;i++) fa[i] = cd(a[i],0);
    for (int i=0;i<m;i++) fa[i] += cd(0,b[i]);
    fft(fa, false);
    vector<cd> fb(sz);
    for (int i=0;i<sz;i++){
        int j = (sz - i) & (sz - 1);
        cd a1 = (fa[i] + conj(fa[j])) * cd(0.5, 0);
        cd a2 = (fa[i] - conj(fa[j])) * cd(0, -0.5);
        fb[i] = a1 * a2;
    }
    fft(fb, true);
    vector<ll> res(n+m-1);
    for (int i=0;i<n+m-1;i++) res[i] = (ll) llround(fb[i].real());
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k;
    if(!(cin>>n>>k)) return 0;
    string S;
    cin>>S;
    vector<ll> Z(n), V(n);
    for (int i=0;i<n;i++){
        if (S[i]=='0') Z[i]=1, V[i]=0;
        else Z[i]=0, V[i]=S[i]-'0';
    }
    vector<ll> h(max(0,n-1));
    ll baseH=0;
    for (int i=0;i+1<n;i++){
        h[i] = Z[i]*V[i+1] + Z[i+1]*V[i];
        baseH += h[i];
    }
    vector<ll> Vr(n), Zr(n);
    for (int i=0;i<n;i++){
        Vr[i] = V[n-1-i];
        Zr[i] = Z[n-1-i];
    }
    vector<ll> conv1 = convolution(Z, Vr);
    vector<ll> conv2 = convolution(V, Zr);
    vector<ll> excluded(n+1);
    for (int d=1; d<=n; d++){
        ll sum=0;
        for (int j=d; j<=n-1; j+=d) sum += h[j-1];
        excluded[d]=sum;
    }
    vector<ll> f(n+1);
    for (int w=1; w<=n; w++){
        ll vert = 0;
        if (w<=n-1){
            vert = conv1[n-1-w] + conv2[n-1-w];
        }
        f[w] = baseH - excluded[w] + vert;
    }
    vector<ll> vals;
    vals.reserve(n);
    for (int w=1; w<=n; w++) vals.push_back(f[w]);
    nth_element(vals.begin(), vals.begin()+k-1, vals.end(), greater<ll>());
    ll kth = vals[k-1];
    cout<<kth<<"\n";
    return 0;
}