///
/**
 * @Samaritan
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define pb emplace_back
#define fi first
#define se second
#define PII pair<int, int>
#define PLL pair<LL, LL>
#define PLI pair<LL, int>

LL quick_pow (LL a, LL b, LL mod) {
    LL ans = 1, base = a;
    while (b) {
        if (b & 1) (ans *= base) %= mod;
        b >>= 1;
        (base *= base) %= mod;
    }
    return ans;
}

inline int log2(const float &x) {
    return ((unsigned &) x >> 23 & 255) - 127;
}

void show(int arr[], int len) {
    for (int i = 0; i <= len; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
struct node {
    int dist, id;
    node() {
    }
    node(int d, int i) : dist(d), id(i) {}
    bool operator < (const node& k) const {
        if (dist == k.dist)
            return id <= k.id;
        return dist < k.dist;
    }
};

const int mod = 998244353;
const int N = 2e3 + 5;
const int logN = 30;
const int INF = 0x3f3f3f3f;

char a[N], b[N], c[N];
const int hash_key = 211;
unsigned long long ha[N], mi[N], hb[N], hc[N];

unsigned long long hash_val(int l, int r, unsigned long long hash_arr[]) {
    return hash_arr[r] - hash_arr[l - 1] * mi[r - l + 1];
}
unordered_set<unsigned long long> ss;
int main() {
    scanf("%s %s %s", a + 1, b + 1, c + 1);
    int alen = strlen(a + 1);
    int blen = strlen(b + 1);
    int clen = strlen(c + 1);
    mi[0] = 1;
    for (int i = 1; i <= alen; ++i) {
        mi[i] = mi[i - 1] * hash_key;
        ha[i] = ha[i - 1] * hash_key + a[i];
    }
    for (int i = 1; i <= blen; ++i) {
        hb[i] = hb[i - 1] * hash_key + b[i];
    }
    for (int i = 1; i <= clen; ++i) {
        hc[i] = hc[i - 1] * hash_key + c[i];
    }
    int min_len = max(blen, clen);
    unsigned long long prefix = hash_val(1, blen, hb);
    unsigned long long suffix = hash_val(1, clen, hc);
//    cout << prefix << " " << suffix << endl;
    for (int len = min_len; len <= alen; ++len) {
        for (int l = 1, r = l + len - 1; r <= alen; ++l, ++r) {
            unsigned long long now_prefix = hash_val(l, l + blen - 1, ha);
            unsigned long long now_suffix = hash_val(r - clen + 1, r, ha);
//            cout << a[l] << " " << a[r] << endl;
//            cout << now_prefix << " " << now_suffix << endl;
            if (now_prefix == prefix && now_suffix == suffix) {
                ss.insert(hash_val(l, r, ha));
//                cout << hash_val(l, r, ha) << endl;
            }
        }
    }
    printf("%d\n", ss.size());
    return 0;
}
