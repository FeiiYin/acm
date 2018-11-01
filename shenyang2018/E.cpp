/*************************************************************************
    > File Name: e.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com 
    > Created Time: 2018/11/1 17:47:25
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
const ll INF = 1e18;
const ld eps = 1e-8;
ll qmod(ll a,ll n,ll mod){ll ans=1;while(n){assert(ans>0);if(n&1ll)ans=ans*a%mod;n>>=1;a=a*a%mod;}return ans%mod;}

//head

//your code goes there
 
long long Max1[N<<2][2], Max2[N<<2][2], Min1[N<<2][2], Min2[N<<2][2]; 
int wh1[N<<2][2], wh2[N<<2][2], wh3[N<<2][2], wh4[N<<2][2];
long long x[N], y[N]; int blf[N];
// 0 x轴 1 y轴
void Getit(ll &goalval, int &goalbl, ll val, int bl, int cant, bool flag) {
	if(bl==cant) return;
	if(val>goalval&&flag==1) goalval=val, goalbl=bl;
	if(val<goalval&&flag==0) goalval=val, goalbl=bl;
}
void push_up(int rt) {
	ll a, b, c, d;
	int aa, bb, cc, dd;
	int lson=rt<<1, rson=rt<<1|1;
	// solve x轴 的max
	a=Max1[lson][0],b=Max2[lson][0],c=Max1[rson][0],d=Max2[rson][0];
	aa=wh1[lson][0],bb=wh2[lson][0],cc=wh1[rson][0],dd=wh2[rson][0];
	Max1[rt][0]=-INF,wh1[rt][0]=0;
	Getit(Max1[rt][0], wh1[rt][0], a, aa, 0, 1);
	Getit(Max1[rt][0], wh1[rt][0], c, cc, 0, 1);
	Max2[rt][0]=-INF,wh2[rt][0]=0;
	Getit(Max2[rt][0], wh2[rt][0], a, aa, wh1[rt][0], 1);
	Getit(Max2[rt][0], wh2[rt][0], b, bb, wh1[rt][0], 1);
	Getit(Max2[rt][0], wh2[rt][0], c, cc, wh1[rt][0], 1);
	Getit(Max2[rt][0], wh2[rt][0], d, dd, wh1[rt][0], 1);

	// solve y轴 的max
	a=Max1[lson][1],b=Max2[lson][1],c=Max1[rson][1],d=Max2[rson][1];
	aa=wh1[lson][1],bb=wh2[lson][1],cc=wh1[rson][1],dd=wh2[rson][1];
	Max1[rt][1]=-INF,wh1[rt][1]=0;
	Getit(Max1[rt][1], wh1[rt][1], a, aa, 0, 1);
	Getit(Max1[rt][1], wh1[rt][1], c, cc, 0, 1);
	Max2[rt][1]=-INF,wh2[rt][1]=0;
	Getit(Max2[rt][1], wh2[rt][1], a, aa, wh1[rt][1], 1);
	Getit(Max2[rt][1], wh2[rt][1], b, bb, wh1[rt][1], 1);
	Getit(Max2[rt][1], wh2[rt][1], c, cc, wh1[rt][1], 1);
	Getit(Max2[rt][1], wh2[rt][1], d, dd, wh1[rt][1], 1);

	// solve x轴 的min
	a=Min1[lson][0],b=Min2[lson][0],c=Min1[rson][0],d=Min2[rson][0];
	aa=wh3[lson][0],bb=wh4[lson][0],cc=wh3[rson][0],dd=wh4[rson][0];
	Min1[rt][0]=INF,wh3[rt][0]=0;
	Getit(Min1[rt][0], wh3[rt][0], a, aa, 0, 0);
	Getit(Min1[rt][0], wh3[rt][0], c, cc, 0, 0);
	Min2[rt][0]=INF,wh4[rt][0]=0;
	Getit(Min2[rt][0], wh4[rt][0], a, aa, wh3[rt][0], 0);
	Getit(Min2[rt][0], wh4[rt][0], b, bb, wh3[rt][0], 0);
	Getit(Min2[rt][0], wh4[rt][0], c, cc, wh3[rt][0], 0);
	Getit(Min2[rt][0], wh4[rt][0], d, dd, wh3[rt][0], 0);

	// solve y轴 的min
	a=Min1[lson][1],b=Min2[lson][1],c=Min1[rson][1],d=Min2[rson][1];
	aa=wh3[lson][1],bb=wh4[lson][1],cc=wh3[rson][1],dd=wh4[rson][1];
	Min1[rt][1]=INF,wh3[rt][1]=0;
	Getit(Min1[rt][1], wh3[rt][1], a, aa, 0, 0);
	Getit(Min1[rt][1], wh3[rt][1], c, cc, 0, 0);
	Min2[rt][1]=INF,wh4[rt][1]=0;
	Getit(Min2[rt][1], wh4[rt][1], a, aa, wh3[rt][1], 0);
	Getit(Min2[rt][1], wh4[rt][1], b, bb, wh3[rt][1], 0);
	Getit(Min2[rt][1], wh4[rt][1], c, cc, wh3[rt][1], 0);
	Getit(Min2[rt][1], wh4[rt][1], d, dd, wh3[rt][1], 0);
}
void build(int l, int r, int rt) {
	if(l==r) {
		Max1[rt][0]=Min1[rt][0]=x[l]+y[l];
		Max1[rt][1]=Min1[rt][1]=x[l]-y[l];
		wh1[rt][0]=wh3[rt][0]=blf[l];
		wh1[rt][1]=wh3[rt][1]=blf[l];
		Max2[rt][0]=Min2[rt][0]=x[l]+y[l];
		Max2[rt][1]=Min2[rt][1]=x[l]-y[l];
		wh2[rt][0]=wh4[rt][0]=blf[l];
		wh2[rt][1]=wh4[rt][1]=blf[l];
		return;
	}
	int mid=l+r>>1;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	push_up(rt);
}
void modify(int pos, int dx, int dy, int b, int l, int r, int rt) {
	if(l==r) {
		x[l]+=dx;
		y[l]+=dy;
		blf[l]=b;
		Max1[rt][0]=Min1[rt][0]=x[l]+y[l];
		Max1[rt][1]=Min1[rt][1]=x[l]-y[l];
		wh1[rt][0]=wh3[rt][0]=blf[l];
		wh1[rt][1]=wh3[rt][1]=blf[l];
		Max2[rt][0]=Min2[rt][0]=x[l]+y[l];
		Max2[rt][1]=Min2[rt][1]=x[l]-y[l];
		wh2[rt][0]=wh4[rt][0]=blf[l];
		wh2[rt][1]=wh4[rt][1]=blf[l];
		return;	
	}
	int mid=l+r>>1;
	if(pos<=mid) modify(pos,dx,dy,b,l,mid,rt<<1);
	if(pos>=mid+1) modify(pos,dx,dy,b,mid+1,r,rt<<1|1);
	push_up(rt);
}
pair<pair<ll,int>, pair<ll,int> > querymax(int L, int R, int l, int r, int rt, bool what) {
	if(L==l&&R==r) {
		return make_pair(make_pair(Max1[rt][what],wh1[rt][what]),make_pair(Max2[rt][what],wh2[rt][what]));
	}
	int mid=l+r>>1;
	pair<pair<ll,int>, pair<ll,int> > ans;
	if(R<=mid) {
		ans=querymax(L,R,l,mid,rt<<1,what);
	} else if(L>=mid+1) {
		ans=querymax(L,R,mid+1,r,rt<<1|1,what);
	} else {
		auto res1=querymax(L,mid,l,mid,rt<<1,what);
		auto res2=querymax(mid+1,R,mid+1,r,rt<<1|1,what);
		ll a, b, c, d; int aa, bb, cc, dd;
		a=res1.fi.fi,b=res1.se.fi,c=res2.fi.fi,d=res2.se.fi;
		aa=res1.fi.se,bb=res1.se.se,cc=res2.fi.se,dd=res2.se.se;
		ans.fi.fi=-INF,ans.fi.se=0;
		Getit(ans.fi.fi, ans.fi.se, a, aa, 0, 1);
		Getit(ans.fi.fi, ans.fi.se, c, cc, 0, 1);
		ans.se.fi=-INF,ans.se.se=0;
		Getit(ans.se.fi, ans.se.se, a, aa, ans.fi.se, 1);
		Getit(ans.se.fi, ans.se.se, b, bb, ans.fi.se, 1);
		Getit(ans.se.fi, ans.se.se, c, cc, ans.fi.se, 1);
		Getit(ans.se.fi, ans.se.se, d, dd, ans.fi.se, 1);
	}
	return ans;
}
pair<pair<ll,int>, pair<ll,int> > querymin(int L, int R, int l, int r, int rt, bool what) {
	if(L==l&&R==r) {
		return make_pair(make_pair(Min1[rt][what],wh3[rt][what]), make_pair(Min2[rt][what], wh4[rt][what]));
	}
	int mid=l+r>>1;
	pair<pair<ll,int>, pair<ll,int> > ans;
	if(R<=mid) {
		ans=querymin(L,R,l,mid,rt<<1,what);
	} else if(L>=mid+1) {
		ans=querymin(L,R,mid+1,r,rt<<1|1,what);
	} else {
		auto res1=querymin(L,mid,l,mid,rt<<1,what);
		auto res2=querymin(mid+1,R,mid+1,r,rt<<1|1,what);
		ll a, b, c, d; int aa, bb, cc, dd;
		a=res1.fi.fi,b=res1.se.fi,c=res2.fi.fi,d=res2.se.fi;
		aa=res1.fi.se,bb=res1.se.se,cc=res2.fi.se,dd=res2.se.se;
		ans.fi.fi=INF,ans.fi.se=0;
		Getit(ans.fi.fi, ans.fi.se, a, aa, 0, 0);
		Getit(ans.fi.fi, ans.fi.se, c, cc, 0, 0);
		ans.se.fi=INF,ans.se.se=0;
		Getit(ans.se.fi, ans.se.se, a, aa, ans.fi.se, 0);
		Getit(ans.se.fi, ans.se.se, b, bb, ans.fi.se, 0);
		Getit(ans.se.fi, ans.se.se, c, cc, ans.fi.se, 0);
		Getit(ans.se.fi, ans.se.se, d, dd, ans.fi.se, 0);
	}
	return ans;
}
int main() {
	int T; scanf("%d",&T);
	int cas=1;
	while(T--) {
		int n, q; scanf("%d%d",&n,&q);
		for(int i=1;i<=n;++i) {
			scanf("%lld%lld%d",&x[i],&y[i],&blf[i]);
			p[i].x=x[i],p[i].y=y[i],p[i].blf=blf[i];
		}
		build(1,n,1);
		printf("Case #%d:\n",cas++);
		while(q--) {
			int op, x, y, z; scanf("%d%d%d",&op,&x,&y);
			//cout<<q<<endl;
			ll ans=0;
			if(op==1) {
				scanf("%d",&z);
				modify(x,y,z,blf[x],1,n,1);
			} else if(op==2) {
				modify(x,0,0,y,1,n,1);
			} else {
				auto res1=querymax(x,y,1,n,1,0);
				auto res2=querymin(x,y,1,n,1,0);
				if(res1.fi.se!=res2.fi.se) ans=max(ans,res1.fi.fi-res2.fi.fi);
				else ans=max(ans,res1.fi.fi-res2.se.fi),ans=max(ans,res1.se.fi-res2.fi.fi);
				res1=querymax(x,y,1,n,1,1);
				res2=querymin(x,y,1,n,1,1);
				if(res1.fi.se!=res2.fi.se) ans=max(ans,res1.fi.fi-res2.fi.fi);
				else ans=max(ans,res1.fi.fi-res2.se.fi),ans=max(ans,res1.se.fi-res2.fi.fi);
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
