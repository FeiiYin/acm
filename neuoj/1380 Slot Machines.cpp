/*
 * @Samaritan_infi
 */
/// 题目求 让初始值加上循环节最小
/// 求出 倒序的next数组，（倒着循环部分一样）
/// 然后 只要 倒序的位置 减去 倒序位置的next 数值 即位当前循环的长度
/// 枚举更新

#include<bits/stdc++.h>

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

const int maxn = 1e6 + 5;
int nx[maxn], a[maxn], b[maxn];
void get_next(int a[], int n) {
    int i = 0, j = -1;
    nx[i] = j;
    while(i < n) {
        if(j == -1 || a[i] == a[j])
            i ++, j ++, nx[i] = j;
        else
            j = nx[j];
    }
}

int main() {
    int n = read();
    for(int i = 0; i < n; i ++)
        a[i] = read(), b[n - i - 1] = a[i];
    get_next(b, n);
    int ans = 1e9, pos = 0, k = 0;
    for(int i = 1; i <= n; i ++) {
        int now_pos = (n - i + 1 - nx[n - i + 1]);
        if(i + now_pos < ans ||
           (i + now_pos == ans && now_pos < pos)) {
            ans = i + now_pos;
            k = i - 1;
            pos = now_pos;
        }
        //cout << now_pos << " " << pos << " " << k << endl;
    }
//    for(int i = 0; i < n; i ++) {
//        cout << b[i] << " ";
//    }cout << endl;
//    for(int i = 0; i <= n; i ++) {
//        cout << nx[i] << " ";
//    }cout << endl;
//    int ans = 0x3f3f3f3f, p = 0, k = 0;
//    for(int i = 1; i <= n; i ++){
//        int np = (n - i + 1 - nxt[n - i + 1]);
//        if(i + np < ans || (i + np == ans && np < p)){
//            ans = i + np;
//            k = i - 1; p = np;
//        }
//    }
    printf("%d %d\n", k, pos);
	return 0;
}
