/*************************************************************************
    > File Name: h.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com 
    > Created Time: 2018/11/17 12:37:28
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

const double eps=1e-10;
const double pi=acos(-1.0);
int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	return x > 0 ? 1 : -1;
}
struct Point {
	double x, y;
	Point () {}
	Point (double _x, double _y) {
		x = _x, y = _y;
	} 
	Point operator - (const Point & b) const {
		return Point (x-b.x, y-b.y);
	}
	Point operator / (const double & b) const {
		return Point(x/b, y/b);
	}
	Point rotate (Point p, double ang) {//绕点p逆时针旋转ang
		Point v = (*this)-p;
		double c = cos (ang), s = sin (ang);
		return Point (p.x + v.x*c - v.y*s, p.y + v.x*s + v.y*c);
	}
};
double cross(Point a, Point b) {
	return a.x*b.y-a.y*b.x;
}
double dot(Point a, Point b) {
	return a.x*b.x+a.y*b.y;
}
double length(Point x) {
	return sqrt(dot(x,x));
}
double rad (Point a, Point b) {//两个向量的夹角
        return fabs (atan2 (fabs (cross (a, b)), dot (a, b)) );
}
struct Line {
	Point s, e;
	double k;
	Line () {}
	Line (Point _s, Point _e) {
		s = _s, e = _e;
		k = atan2(e.y-s.y,e.x-s.x);
	}
};
Point line_intersection (Line a, Line v) {//直线交点
    //调用前确保有交点
    double a1 = cross (v.e-v.s, a.s-v.s);
    double a2 = cross (v.e-v.s, a.e-v.s);
    return Point ((a.s.x*a2-a.e.x*a1)/(a2-a1), (a.s.y*a2-a.e.y*a1)/(a2-a1));
}
int main() {
	Point p[10];
	int T; scanf("%d",&T);
	while(T--) {
		int cas; scanf("%d",&cas);
		for(int i=0;i<3;++i) scanf("%lf%lf",&p[i].x,&p[i].y);
		double ang1=rad(p[2]-p[1],p[0]-p[1]), 
		       ang2=rad(p[1]-p[0],p[2]-p[0]),
		       ang3=rad(p[0]-p[2],p[1]-p[2]); 
		double l=0.0,r=min(ang1,min(ang2,min(ang3,pi/6))),mid;
		Point ans;
		while(r-l>eps) {
			mid=(l+r)/2.0;
			Point newb=p[1].rotate(p[0], mid);
			Point newc=p[2].rotate(p[1], mid);
			Line l1=Line(p[0], newb), l2=Line(p[1], newc);
			Point o = line_intersection(l1, l2);
			Point v1=p[0]-p[2], v2=o-p[2];
			double ang=rad(v1, v2);
			if(dcmp(mid-ang)==1) r=mid;
			else l=mid;
			ans=o;
		}
		printf("%d %.5lf %.5lf\n",cas,ans.x,ans.y);
	}
	return 0;
}
