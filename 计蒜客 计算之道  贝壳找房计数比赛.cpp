/*
 * @Samaritan_infi
 */
 
/// 学习知识点： C(a1)(sum(a)) * C(a2)(sum(a)-a1) * C(a3)(sum(a)-a1-a2) ... = sum(a)!/ ( a1! * a2! ... )
/// 注意这里 不管是包含几个子串，都可以将其他剩余的看成无关字符，这样aaa = aa+a, aaa = a + aa 

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

const int maxn = 2e5 + 5;

struct node {
    int x, y;
    bool operator < (const node &k) const {
        if(x == k.x) return y > k.y;
        return x < k.x;
    }
};

char a[maxn], b[maxn];
int c[30], d[30];

bool check(int a[], int b[]) {
    for(int i = 0; i < 26; i ++) {
        if(a[i] >= b[i]) continue;
        return false;
    }
    return true;
}

const int mod = 1e9 + 7;
ll fab[maxn];
ll inv[maxn];
void init() {
    fab[0] = 1;
    for(ll i = 1; i <= 2e5; i ++) {
        fab[i] = fab[i - 1] * i % mod;
    }
    inv[1] = 1;
    for(int i = 2; i <= 2e5; i ++)
        inv[i] = inv[mod % i] * (mod - mod/i)%mod;
}
const int MOD = mod;
inline int pow(const int n, const int k) {
    long long ans = 1;
    for (long long num = n, t = k; t; num = num * num % MOD, t >>= 1) if (t & 1) ans = ans * num % MOD;
    return ans;
}
inline int INV(const int num) {
    return pow(num, MOD - 2);
}

int main() {
    init();
    int kase = read();

    while(kase --) {
        memset(d, 0, sizeof d);
        memset(c, 0, sizeof c);
        scanf("%s", a);
        scanf("%s", b);
        int la = strlen(a), lb = strlen(b);
        for(int i = 0; i < lb; i ++) {
            d[ b[i] - 'a' ] ++;
        }
        for(int i = 0; i < la; i ++) {
            c[ a[i] - 'a' ] ++;
        }
        if(! check(c, d)) {
            puts("0");
            continue;
        }
        int num = 0;
        ll ans = fab[la - lb], fenmu = 1;
        for(int i = 0; i < 26; i ++) {
            c[i] -= d[i];
            if(c[i] > 0) {
                fenmu = (fenmu * fab[ c[i] ]) % mod;
                //ans = (ans * inv[ fab[ c[i] ] ]) % mod;
            }
        }
        ans = ans * INV(fenmu) % mod;
        //ll ans = fab[num];
        //cout << ans << endl;

        ans = (ans * (la - lb + 1)) % mod;
        printf("%lld\n", ans);
    }
	return 0;
}
