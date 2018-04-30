/*
 * @Samaritan_infi
 */
/// 考虑到很多个分母是相等的，所以对查询分块。（对a[i]分块不仅会T而且计算log精度也不够）
/// 然后 对每一个a[i] 看log q (a[i]) 等于 j 时的查询的范围是多少 ， 此时 范围是 [pow(a[i], 1.0/ j), pos]
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
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
int n,m;

const int maxn = 5e5 + 5;
const int mod = 1e9;

void show(ll a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

ll a[maxn];
pair< ll, ll > temp[maxn];
ll sum[maxn];
ll q[maxn];

int main() {
    int kase = read();
    while(kase --) {
        int n = read(), m = read();
        for(int i = 0; i < n; i ++) scanf("%lld", &a[i]);
        for(int i = 0; i < m; i ++) {
            scanf("%lld", &temp[i].first);
            temp[i].second = i + 1;
        }
        sort(temp, temp + m);
        sum[0] = 0;
        //q[0] = temp[0].first;

        for(int i = 1; i <= m; i ++) {
            q[i] = temp[i - 1].first;
            sum[i] = sum[i - 1] + temp[i - 1].second;
        }
//        show(q, m);
//        show(sum, m);
        ll ans = 0;
        for(int i = 0; i < n; i ++) {
            int pos = m;
            for(int j = 1; j <= 31; j ++) {
                if(! pos) continue;
                int now = ceil( pow(a[i], 1.0/j) );
                int next_pos = lower_bound(q + 1, q + 1 + m, now) - q;
                ans = (ans + (sum[pos] - sum[next_pos - 1])*(a[i]/j) % mod ) % mod;
                pos = next_pos - 1;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
