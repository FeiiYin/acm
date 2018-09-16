/*************************************************************************
    > File Name: k.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com 
    > Created Time: 2018年09月16日 12:04:44
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
 
int main() {
	int T; scanf("%d",&T);
	while(T--) {
		int n; scanf("%d",&n);
		int f[32];
		memset(f,0,sizeof(f));
		rep(i,1,n) {
			int x; scanf("%d",&x);
			int cnt = 0;
			while(x) x/=2, ++cnt;
			f[cnt]++;
		}
		int ans = 0;
		rep(i,1,32) ans=max(ans,f[i]);
		cout<<ans<<endl;
	}
	return 0;
}
