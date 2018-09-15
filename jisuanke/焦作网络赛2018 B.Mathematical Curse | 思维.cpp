/*************************************************************************
    > File Name: b.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com 
    > Created Time: 2018年09月15日 14:50:07
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
 
char op[10];
int n, m, k, a[1005];
ll Max[1005][10], Min[1005][10];
ll calc(ll x, int a, char c) {
	if(c == '+') {
		return x+a;
	} else if(c == '-') {
		return x-a;
	} else if(c == '*') {
		return x*a;
	} else if(a != 0) {
		return x/a;
	}
	return x;
}
int main() {
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d",&n,&m,&k);
		rep(i,1,n) scanf("%d",&a[i]);
		scanf("%s",op+1);
		rep(i,0,n) rep(j,0,m+2) Max[i][j]=-LLINF,Min[i][j]=LLINF;
		Max[0][0]=Min[0][0]=k;
		for(int i=1; i<=n; ++i) {
			for(int j=0; j<=m; ++j) {
				// 不选
				Max[i][j] = max(Max[i-1][j], Max[i][j]);
				Min[i][j] = min(Min[i-1][j], Min[i][j]);
				if(j == 0) continue;
				//选
				if(abs(Max[i-1][j-1])!=LLINF) {
					Max[i][j]=max(Max[i][j], calc(Max[i-1][j-1], a[i], op[j]));
					Max[i][j]=max(Max[i][j], calc(Min[i-1][j-1], a[i], op[j]));
				}
				if(abs(Min[i-1][j-1])!=LLINF) {
					Min[i][j]=min(Min[i][j], calc(Min[i-1][j-1], a[i], op[j]));
					Min[i][j]=min(Min[i][j], calc(Max[i-1][j-1], a[i], op[j]));
				}
			}
		}
		printf("%lld\n",max(Max[n][m], Min[n][m]));
	}
	return 0;
}
