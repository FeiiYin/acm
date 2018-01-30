#include <bits/stdc++.h>
using namespace std;

///最大独立机
///二分图 HK算法

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
const int maxm = 310 ;
char read[maxm] ;
bool pic[maxm][maxm] ;
int address[maxm][maxm] ;
int ddx[] = {-2 , -2 , -1 , -1 , 1 ,  1 , 2 ,  2 } ;
int ddy[] = { 1 , -1 ,  2 , -2 , 2 , -2 , 1 , -1 } ;


char a[maxm][maxm] ;
int main(){
    int n , i , j , sum1 , sum2 , l , r;
    int kase ; int tt = 1 ;
    scanf("%d" , &kase) ;
    while(kase -- ) {
        scanf("%d" , &n) ;
        sum1 = sum2 = 0 ;
        for(int i = 0 ; i < n ; i ++ ){
            scanf("%s" , a[i]) ;
        }
        for(int i = 0 ; i < n ; i ++ ){
            for(int j = 0 ; j < n ; j ++ ){
                if(a[i][j] == '.'){
                    if((i + j) % 2 == 0) address[i][j] = ++ sum1 ;
                    else address[i][j] = ++ sum2 ;
                }
            }
        }
        init(sum1 + 12) ;
        for(int i = 0 ; i < n ; i ++ ){
            for(int j = 0 ; j < n ; j ++ ){
                if((i + j) % 2 == 0)
                if(a[i][j] == '.')
                for(int k = 0 ; k < 8 ; k ++ ){
                    l = i + ddx[k] ;
                    r = j + ddy[k] ;
                    if(l >= 0 && l < n && r >= 0 && r < n)
                    if(a[l][r] == '.')
                    add(address[i][j] , address[l][r]) ;
                }
            }
        }
        n1 = sum1 ;
        n2 = sum2 ;
        printf("Case #%d: %d\n" , tt ++ , n1 + n2 - HK()) ;
    }

    return 0 ;
}
