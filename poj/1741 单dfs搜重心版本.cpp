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


///更新 一遍dfs时，其实只要将当前搜索的根的子树大小传给每一次dfs，因为上一边dfs时已经将它给搜索出来了
///注意一开始的时候初始化，然后用它减去自己的孩子个数，可以求出正确的重心，
///少一边dfs，提速50ms  ， 219ms

///求出当前未被访问的重心
///记住一定要用当前子树的根的size去减，而不是当前结点的父亲，牢记
void dfs_root(int u , int pre , int now_root_son) {
    son[u] = 1 ;
    int u_max_son = 0 ;
    for(int i = 0 ; i < edge[u].size() ; i ++) {
        int v = edge[u][i].u ;
        if(v == pre || vis[v]) continue ;
        dfs_root(v , u , now_root_son) ;
        son[u] += son[v] ;
        u_max_son = max(u_max_son , son[v]) ;
    }

    u_max_son = max(u_max_son , now_root_son - son[u]) ;

    if(u_max_son < root_max_son) {
        root_max_son = u_max_son ;
        root = u ;
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
    dfs_root(x, 0, son[x]);

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
        son[1] = n ; 
        dfs(1) ;
        printf("%d\n" , ans) ;
    }
    return 0 ;
}
