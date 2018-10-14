/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e3 + 5;


struct node {
    int id, val;
    node () {}
    node (int a, int b) : id(a), val(b) {}
    bool operator < (const node & k) const {
        return val > k.val;
    }
};

priority_queue<node> pq;
int par[N];

int find_par(int x) {
    if (x == par[x]) return x;
    return par[x] = find_par(par[x]);
}

bool unite (int x, int y) {
    int a = find_par(x), b = find_par(y);
    if (a == b) {
        return false;
    }
    par[a] = b;
    return true;
}

char arr[N], brr[N];
int num[26];
bool vis[N];

LL work (int n) {
    LL ans = 0;
    for (int i = 0; i < 26; ++i) if (num[i]) {
        priority_queue<node> pq;
        for (int j = 0; j < n; ++j) if (! vis[j]) {
            if (arr[j] - 'A' <= i)
                pq.push(node(j, i - arr[j] + 'A'));
            else {
                //pq.push(node(j, arr[j] - 'A' - i));
                pq.push(node(j, 'Z' - arr[j] + 1 + i));
            }
        }
        for (int j = 0; j < num[i]; ++j) {
            node tt = pq.top(); pq.pop();
            ans += tt.val;
            vis[tt.id] = true;
        }
    }
    return ans;
}

int main () {
    //int kase; scanf("%d", &kase);
    while (~ scanf("%s", arr)) {
        scanf("%s", brr);
        memset(num, 0, sizeof num);
        int a_len = strlen(arr), b_len = strlen(brr);
        for (int i = 0; i < b_len; ++i) {
            num[ brr[i] - 'A' ] ++;
        }
        memset(vis, 0, sizeof vis);
        printf("%lld\n", work(a_len));
    }
    return 0;
}
