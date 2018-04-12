/*
 * @Samaritan_infi
 */
/// NIM博弈  当面对抑或和为0的时候是必败局面
/// 题目链接 http://hzwer.com/2746.html
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

template <class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int maxn = 1005;
int stone[20];
int pick[20];
int sg[maxn];
bool vis[maxn];
///1.可选步数为1~m的连续整数，直接取模即可，SG(x) = x % (m+1);
///2.可选步数为任意步，SG(x) = x;
///3.可选步数为一系列不连续的数，用GetSG()计算

///如果SG[ stone[i] ] 抑或和为0 为必败状态
///求第一步 暴力枚举
void cal_sg(int n, int m) {
    for(int i = 1; i <= 1000; i ++) {
        memset(vis, 0, sizeof vis);
        for(int j = 1; j <= m; j ++)
            if(i - pick[j] >= 0) vis[ sg[i - pick[j] ] ] = 1;
        for(int j = 0; j <= 10; j ++)
            if(! vis[j]) {
                sg[i] = j;
                break;
            }
    }
}


int main() {
    int n = read();
    for(int i = 1; i <= n; i ++) stone[i] = read();
    int m = read();
    for(int i = 1; i <= m; i ++) pick[i] = read();
    cal_sg(n, m);
    int ans = 0;
    for(int i = 1; i <= n; i ++) ans ^= sg[ stone[i] ];
    if(! ans) puts("NO");
    else {
        for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m && pick[j] <= stone[i]; j ++)
        if((ans ^ sg[ stone[i] ] ^ sg[ stone[i] - pick[j] ]) == 0) {
            puts("YES");
            printf("%d %d", i, pick[j]);
            return 0;
        }
    }
    return 0;
}
