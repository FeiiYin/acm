#include <bits/stdc++.h>

using namespace std ;
typedef long long ll;

///note
///һ��ʼ����������ģ� ���Ǽ���������dp[][]�ģ�����wa
///��Ϊ�������ܱ�֤������ȷ
///����ʱ �� ����Ӯ��״̬����������ѵ��ܶ��������ֻҪ��һ��״̬����Ӯ�ˣ���ô���״̬һ����Ӯ
///�ܺõ�һ����Ŀ
///@Samaritan_infi

const int mod = 4e6 ;
const int maxn = 105 ;

vector< pair<int , int> > edge[maxn] ;

int dp[maxn][maxn][30][4] ;
pair<int , int> temp ;
bool dfs(int a , int b , int val , int turn ){
    if(dp[a][b][val][turn] != -1) return dp[a][b][val][turn] ;
    if(!turn){ /// a turn 0
        for(int i = 0 ; i < edge[a].size() ; i ++){
            temp = edge[a][i] ;
            if(temp.second >= val && dfs(temp.first , b , temp.second , 1) == false)
                return dp[a][b][val][turn] = false ;
        }
        return dp[a][b][val][turn] = true ;
    }
    /// b turn 1
    for(int i = 0 ; i < edge[b].size() ; i ++){
        temp = edge[b][i] ;
        if(temp.second >= val && dfs(a , temp.first , temp.second , 0) == true)
            return dp[a][b][val][turn] = true ;
    }
    return dp[a][b][val][turn] = false ;
}


int main(){
    int n , m ;
    int l , r , v ;
    char val[3] ;
    memset(dp , -1 , sizeof(dp)) ;
    scanf("%d %d" , &n , &m) ;
    for(int i = 0 ; i < m ; i ++){
        scanf("%d %d %s" , &l , &r , val) ;
        v = val[0] - 'a' ;
        edge[l].push_back(make_pair(r , v)) ;
    }

    for(int i = 1 ; i <= n ; i ++) dp[i][i][0][0] = true ;

    for(int i = 1 ; i <= n ; i ++ ){
        for(int j = 1 ; j <= n ; j ++ ){
            if(dfs(i , j , 0 , 0) == true) putchar('B') ;
            else putchar('A') ;
        }
        puts("") ;
    }
    return 0 ;
}
