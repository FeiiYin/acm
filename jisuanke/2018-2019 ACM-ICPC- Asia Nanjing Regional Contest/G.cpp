/*************************************************************************
    > File Name: g.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com 
    > Created Time: 2018/11/18 13:37:05
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

#define rep(i,a,b) for(int i = (a); i < (b); ++i)
#define per(i,a,b) for(int i = (b); i > (a); --i)
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
ll powmod(ll a,ll n){ll ans=1;while(n){assert(ans>0);if(n&1ll)ans=ans*a%mod;n>>=1;a=a*a%mod;}return ans%mod;}

//head

//your code goes there
 
int main() {
	int T; scanf("%d",&T);
	ll inv2=powmod(2ll,mod-2), inv3=powmod(3ll,mod-2), inv4=powmod(4ll,mod-2);
	while(T--) {
		ll n; scanf("%lld",&n);
		ll ans=n*(n+1)%mod*(n+2)%mod*(n+3)%mod*inv2%mod*inv3%mod*inv4%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
