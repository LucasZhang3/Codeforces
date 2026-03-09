//https://codeforces.com/contest/2207/problem/A
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        int ones = 0;
        for (char c : s) if (c == '1') ones++;

        if (ones == 0) {
            cout << "0 0\n";
            continue;
        }

        int add = 0;
        for (int i = 1; i + 1 < n; i++)
            if (s[i] == '0' && s[i - 1] == '1' && s[i + 1] == '1')
                add++;

        int mx = ones + add;

        vector<int> runs, zeros;
        for (int i = 0; i < n;) {
            if (s[i] == '1') {
                int c = 0;
                while (i < n && s[i] == '1') c++, i++;
                runs.push_back(c);
            } else {
                int z = 0;
                while (i < n && s[i] == '0') z++, i++;
                if (!runs.empty() && i < n) zeros.push_back(z);
            }
        }

        int m = runs.size();
        int mn = 0;
        int i = 0;

        while (i < m) {
            int sum = runs[i];
            int k = 1;
            while (i < m - 1 && zeros[i] == 1) {
                sum += runs[i + 1];
                k++;
                i++;
            }
            int R = sum + (k - 1);
            mn += R / 2 + 1;
            i++;
        }

        cout << mn << " " << mx << "\n";
    }
}