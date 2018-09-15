/*************************************************************************
    > File Name: k.sb.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com
    > Created Time: 2018年09月15日 14:23:34
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <cassert>
#include <iomanip>
using namespace std;

#define rep(i,a,b) for(int i = (a); i <= (b); ++i)
#define per(i,a,b) for(int i = (a); i >= (b); --i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define sqr(x) (x) * (x)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef pair<PII,int> PIII;
const int N = 100005;
const int P = 1000000007;
const ll mod = P;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const ld eps = 1e-8;
ll qmod(ll a,ll n,ll mod){ll ans=1;while(n){assert(ans>0);if(n&1ll)ans=ans*a%mod;n>>=1;a=a*a%mod;}return ans%mod;}

//head

//your code goes there

ll dp[10005], pw[30];
vector<int> v;
int main() {
	pw[1]=1;
	for(int i=2;i<30;++i) pw[i]=pw[i-1]*2;
	int T; scanf("%d",&T);
	while(T--) {
		int n, q; scanf("%d%d",&n,&q);
		v.clear();
        memset(dp,0,sizeof(dp));dp[0]=1;
		for(int i=0; i<n; ++i) {
			int a, b; scanf("%d%d",&a,&b);
			for(int j=1; j<=b; ++j) {
				v.pb(pw[j]*a);
			}
		}
		for(int i=0; i<SZ(v); ++i) {
			for(int j=10000; j>=v[i]; --j) {
				dp[j]+=dp[j-v[i]];
				dp[j]%=mod;
				//dp[j]=max(dp[j-v[i]], dp[j]);
			}
		}
		//for (int i = 0; i <= 100; i ++) cout << dp[i] << " "; cout << endl;
		while(q--) {
			int s; scanf("%d",&s);
			printf("%lld\n",dp[s]%mod);
		}
	}
	return 0;
}
