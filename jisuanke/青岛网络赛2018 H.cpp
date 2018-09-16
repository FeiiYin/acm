  /*************************************************************************
    > File Name: h.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com 
    > Created Time: 2018年09月16日 12:54:13
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
 
char s[100005];
bool cango(int time, char c) {
	return (time+c-'0')%2==1;
}
int f[100005], st[100005];
ll pre[100005];
int main() {
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%s",s+1);
		int n = strlen(s+1);
		int pos=0,time=0;
		while(pos<n) {
			if(cango(time,s[pos+1])) ++time,st[++pos]=time%2, f[pos]=time;
			else ++time;
		}
		//rep(i,1,n) cout<<f[i]<<" ";cout<<endl;
		ll ans = 0;
		rep(i,1,n) pre[i]=pre[i-1]+f[i];
		rep(i,0,n-1) {
			ll past = f[i];
			ll add;
			if(st[i]==0) add=pre[n]-pre[i];
			else if(st[i]==s[i+1]-'0') add=pre[n]-pre[i]-(n-i);
			else add=pre[n]-pre[i]+(n-i);
			/*
			if(st[i]==0) cout << "status same\n";
			else cout << "status not same\n";
			cout << "past : " << past << "  add : " << add << " ?? : " << pre[n]-pre[i] << endl;
			*/
			ans+=add-past*(n-i);
		}
		cout<<ans<<endl;
	}
	return 0;
}
