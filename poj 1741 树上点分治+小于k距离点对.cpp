/*
 * @Samaritan_infi
 */

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

struct node {
    int u , v ;
};

const int maxn = 1e4 + 5 ;
vector< node > edge[maxn] ;
vector<int> temp_dis ;
int son[maxn] ; /// 孩子个数含自己
int sz[maxn] ; 
bool vis[maxn] ;/// 是否作为根结点过
int root , root_max_son ;
int n , k ;




///求出当前未被访问的重心
///不能一遍求dfs，因为这样搜索，搜索到子树的时候，另一块的大小还没搜出来，
///所以这样这一句
///             u_max_son = max(u_max_son , son[now_root] - son[u]) ;
///这样一减就不能求出真实的最大值，也就不能求出真实的重心，也就可能退化，也就t了
/*
///求出当前未被访问的重心
///记住一定要用当前子树的根的size去减，而不是当前结点的父亲，牢记
void dfs_root(int u , int pre , int now_root) {
    son[u] = 1 ;
    int u_max_son = 0 ;
    for(int i = 0 ; i < edge[u].size() ; i ++) {
        int v = edge[u][i].u ;
        if(v == pre || vis[v]) continue ;
        dfs_root(v , u , now_root) ;
        son[u] += son[v] ;
        u_max_son = max(u_max_son , son[v]) ;
    }

    u_max_son = max(u_max_son , son[now_root] - son[u]) ;

    if(u_max_son < root_max_son) {
        root_max_son = u_max_son ;
        root = u ;
    }
}
*/
 /// 找出以u为根的子树的重心 ， 双dfs
void dfs_size(int u , int pre) {     
    son[u] = 1 ; sz[u] = 0 ;

    for (int i = 0; i < edge[u].size() ; i ++) {
        int v = edge[u][i].u ;
        if (v == pre || vis[v]) continue ;
        dfs_size(v , u) ;
        son[u] += son[v] ;
        sz[u] = max(sz[u], son[v]);
    }
}

void dfs_root(int u , int pre , int now_root) { 
    sz[u] = max(sz[u], sz[now_root] - sz[u]);
    
    if (root_max_son > sz[u]) {
        root_max_son = sz[u] ; 
        root = u;
    }

    for (int i = 0 ; i < edge[u].size() ; i ++) {
        int v = edge[u][i].u;
        if (v == pre || vis[v]) continue;
        dfs_root(v , u , now_root);
    }
}


void dfs_dis(int u , int pre , int d) {
    temp_dis.push_back(d) ;
    for(int i = 0 ; i < edge[u].size() ; i ++) {
        int v = edge[u][i].u ;
        if(vis[v] || v == pre) continue ;
        dfs_dis(v , u , d + edge[u][i].v) ;
    }
}

int cal(int x , int d) {
    temp_dis.clear() ;
    dfs_dis(x , 0 , d) ;
    sort(temp_dis.begin() , temp_dis.end()) ;
    int l = 0 , r = temp_dis.size() - 1;
    int res = 0 ;
    while(l < r) {
        while(l < r && temp_dis[l] + temp_dis[r] > k) r -- ;
        res += r - l ;
        l ++ ;
    }
    return res ;
}

int ans ;

void dfs(int x) {
    root_max_son = n ;
    dfs_size(x, 0) ; dfs_root(x, 0, x);

    x = root ; vis[x] = true ;
    //cout << x << endl ;
    ans += cal(x , 0) ;
    for(int i = 0 ; i < edge[x].size() ; i ++) {
        int v = edge[x][i].u ;
        if(vis[v]) continue ;
        ans -= cal(v , edge[x][i].v) ;
        dfs(v) ;
    }
}

void init(int n) {
    for(int i = 1 ; i <= n ; i ++) edge[i].clear() ;
    memset(vis , 0 , sizeof vis) ;
    ans = 0 ;
    son[0] = n ;
}

int main() {
    while( ~ scanf("%d %d" , &n , &k)) {
        if(n == 0 && k == 0) break ;
        init(n) ;
        int a , b , v ;
        for(int i = 1 ; i < n ; i ++) {
            scan(a) ;
            scan(b) ;
            scan(v) ;
            edge[a].push_back( (node){b , v} ) ;
            edge[b].push_back( (node){a , v} ) ;
        }
        dfs(1) ;
        printf("%d\n" , ans) ;
    }
    return 0 ;
}
