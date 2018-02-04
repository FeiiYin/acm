#include <bits/stdc++.h>
using namespace std;


const int maxn = 101010 ;

int n1 , n2 ;
vector<int> g[maxn] ;
int mx[maxn] , my[maxn] ;
queue<int> que ;
int dx[maxn] , dy[maxn] ;
bool vis[maxn] ;

void init(int n) {
    for(int i = 1 ; i <= n ; i ++ )
        g[i].clear() ;
}
void add(int l , int r){
    g[l].push_back(r) ;
}
bool match(int u){
    for(int i = 0 ; i < g[u].size() ; i ++ ){
        int j = g[u][i] ;
        if(!vis[j] && dy[j] == dx[u] + 1){
            vis[j] = true ;
            if(!my[j] || match(my[j])){
                mx[u] = j ;
                my[j] = u ;
                return true ;
            }
        }
    }
    return false ;
}

int HK(){
    memset(mx , 0 , sizeof(mx)) ;
    memset(my , 0 , sizeof(my)) ;
    int ans = 0 ;
    while(true) {
        bool flag = false ;
        while(!que.empty()) que.pop() ;
        memset(dx , 0 , sizeof(dx)) ;
        memset(dy , 0 , sizeof(dy)) ;
        for(int i = 1 ; i <= n1 ; i ++ )
            if(!mx[i]) que.push(i) ;
        while(!que.empty()){
            int u = que.front() ;
            que.pop() ;
            for(int i = 0 ; i < g[u].size() ; i ++ ){
                int j = g[u][i] ;
                if(!dy[j]){
                    dy[j] = dx[u] + 1 ;
                    if(my[j]){
                        dx[my[j]] = dy[j] + 1 ;
                        que.push(my[j]) ;
                    }else
                        flag = true ;
                }
            }
        }
        if(!flag) break ;
        memset(vis , 0 , sizeof(vis)) ;
        for(int i = 1 ; i <= n1 ; i ++ )
            if(!mx[i] && match(i)) ans ++ ;
    }
    return ans ;
}

const int maxm = 110 ;

bool mp[maxm][maxm] ;

int main(){
    int n , i , j, l , r , m ;
    int kase ;
    scanf("%d" , &kase) ;
    while(kase -- ) {
        scanf("%d %d" , &n , &m) ;

        init(n) ;
        memset(mp , 0 , sizeof(mp)) ;

        for(int i = 0 ; i < m ; i ++){
            scanf("%d %d" , &l , &r) ;
            mp[l][r] = 1 ;
            add(l , r) ;
        }

        for(int k = 1 ; k <= n ; k ++)
            for(int i = 1 ; i <= n ; i ++)
                for(int j = 1 ; j <= n ; j ++)
                    if(mp[i][k] && mp[k][j]){
                        mp[i][j] = 1 ;
                        add(i , j) ;
                    }

        n1 = n2 = n ;

        printf("%d\n" , n - HK()) ;
    }

    return 0 ;
}
