/*************************************************************************
    > File Name: d.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com 
    > Created Time: 2018/11/18 12:11:41
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
ll qmod(ll a,ll n,ll mod){ll ans=1;while(n){assert(ans>0);if(n&1ll)ans=ans*a%mod;n>>=1;a=a*a%mod;}return ans%mod;}

//head

//your code goes there


double XL, XR, YL, YR, ZL, ZR;
double eps=1e-3;
int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
struct Point {
	double x, y, z;
	Point () {}
	Point (double _x, double _y, double _z) {
		x = _x, y = _y, z = _z;
	}
};
double dist(Point a, Point b) {
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)+sqr(a.z-b.z));
}
double Mindist;
int n;
Point p[105];
inline double check(Point c) {
	double Maxd=0;
	rep(i,1,n) Maxd=max(Maxd,dist(c,p[i]));
	return Maxd;
}
inline double checkz(double x, double y) {
	double l=ZL, r=ZR, mid, mmid;
	double Mind=1e9;
	while(r-l>eps) {
		mid=(l+r)/2.0, mmid=(mid+r)/2.0;
		double ans1=check(Point(x,y,mid)), ans2=check(Point(x,y,mmid));
		Mind=min(Mind,ans1), Mind=min(Mind,ans2);
		if(dcmp(ans1-ans2)<=0) r=mmid;
		else l=mid;	
	}
	return Mind;
}
inline double checky(double x) {
	double l=YL, r=YR, mid, mmid;
	double Mind=1e9;
	while(r-l>eps) {
		mid=(l+r)/2.0,  mmid=(mid+r)/2.0;
		double ans1=checkz(x,mid), ans2=checkz(x,mmid);
		Mind=min(Mind,ans1), Mind=min(Mind,ans2);
		if(dcmp(ans1-ans2)<=0) r=mmid;
		else l=mid;
	}
	return Mind;
}
void makedata() {
	srand(time(0));
	cout<<100<<endl;
	cout<<100000<<" "<<100000<<" "<<100000<<endl;
	cout<<-100000<<" "<<100000<<" "<<100000<<endl;
	for(int i=1;i<=98;++i) {
		ll x=rand()*rand()%100000;
		ll y=rand()*rand()%100000;
		ll z=rand()*rand()%100000;
		if(rand()&1) x=-x;
		if(rand()&1) y=-y;
		if(rand()&1) z=-z;
		cout<<x<<" "<<y<<" "<<z<<endl;
	}
}
int main() {
	//freopen("in","w",stdout);
	//makedata();
	//time_t t1 = clock();
	XL=YL=ZL=100000.0, XR=YR=ZR=-100000.0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].z);
	rep(i,1,n) {
		XL=min(p[i].x,XL);
		YL=min(p[i].y,YL);
		ZL=min(p[i].z,ZL);
		XR=max(p[i].x,XR);
		YR=max(p[i].y,YR);
		ZR=max(p[i].z,ZR);
	}
	if(XL==XR) XL--,XR++;
	if(YL==YR) YL--,YR++;
	if(ZL==ZR) ZL--,ZR++;
	/*
	cout<<XL<<" "<<XR<<endl;
	cout<<YL<<" "<<YR<<endl;
	cout<<ZL<<" "<<ZR<<endl;
	*/
	Mindist=1e9;
	double l=XL,r=XR, mid, mmid;
	while(r-l>eps) {
		mid=(l+r)/2.0, mmid=(mid+r)/2.0;
		double ans1=checky(mid), ans2=checky(mmid);
		Mindist=min(Mindist,ans1), Mindist=min(Mindist,ans2);
		if(dcmp(ans1-ans2)<=0) r=mmid;
		else l=mid;
	}
	printf("%.10lf\n",Mindist);
	//cout<<setprecision(15)<<Mindist<<endl;
	//time_t t2 = clock();
	//cerr<<t2-t1<<"ms"<<endl;
	return 0;
}
