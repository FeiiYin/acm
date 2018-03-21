/*
 * @Samaritan_infi
 */
/// 这个是re版本 ，等我改了再说
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll ;

template <class T>
inline void scan(T &ret) {
    char c ;
    ret = 0 ;
    while((c = getchar()) < '0' || c > '9') ;
    while(c >= '0' && c <= '9') {
        ret = ret * 10 + c - '0' , c = getchar() ;
    }
}

const int maxn = 10005 ;
vector< pair<int , int> > edge[maxn] ;
vector<int> temp_dis ;
int son[maxn] ; /// 孩子个数
bool vis[maxn] ;/// 是否作为根结点过
int root , root_max_son ;
int n , k ;

///求出当前未被访问的重心
void dfs_root(int x , int par) {
    int max_son_x = 0 ;
    for(int i = 0 ; i < edge[x].size() ; i ++) {
        int u = edge[x][i].first ;
        if(u == par || vis[u]) continue ;
        dfs_root(u , x) ;
        son[x] += 1 + son[u] ;
        max_son_x = max(max_son_x , 1 + son[u]) ;
    }
    max_son_x = max(max_son_x , n - 1 - son[x]) ;
    if(max_son_x < root_max_son) {
        root = x ; root_max_son = max_son_x ;
    }
}

void dfs_dis(int x , int par , int dis) {
    temp_dis.push_back(dis) ;
    for(int i = 0 ; i < edge[x].size() ; i ++) {
        int u = edge[x][i].first ;
        if(u == par || vis[u]) continue ;
        dfs_dis(u , x , dis + edge[x][i].second) ;
    }
}

int cal(int x , int d) {
    temp_dis.clear() ;
    dfs_dis(x , 0 , d) ;
    //cout << "start:  " ;for(int i = 0 ; i < temp_dis.size() ; i ++) cout << temp_dis[i] << " "  ; cout << endl ;
    sort(temp_dis.begin() , temp_dis.end()) ;
    int l = 0 , r = temp_dis.size() - 1 ;
    int ans = 0 ;
    while( l < r ) {
        while(l < r && temp_dis[l] + temp_dis[r] > k) r -- ;
        ans += r - l ;
        l ++ ;
    }
    return ans ;
}

int ans ;
void dfs(int u) {
    root_max_son = n ;
    dfs_root(u , 0) ;
    vis[root] = true ;
    int now_root = root ;
    ans += cal(now_root , 0) ;

    for(int i = 0 ; i < edge[now_root].size() ; i ++) {
        int u = edge[now_root][i].first ;
        if(vis[u]) continue ;
        ans -= cal(u , edge[now_root][i].second) ;
    }
    for(int i = 0 ; i < edge[now_root].size() ; i ++) {
        int u = edge[now_root][i].first ;
        if(vis[u]) continue ;
        dfs(u) ;
    }
}


void init() {
    for(int i = 1 ; i <= n ; i ++) edge[i].clear() ;
    memset(son , 0 , sizeof son) ;
    memset(vis , false , sizeof vis) ;
    ans = 0 ;
}

int main() {
    while(~ scanf("%d %d" , &n , &k)) {
        if(n == 0 && k == 0) break ;
        int a , b , v ;
        init() ;
        for(int i = 1 ; i < n ; i ++) {
            scanf("%d %d %d" , &a , &b , &v) ;
            //scan(a) ; scan(b) ; scan(v) ;
            edge[a].push_back( make_pair(b , v) ) ;
            edge[b].push_back( make_pair(a , v) ) ;
        }
        dfs(1) ;
        printf("%d\n" , ans) ;
    }
    return 0 ;
}
