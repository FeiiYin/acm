#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5 ;

char read[maxn] ;

vector<int> edge[maxn] ;
int deg[maxn] ;

int ans[maxn][26] ;
queue<int> pq ;

int main(){
    int n , m , k ;
    scanf("%d %d" , &n , &m) ;
    scanf("%s" , read + 1) ;

    int a , b ;
    bool flag = false ;
    for(int i = 0 ; i < m ; i ++){
        scanf("%d %d" , &a , &b) ;
        if(a == b) flag = true ;
        edge[a].push_back(b) ;
        deg[b] ++ ;
    }
    if(flag == true) {puts("-1") ; return 0 ;}

    for(int i = 1 ; i <= n ; i ++ ){
        if(!deg[i]) pq.push(i) ;
    }
    int out = 0 ;
    int cnt = 0 ;

    while(!pq.empty()){
        int u = pq.front() ;
        cnt ++ ;
        pq.pop() ;
        ans[u][ read[u] - 'a' ] ++ ;
        out = max(out , ans[u][read[u] - 'a']) ;
        for(int num : edge[u]){
            for(int i = 0 ; i < 26 ; i ++ ){
                ans[num][i] = max(ans[u][i] , ans[num][i]);
            }
            deg[num] -- ;
            if(!deg[num])   pq.push(num) ;
        }
    }

    if(cnt < n) out = -1 ;
    printf("%d\n" , out) ;

    return 0 ;
}

///原来用的搜索，会超时
/*

int dfs(int st , int arr[]){
    int ans = 0 ;
    if(vis[st]) return -1 ;
    vis[st] = 1 ;
    arr[ read[st] - 'a' ] ++ ;

    for(auto k = edge[st].begin() ; k != edge[st].end() ; k ++ ){
        //int num : edge[st] ){
        int num = *k ;
        int temp = dfs(num , arr) ;
        if(temp == -1){
            return -1 ;
        }else{
            ans = max(temp , ans) ;
        }
    }

    vis[st] = 0 ;
    arr[ read[st] - 'a' ] -- ;
    if(ans) return ans ;
    arr[ read[st] - 'a' ] ++ ;
    for(int i = 0 ; i < 26 ; i ++ ){
        //cout << arr[i] ;
        ans = max(ans , arr[i]) ;
    }//cout << "    "<< st  << endl ;
    arr[ read[st] - 'a' ] -- ;
    return ans ;
}*/
