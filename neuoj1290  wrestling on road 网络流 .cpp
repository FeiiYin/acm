#include<bits/stdc++.h>
using namespace std;


typedef long long ll ;
//注意由于跑过一遍最大流之后，每个结点里的flow和cap都会改变，所以简单的删边是不行的，好吧，我花了两个小时才发现这个道理。。。。。。。

//用#define type xxx替代流的类型(int, double, long long)
//极其关键：边数开两倍
#define type int
const int maxn = 4005 ;
const int maxm = 40105 ;
const int INF = 0x3f3f3f3f ;
int n;
int s, t;
struct Edge {
    int from, to, next;
    type cap, flow;
    void get (int u, int a, int b, type c, type d) {
        from = u; to = a; next = b; cap = c; flow = d;
    }
}edge[maxm];
int tol;
int head[maxn];
int gap[maxn], dep[maxn], pre[maxn], cur[maxn];
void init () {
    tol = 0;
    memset (head, -1, sizeof head);
}

void add_edge (int u, int v, type w, type rw=0) {
    //cout << u << " " << v << " " << w << endl;
    edge[tol].get(u, v,head[u],w,0);head[u]=tol++;
    edge[tol].get(v, u,head[v],rw,0);head[v]=tol++;
}
void delete_node(){
    int from = edge[-- tol].from ;
    //int to = edge[tol].to ;
    head[from] = edge[tol].next ;
}

type sap (int start, int end, int N) {
    memset (gap, 0, sizeof gap);
    memset (dep, 0, sizeof dep);
    memcpy (cur, head, sizeof head);
    int u = start;
    pre[u] = -1;
    gap[0] = N;
    type ans = 0;
    while (dep[start] < N) {
        if (u == end) {
            type Min = INF;
            for (int i = pre[u]; i != -1; i = pre[edge[i^1].to])
                if (Min > edge[i].cap - edge[i].flow)
                   Min = edge[i].cap-edge[i].flow;
            for (int i = pre[u]; i != -1; i = pre[edge[i^1].to]) {
                edge[i].flow += Min;
                edge[i^1].flow -= Min;
            }
            u = start;
            ans += Min;
            continue;
        }
        bool flag = false;
        int v;
        for (int i = cur[u]; i != -1; i = edge[i].next) {
            v = edge[i].to;
            if (edge[i].cap - edge[i].flow && dep[v]+1 == dep[u]) {
                flag = true;
                cur[u] = pre[v] = i;
                break;
            }
        }
        if (flag) {
            u = v;
            continue;
        }
        int Min = N;
        for (int i = head[u]; i != -1; i = edge[i].next)
            if (edge[i].cap - edge[i].flow && dep[edge[i].to] < Min) {
	              Min = dep[edge[i].to];
	              cur[u] = i;
	         }
        gap[dep[u]]--;
        if (!gap[dep[u]]) return ans;
        dep[u] = Min+1;
        gap[dep[u]]++;
        if (u != start) u = edge[pre[u]^1].to;
    }
    return ans;
}

vector<pair<int , int> > temp ;
int main(){
    int kase ;
    scanf("%d" , &kase) ;
    int l , r , m ;
    int tt = 1 ;
    while(kase -- ){
        scanf("%d %d" , &n , &m) ;

        init() ;
        for(int i = 0 ; i < m ; i ++ ){
            scanf("%d %d" , &l , &r) ;
            add_edge(l , r , 1) ;
            add_edge(r , l , 1) ;
            temp.push_back(make_pair(l , r)) ;
        }
        s = n + 1 ;
        t = n + 2 ;


        add_edge(s , 1 , 1) ; add_edge(s , 2 , 1) ;
        add_edge(n-1 , t , 1) ;add_edge(n , t , 1) ;
        int ans = sap(s , t , n + 2) ;

        printf("Case #%d: " , tt ++ ) ;
        if(ans < 2){
            puts("Van is in a dilemma!") ;
            continue ;
        }

        //cout << "ans : " << ans << endl ;
        for(int i = 0 ; i < tol - 8 ; i ++ ){
            if(i % 2){
                edge[i].cap = edge[i].flow = 0 ;
            }else{
                edge[i].cap = 1 ;
                edge[i].flow = 0 ;
            }
        }

        for(int i = 1 ; i <= 8 ; i ++ ){
            delete_node() ;
        }
        /*init() ;
        for(int i = 0 ; i < temp.size() ; i ++ ){
            l = temp[i].first ; r = temp[i].second ;
            add_edge(l , r , 1) ;
            add_edge(r , l , 1) ;
        }*/
        add_edge(s , 1 , 1) ; add_edge(s , n - 1 , 1) ;
        add_edge(n , t , 1) ; add_edge(2 , t , 1) ;
        ans = sap(s , t , n + 2) ;
        //cout << "ans :" << ans << endl ;
        if(ans < 2){
            puts("Van is in a dilemma!") ;
            continue ;
        }
        puts("Banana and kazuya won't be angry!") ;
    }

    return 0 ;
}
/*
1
4 3
1 4
2 4
4 3
*/
