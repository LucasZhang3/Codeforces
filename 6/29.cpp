//https://codeforces.com/contest/2206/problem/D
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll NEG_INF = -1e18;

struct Func {
    ll M, B;
};

Func compose(const Func& L, const Func& R) {
    return { max(L.M, R.M + L.B), L.B + R.B };
}

const Func ID = { NEG_INF, 0 };

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> parent(n + 1);
    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; ++i) {
        int p; cin >> p;
        parent[i] = p;
        children[p].push_back(i);
    }
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> order;
    stack<int> st;
    st.push(1);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        order.push_back(u);
        for (int v : children[u]) st.push(v);
    }
    vector<int> sz(n + 1, 1);
    vector<int> heavy(n + 1, 0);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        int maxsz = 0;
        for (int v : children[u]) {
            sz[u] += sz[v];
            if (sz[v] > maxsz) {
                maxsz = sz[v];
                heavy[u] = v;
            }
        }
    }

    vector<ll> dp(n + 1), light(n + 1, 0);
    stack<pair<int, int>> st2;
    st2.push({1, 0});
    while (!st2.empty()) {
        auto [u, state] = st2.top(); st2.pop();
        if (state == 0) {
            st2.push({u, 1});
            for (int v : children[u]) st2.push({v, 0});
        } else {
            ll sum = 0;
            for (int v : children[u]) sum += dp[v];
            dp[u] = max(a[u], sum);
            if (heavy[u]) light[u] = sum - dp[heavy[u]];
            else light[u] = sum;
        }
    }

    vector<int> hld_order;
    stack<int> st3;
    st3.push(1);
    while (!st3.empty()) {
        int u = st3.top(); st3.pop();
        hld_order.push_back(u);
        for (int v : children[u]) if (v != heavy[u]) st3.push(v);
        if (heavy[u]) st3.push(heavy[u]);
    }

    vector<int> head(n + 1), pos(n + 1), chain_id(n + 1);
    vector<vector<int>> chains;
    int cur_chain = -1;
    for (int i = 0; i < (int)hld_order.size(); ++i) {
        int u = hld_order[i];
        if (i == 0) {
            cur_chain++;
            chains.emplace_back();
            head[u] = u;
            chain_id[u] = cur_chain;
            pos[u] = 0;
            chains.back().push_back(u);
        } else {
            int p = parent[u];
            if (heavy[p] == u) {
                head[u] = head[p];
                chain_id[u] = chain_id[p];
                pos[u] = chains[chain_id[u]].size();
                chains[chain_id[u]].push_back(u);
            } else {
                cur_chain++;
                chains.emplace_back();
                head[u] = u;
                chain_id[u] = cur_chain;
                pos[u] = 0;
                chains.back().push_back(u);
            }
        }
    }
    int num_chains = chains.size();
    vector<int> chain_len(num_chains);
    for (int c = 0; c < num_chains; ++c) chain_len[c] = chains[c].size();

    struct SegTree {
        int n;
        vector<Func> t;
        SegTree(int sz, const vector<Func>& arr) {
            n = 1;
            while (n < sz) n <<= 1;
            t.assign(2 * n, ID);
            for (int i = 0; i < sz; ++i) t[n + i] = arr[i];
            for (int i = n - 1; i >= 1; --i) t[i] = compose(t[2 * i], t[2 * i + 1]);
        }
        void upd(int idx, const Func& f) {
            int i = idx + n;
            t[i] = f;
            for (i >>= 1; i; i >>= 1) t[i] = compose(t[2 * i], t[2 * i + 1]);
        }
        Func query(int l, int r) {
            l += n; r += n;
            Func leftRes = ID, rightRes = ID;
            while (l <= r) {
                if (l & 1) leftRes = compose(leftRes, t[l++]);
                if (!(r & 1)) rightRes = compose(t[r--], rightRes);
                l >>= 1; r >>= 1;
            }
            return compose(leftRes, rightRes);
        }
    };

    vector<SegTree> segs;
    for (int c = 0; c < num_chains; ++c) {
        vector<Func> init(chain_len[c]);
        for (int i = 0; i < chain_len[c]; ++i) {
            int node = chains[c][i];
            init[i] = {a[node], light[node]};
        }
        segs.emplace_back(chain_len[c], init);
    }

    auto get_dp = [&](int node) -> ll {
        int c = chain_id[node];
        int l = pos[node];
        int r = chain_len[c] - 1;
        Func res = segs[c].query(l, r);
        return max(res.M, res.B);
    };

    auto update_node = [&](int node, ll new_a, ll new_light) {
        int c = chain_id[node];
        segs[c].upd(pos[node], {new_a, new_light});
    };

    cout << get_dp(1) << '\n';

    while (q--) {
        int u; ll x;
        cin >> u >> x;
        ll old_a = a[u];
        a[u] = x;

        int h = head[u];
        ll old_head = get_dp(h);
        update_node(u, x, light[u]);
        ll new_head = get_dp(h);

        if (new_head != old_head) {
            ll delta = new_head - old_head;
            int cur = h;
            while (true) {
                int p = parent[cur];
                if (p == 0) break;
                light[p] += delta;
                ll old_p_head = get_dp(head[p]);
                update_node(p, a[p], light[p]);
                ll new_p_head = get_dp(head[p]);
                ll delta_p = new_p_head - old_p_head;
                if (delta_p == 0) break;
                delta = delta_p;
                cur = head[p];
            }
        }
        cout << get_dp(1) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}