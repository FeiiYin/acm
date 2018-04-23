/*
 * @Samaritan_infi
 */
/// 由于璐是固定的，所以将对应的璐数i和原来长度转成店，最后要求的是截距最短的，求出凸包，然后离线计算一下
/// 武神好强
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

const int maxn = 1e5 + 5;
int dis_1[maxn];
int dis[maxn];

struct point{
    int x, y;
    point() {}
    point(int a, int b) {x = a, y = b;}
    friend point operator - (const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
};//p[maxn];
vector<point> temp;

//ll check(int i, int j, int k) {
//    //i j < j k
//    ll a = (ll)(p[i].y - p[j].y) * (p[j].x - temp[k].x);
//    ll b = (ll)(p[j].y - temp[k].y) * (p[i].x - p[j].x);
//    return a < b;
//}

pair<int, int> query[maxn];
ll ans[maxn];

/// 凸包
const double eps = 1e-8;
int cmp(double x) {
    if(fabs(x) < eps) return 0;
    if(x > 0) return 1;
    return -1;
}

double det(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
}
struct polygon_convex {
    vector<point> P;
    polygon_convex(int Size = 0) {P.resize(Size);}
};

bool comp_less(const point &a, const point &b) {
    return cmp(a.x-b.x)<0 || cmp(a.x-b.x)==0 && cmp(a.y-b.y)<0;
}

polygon_convex convex_hull(vector<point> a) {
    polygon_convex res(2 * a.size() + 5);
    sort(a.begin(), a.end(), comp_less);
    int m = 0;
    for(int i = 0; i < a.size(); i ++) {
        while(m > 1 && cmp(det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-2]))<=0) --m;
        res.P[m ++] = a[i];
    }
    int k = m;
    for(int i = int(a.size())-2; i >= 0; i --) {
        while(m>k && cmp(det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-2]))<=0) --m;
        res.P[m ++] = a[i];
    }
    res.P.resize(m);
    if(a.size() > 1) res.P.resize(m - 1);
    return res;
}


int main() {
    int kase = read();
    while(kase --) {
        int n = read(), m = read();
        for(int i = 2; i <= n; i ++) dis_1[i] = read();
        dis[n] = 0;
        for(int i = 2; i <= n - 1; i ++) dis[i] = read();

        for(int i = n - 1; i >= 2; i --) dis[i] += dis[i + 1];
        temp.clear();
        temp.resize(n - 1);
        for(int i = n; i >= 2; i --) {
            dis[i] += dis_1[i];
            temp[n - i] = point(n + 1 - i, dis[i]);
        }

 //for(int i = 2; i <= n; i ++) cout << dis[i] << " "; cout << endl;
//        cout << "test:" << endl;
//        for(int i = 1; i <= n - 1; i ++) cout << temp[i].x << " " << temp[i].y << endl;
//        cout << "test:" << endl;
        polygon_convex p = convex_hull(temp);
//        for(int i = 0; i < p.P.size(); i ++) {
//            cout << p.P[i].x << " " << p.P[i].y << endl;
//        }
//
//        p[0] = temp[1];
//        p[1] = temp[2];
//        int head = 0, tail = 2;
//        for(int i = 3; i <= n - 1; i ++) {
//            while(head + 1 < tail && check(tail - 2, tail - 1, i))
//                tail --;
//            p[tail ++] = temp[i];
//        }
//        for(int i = head; i < tail; i ++) {
//            cout << p[i].x << " " << p[i].y << endl;
//        }
        for(int i = 1; i <= m; i ++) query[i] = make_pair(read(), i);
        sort(query + 1, query + 1 + m);
        //for(int i = 1; i <= m; i ++) cout << query[i].first << " "; cout << endl;
        int pos = p.P.size() - 1;
        for(int i = 1; i <= m; i ++) {
            int d = query[i].first;
            if(pos == 0) {
                ans[ query[i].second ] = (ll)(p.P[pos].x * d) + p.P[pos].y;
            } else {
                while(pos > 0) {
                    ll a = (ll)(p.P[pos].x * d) + p.P[pos].y;
                    ll b = (ll)(p.P[pos - 1].x * d) + p.P[pos - 1].y;
                    if(a < b) break;
                    else pos --;
                }
//                cout << d << endl;
//                cout << pos << endl;
                ans[ query[i].second ] = (ll)(p.P[pos].x * d) + p.P[pos].y;
//                cout << ans[ query[i].second ] << endl;
            }
        }
        printf("%lld", ans[1]);
        for(int i = 2; i <= m; i ++) printf(" %lld", ans[i]);
        puts("");
    }
    return 0;
}
/*
1
6 5
3 4 7 10 100
10 24 4 69
*/
