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


int main() {
    int kase = read();
    while(kase --) {
        int n = read(), ans = 0, flag = 1, x;
        for(int i = 1; i <= n; i ++) {
            x = read();
            if(x != 1) flag = 0;
            ans ^= x;
        }
        if(flag) {
            if(n & 1) puts("Brother");
            else    puts("John");
        } else {
            /// SG[x] = x  函数抑或和为0 
            if(! ans) puts("Brother");
            else puts("John");
        }
    }
    return 0;
}
