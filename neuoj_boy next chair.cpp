#include<bits/stdc++.h>
using namespace std;


typedef long long ll ;
const double pi =  acos(-1.0);
const int maxn = 1e6 + 5 ;

namespace fastIO {
    #define BUF_SIZE 100000
    bool IOerror = 0;
    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if(p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if(pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }
    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
    inline void read(int &x) {
        char ch;
        while(blank(ch = nc()));
        if(IOerror)
            return;
        for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
    }
    #undef BUF_SIZE

};

int par[maxn] ;
int find_par(int x){
    if(par[x] == x) return x ;
    return par[x] = find_par(par[x]) ;
}


int operation[maxn][3] ;
int ans[maxn] , pos ;
int main(){
    int kase ;
    fastIO::read(kase) ; // scanf("%d" , &kase) ;
    int m , n , l , r ;
    int tt = 1 ;
    while(kase -- ){
        fastIO::read(n);//scanf("%d" , &n) ;
        memset(par , 0 , sizeof(par)) ;
        int op , top = 0 , bottom = 1e8 ;

        for(int i = 1 ; i <= n ; i ++ ){
            fastIO::read(operation[i][0]);//scanf("%d" , &operation[i][0]) ;
            if(operation[i][0] == 1){
                fastIO::read(operation[i][1]);//scanf("%d" , &operation[i][1]) ;
                m = operation[i][1] ;
                top = max(top , m) ;
                par[m] = m ;
            }else{
                fastIO::read(operation[i][1]);//scanf("%d %d" , &operation[i][1] , &operation[i][2] ) ;
                fastIO::read(operation[i][2]);
                bottom = min(bottom , operation[i][1]) ;
            }
        }
        int max_root ;
        for(int i = top ; i >= bottom ; i -- ){
            if(par[i]){
                max_root = i ;
            }else{
                par[i] = max_root ;
            }
        }

        int root ;
        pos = 0 ;
        printf("Case #%d:\n" , tt ++ ) ;
        for(int i = n ; i >= 1 ; i -- ){
            if(operation[i][0] == 1 ){
                root = operation[i][1] ;
                par[root] = par[root + 1] ;
            }else if(operation[i][0] == 2 ){
                l = operation[i][1] ;
                r = operation[i][2] ;
                m = find_par(l) ;
                if(l <= m && m <= r){
                    ans[pos ++ ] = m  ;
                }else{
                    ans[pos ++ ] = -1 ;
                }
            }
        }
        for(int i = pos - 1 ; i >= 0 ; i -- ){
            printf("%d\n" , ans[i]) ;
        }
    }
    return 0 ;
}

