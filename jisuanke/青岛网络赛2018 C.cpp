/*************************************************************************
    > File Name: c.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com 
    > Created Time: 2018年09月16日 12:24:17
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

struct op {
	char op[5];
	int x, y;
} a[10005];
bool vis[10005][256];
int add (int x, int y) {
	return (x + y) % 256;
}
int main() {
	int T; scanf("%d",&T);
	while(T--) {
		int n; scanf("%d",&n);
		memset(vis,0,sizeof(vis));
		rep(i,1,n) {
			scanf("%s%d",a[i].op,&a[i].x);
			if(a[i].op[0]!='a') scanf("%d",&a[i].y);
		}
		rep(i,0,255) vis[n+1][i]=1;
		int pos = 1, now = 0;
		while(!vis[pos][now]) {
			vis[pos][now]=1;
			//cout << pos << ' ' << now << endl;
			if(a[pos].op[0]=='a') now=add(now,a[pos].x),++pos;
			else if(a[pos].op[1]=='e') {
				if(now==a[pos].x) pos=a[pos].y;
				else ++pos;
			} else if(a[pos].op[1]=='n') {
				if(now==a[pos].x) ++pos;
				else pos=a[pos].y;
			} else if(a[pos].op[1]=='l') {
				if(now<a[pos].x) pos=a[pos].y;
				else ++pos;
			} else {
				if(now>a[pos].x) pos=a[pos].y;
				else ++pos;
			}
		}
		if(pos==n+1) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
