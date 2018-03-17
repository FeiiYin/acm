/*
 * @Samaritan_infi
 */
 ///这里的树的所有边权值为1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int mod = 15498 ;

const int maxn = 100005 ;
const int inf = 0x3f3f3f3f ;
vector<int> edge[maxn] ;
int d[maxn] ;
bool vis[maxn] ;
void init(int n) {

    memset(vis , 0 , sizeof (vis)) ;
    memset(d , inf , sizeof d) ;
    //d[1] = 0 ;
}

void dfs(int u) {
    vis[u] = 1 ;
    //cout << u << endl ;
    for(int i = 0 ; i < edge[u].size() ; i ++) {
        int v = edge[u][i] ;
        if(! vis[v]) {
            d[v] = d[u] + 1 ;
            dfs(v) ;
        }
    }
}
void show(int n) {
    for(int i = 1 ; i <= n ; i ++) cout << d[i] << " " ;cout << endl ;

}

int main() {
    //int kase ; scanf("%d" , &kase) ;
    int n ;
    while ( ~ scanf("%d" , &n)) {
        init(n) ;
        for(int i = 1 ; i<= n ; i ++) edge[i].clear() ;
        int l , r ;
        for(int i = 1 ; i < n ; i ++) {
            scanf("%d %d" , &l , &r) ;
            edge[l].push_back(r) ;
            edge[r].push_back(l) ;
        }
        d[1] = 0 ;
        dfs(1) ;
        int start = 1 ;
        int num = -1 ;
        //show(n) ;
        for(int i = 1 ; i <= n ; i ++) {
            if(d[i] > num && d[i] != inf) {
                num = d[i] ;
                start = i ;
            }
        }

        init(n) ;
        d[start] = 0 ;
        dfs(start) ;
        //show(n) ;
        int ans = 0 ;
        int flag = false ;

        for(int i = 1 ; i <= n ; i ++) {
            if(d[i] > ans && d[i] != inf) {
                ans = d[i] ;
                flag = false ;
                start = i ;
            } else if(d[i] == ans) {
                flag = true ;
            }
        }
        if(flag) {
            printf("%d\n" , ans) ;
            continue ;
        }

        init(n) ;
        d[start] = 0 ;
        dfs(start) ;

        ans = 0 ;
        flag = false ;

        for(int i = 1 ; i <= n ; i ++) {
            if(d[i] > ans && d[i] != inf) {
                ans = d[i] ;
                flag = false ;
                //start = i ;
            } else if(d[i] == ans) {
                flag = true ;
            }
        }
        if(flag) {
            printf("%d\n" , ans) ;
        }
        else
        printf("%d\n" , ans - 1 ) ;
    }
    return 0 ;
}
/*
5
1 2
1 5
4 5
5 3
*/
