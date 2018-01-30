#include <bits/stdc++.h>
using namespace std;

///贪心 从两边双搜  (?(? 左边4 右边0 ， 即成立
const int maxn = 5050 ;
char read[maxn] ;

int mark[maxn][maxn] ;
int main(){
    scanf("%s" , read) ;
    memset(mark , 0 , sizeof(mark)) ;
    int len = strlen(read) ;
    for(int i = 0 ; i < strlen(read) ; i ++ ){
        int temp = 0 ;
        for(int j = i ; j < strlen(read) ; j ++ ){
            if(read[j] == '(' || read[j] == '?') temp ++ ;
            else temp -- ;
            if(temp >= 0) mark[i][j] ++ ;
            else break ;
        }
    }

    for(int i = strlen(read) - 1 ; i >= 0 ; i --){
        int temp = 0 ;
        for(int j = i ; j >= 0 ; j -- ){
            if(read[j] == ')' || read[j] == '?') temp ++ ;
            else temp -- ;
            if(temp >= 0) mark[j][i] ++ ;
            else break ;
        }
    }
    int ans = 0 ;
    for(int i = 0 ; i < strlen(read) ; i ++ ){
        for(int j = i ; j < strlen(read) ; j ++ ){
            if((i + j) % 2 && mark[i][j] == 2) ans ++ ;
        }
    }
    printf("%d\n" , ans) ;
    return 0 ;
}
