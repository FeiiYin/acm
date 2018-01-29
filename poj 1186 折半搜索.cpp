//#include <bits/stdc++.h>
#include <map>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std ;
typedef long long ll;

const int maxn = 5e6 + 5 ;
const int mod = 4e6 ;

int k[10] , p[10] ;
map<int , int> pq ;
///map will time exceed

int mid ;

int hash_table[maxn][2] ;
bool hash_vis[maxn] ;

int search_hash(int val){
    ///int index = (val + mod) % mod ; this is wrong , because it may < - 2 * mod ;
    int index = val ;
    while(index < 0 ) index += mod ;
    while(index >= mod) index -= mod ;

    while(hash_vis[index] == true){
        if(hash_table[index][0] == val) break ;
        index = (index + 1) % mod ;
    }
    return index ;
}

void insert_hash(int val){
    int index = search_hash(val) ;
    hash_vis[index] = true ;
    hash_table[index][0] = val ;
    hash_table[index][1] ++ ;
}

int quick_pow(int x , int n){
    int ans = 1 ;
    int base = x ;
    while(n){
        if(n & 1) ans *= base ;
        base *= base ;
        n >>= 1 ;
    }
    return ans ;
}

int n , m ;
void dfs(int deep , int val){
    if(deep > mid){
        insert_hash(val) ;
        return ;
    }
    for(int i = 1 ; i <= m ; i ++ ){
        int temp_val = val + k[deep] * quick_pow(i , p[deep]) ;
        dfs(deep + 1 , temp_val) ;
    }
}
int ans ;
void dfs_ans(int deep , int val){
    if(deep > n){
        int index = search_hash(- val) ;
        ans += hash_table[index][1] ;
        return ;
    }
    for(int i = 1 ; i <= m ; i ++ ){
        int temp_val = val + k[deep] * quick_pow(i , p[deep]) ;
        dfs_ans(deep + 1 , temp_val) ;
    }
}

int main()
{
    while( ~ scanf("%d %d" , &n , &m)){
        for(int i = 1 ; i <= n ; i ++ ){
            scanf("%d %d" , &k[i] , &p[i]) ;
        }
        memset(hash_table , 0 , sizeof(hash_table)) ;
        memset(hash_vis , 0 , sizeof(hash_vis)) ;

        mid = n >> 1 ;
        dfs(1 , 0) ;
        //for(auto it = pq.begin() ; it != pq.end() ; it ++ )
        //    cout << it->first  << " " << it->second << endl ;
        ans = 0 ;
        dfs_ans(mid + 1 , 0) ;
        printf("%d\n" , ans) ;
    }
    return 0 ;
}
