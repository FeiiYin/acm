///注意课只能从每一天的两边消去，所以需要dp
///先暴力处理出f[i][j]  第i天在消去j节课的最少时间
///然后分组dp  dp[i] 表示消去i节课时，最少的时间
///dp[i] = min(dp[i] , dp[i - t] - len[day] + f[day][t])
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 505 ;
const int inf = 0x3f3f3f3f ;
char read[maxn] ;

int num[maxn] ;
int len[maxn] ;
int pos[maxn][maxn] ;

int f[maxn][maxn] ;
int dp[maxn] ;

void init(){
    memset(num , 0 , sizeof(num)) ;
    memset(f , 0 , sizeof(f)) ;
    memset(dp , inf , sizeof(dp)) ;
}

void show(int a[][maxn]){
    for(int i = 0 ; i < 5 ; i ++){
        for(int j = 0 ; j < 5 ; j ++){
            cout << a[i][j] << " " ;
        }cout << endl;
    }
}
int main(){

    int n , m , k ;
    while(~ scanf("%d %d %d" , &n , &m , &k) ){
        init() ;
        int lesson = 0 ;
        for(int i = 0 ; i < n;  i ++){
            scanf("%s" , read) ;

            for(int j = 0 ; j < m ; j ++){
                if(read[j] == '1'){
                    pos[i][ ++ num[i] ] = j ; ///从1开始
                }
            }
            len[i] = pos[i][ num[i] ] - pos[i][1] + 1 ;
            lesson += len[i] ;
        }

        for(int i = 0 ; i < n ; i ++){
            for(int j = 0 ; j <= min(num[i] , k) ; j ++){
                int temp = inf , l , r;
                for(l = 0 ; l <= j ; l ++){
                    r = j - l ;
                    temp = min(temp , pos[i][ num[i] - r ] - pos[i][l + 1] + 1) ;
                }
                f[i][j] = temp ;
            }
            f[i][num[i]] = 0 ;
        }
        //show(f) ;
        ///分组背包
        dp[0] = lesson ;
        for(int i = 0 ; i < n ; i ++) {
            for(int j = k ; j >= 0 ; j --) { ///注意这里从大到小，防止该组自己更新的数据被自己使用
                for(int t = 0 ; t <= j ; t ++)
                    dp[j] = min(dp[j] , dp[j - t] - len[i] + f[i][t]) ;
            }
        }
        //for(int i = 0 ; i <= k ; i ++)  cout << dp[i] << " " ; cout << endl ;
        printf("%d\n" , dp[k]) ;
    }
    return 0 ;
}
