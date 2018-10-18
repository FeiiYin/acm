/*
 * @Samaritan_infi
 */
/// 一般图最大独立集 == 补图的最大团， 求点 用回溯
//#include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

const int maxn = 110, maxm = 3e4 + 5;
const int inf = 2147483640;

bool pic[maxn][maxn];
int dp[maxn]; /// i to n 最大团的结点数
int clique_size;
int que[maxn][maxn];
int n;
bool ans[maxn];
bool vis[maxn];

void dfs(int pos, int deep) {
    if(! pos) {
        if(deep > clique_size) {
            clique_size = deep;
            memcpy(ans, vis, sizeof vis);
            /// memcpy(ans, vis, sizeof (int)*(n+1)) 会wa，不要用
//            memset(ans, 0, sizeof ans);
//            for(int i = 1; i <= n; i ++)
//                if(vis[i]) ans[i] = true;
        }
//        for(int i = 0; i <= n; i ++) {
//            for(int j = 0; j <= n; j ++)
//                cout << que[i][j]<< " ";
//            cout << endl;
//        }
        return;
    }
    for(int i = 0; i < pos; i ++) {
        int k = que[deep][i];
        if(deep + n + 1 - k <= clique_size) return;
        if(deep + dp[k] <= clique_size) return;

        int cnt = 0;
        vis[k] = true;
        for(int j = i + 1; j < pos; j ++)
            if(pic[k][ que[deep][j] ])
                que[deep + 1][cnt ++] = que[deep][j];
        dfs(cnt, deep + 1);
        vis[k] = false;
    }
}

void work() {
    clique_size = 1;
    dp[n] = 1;
    for(int i = n - 1; i >= 1; i --) {
        int pos = 0;
        for(int j = i + 1; j <= n; j ++)
            if(pic[i][j]) que[1][pos ++] = j;
        vis[i] = true;
        dfs(pos, 1);
        vis[i] = false;
        dp[i] = clique_size;
    }
}

int main() {
    int kase = read();
    while(kase --) {
        n = read();
        int m = read();
        memset(pic, true, sizeof pic);
        memset(vis, false, sizeof vis);
        for(int i = 1; i <= n; i ++) pic[i][i] = false;
        int l, r;
        while(m --) {
            l = read(), r = read();
            pic[l][r] = pic[r][l] = false;
        }
        work();
        printf("%d\n", clique_size);

        for(int i = 1; i <= n; i ++)
            if(ans[i]) printf("%d ", i);
        puts("");
    }
    return 0;
}
