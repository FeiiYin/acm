/*************************************************************************
    > File Name: c.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com 
    > Created Time: 2018/11/17 13:22:02
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
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const ld eps = 1e-8;
ll qmod(ll a,ll n,ll mod){ll ans=1;while(n){assert(ans>0);if(n&1ll)ans=ans*a%mod;n>>=1;a=a*a%mod;}return ans%mod;}

//head

//your code goes there

const ll mod=1e9;
struct Matrix {
	ll a[2][2];
	void init() {
		for(int i=0;i<2;++i)
			for(int j=0;j<2;++j)
				a[i][j]=0;
	}
	void print() {
		for(int i=0;i<2;++i)
			for(int j=0;j<2;++j) 
				printf("%lld%c",a[i][j]," \n"[j==1]);
	}
};
Matrix mul(Matrix a, Matrix b) {
	Matrix ans; ans.init();
	for(int i=0;i<2;++i)
		for(int j=0;j<2;++j)
			for(int k=0;k<2;++k)
				ans.a[i][j]+=a.a[i][k]*b.a[k][j], ans.a[i][j]%=mod;
	return ans;
}
Matrix powmod(Matrix a, ll n) {
	Matrix ans; ans.init(); ans.a[0][0]=ans.a[1][1]=1;
	while(n) {
		if(n&1ll) ans=mul(ans,a);
		n/=2;
		a=mul(a,a);
	}
	return ans;
}
int main() {
	int T; scanf("%d",&T);
	while(T--) {
		int cas; ll n; scanf("%d%lld",&cas,&n);
		if(n<=2) {
			printf("%d 1\n",cas,1);
			continue;
		}
		Matrix a; a.init();
		a.a[0][0]=a.a[0][1]=a.a[1][0]=1;
		Matrix ans=powmod(a,n-2);
		ll res=(ans.a[0][0]+ans.a[0][1])%mod;
		//ans.print();
		printf("%d %lld\n",cas,res);
	}
	return 0;
}
