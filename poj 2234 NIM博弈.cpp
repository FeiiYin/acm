/*
 * @Samaritan_infi
 */
/// NIM博弈  当面对抑或和为0的时候是必败局面
//#include<bits/stdc++.h>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

template <class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

inline ll read() {
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int main() {
    int n;
    while(~ scanf("%d", &n)) {
        ll x, ans = 0;
        while(n --) {
            x = read();
            ans ^= x;
        }
        if(! ans)   puts("No");
        else        puts("Yes");
    }
    return 0;
}
