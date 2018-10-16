///注意对0很多的矩阵进行矩阵乘法优化
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 500 ;
int out[maxn] ;
int matrix[maxn][maxn] ;

int n ;
void init(){
    int a = n / 4 ;
    for(int i = 1 ; i <= a ; i ++)
        out[i] = 3 * a + i ;
    for(int i = a + 1 ; i <= n ; i ++)
        out[i] = i - a ;
}
void build_matrix(){
    memset(matrix , 0 , sizeof(matrix)) ;
    for(int i = 1 ; i <= n ; i ++)
        matrix[ out[i] ][i] = 1 ;
}
void show_matrix(int a[][maxn]){
    for(int i = 1 ; i <= n ; i ++){
        for(int j = 1 ; j <= n ; j ++)
            cout << a[i][j] << " " ;
        cout << endl ;
    }
}
void change(int l , int r){
    int temp = out[l] ;
    out[l] = out[r] ;
    out[r] = temp ;
}

int c[maxn][maxn] ;
void mul(int a[][maxn] , int b[][maxn]){
    memset(c , 0 , sizeof(c)) ;
    for(int i = 1 ; i <= n ; i ++)
    for(int k = 1 ; k <= n ; k ++)
    if(a[i][k])
    //因为每一列只有一个1，所以需要优化，缺少会超时
    for(int j = 1 ; j <= n ; j ++)
        c[i][j] += a[i][k] * b[k][j] ;

    for(int i = 1 ; i <= n ; i ++){
        for(int j = 1 ; j <= n ; j ++){
            a[i][j] = c[i][j] ;
        }
    }
}

int ans[maxn][maxn] ;
void pow_matrix(int m){
    memset(ans , 0 , sizeof(ans)) ;
    for(int i = 1 ; i <= n ; i ++) ans[i][i] = 1 ;

    while(m){
        if(m & 1) mul(ans , matrix) ;
        mul(matrix , matrix) ;
        m >>= 1 ;
    }
}

int main(){
    int kase ; scanf("%d" , &kase) ;
    int tt = 1 ;
    while(kase --){
        int k , m ;
        scanf("%d %d %d" , &n , &k , &m) ;
        init() ;
        int l , r ;
        while(k --){
            scanf("%d %d" , &l , &r) ;
            change(l , r) ;
        }
        build_matrix() ;

        pow_matrix(m) ;
        //show_matrix(ans) ;
        printf("Case #%d:\n" , tt ++ ) ;
        for(int i = 1 ; i < n ; i ++){
            for(int j = 1 ; j <= n ; j ++){
                if(ans[j][i]){
                    printf("%d " , j) ;
                    break ;
                }
            }
        }
        for(int j = 1 ; j <= n ; j ++){
            if(ans[j][n]){
                printf("%d\n" , j) ;
                break ;
            }
        }
    }
    return 0 ;
}
