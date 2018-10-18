/*
 * @Samaritan_infi
 */


//#include<bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;

const int maxn = 10005;
bool isprime[maxn];
int prime[maxn], prime_size;
void init(int tot) {
    memset(isprime, 1, sizeof isprime);
    isprime[1] = 0;
    prime_size = 0;
    for(int i = 2; i <= tot; i ++) {
        if(isprime[i]) prime[++ prime_size] = i;
        for(int j = 1; j <= prime_size && prime[j] * i <= tot; j ++) {
            isprime[ prime[j] * i ] = false;
            if(i % prime[j] == 0) break;
        }
    }
}
void into_arr(int num, int a[]) {
    int i = 3;
    while(num) {
        a[i --] = num % 10;
        num /= 10;
    }
}
int into_num(int a[]) {
    return a[0] * 1000 + a[1] * 100 + a[2] * 10 + a[3];
}

bool vis[maxn];
int ans;
int finish;


void bfs(int x) {
    int arr[5];

    queue< pair<int, int> > pq;
    vis[x] = true;
    pq.push(make_pair(x, 0));
    while(! pq.empty()) {
        pair<int, int> node = pq.front(); pq.pop();
        x = node.first;
        int deep = node.second;
        if(x == finish){ans = deep; break; }
        into_arr(x, arr);
        for(int i = 0; i < 4; i ++) {
            int down = (i == 0) ? 1 : 0;
            int pre = arr[i];
            for(int j = down; j <= 9; j ++) {
                if(j == pre) continue;
                arr[i] = j;
                int now = into_num(arr);
                if(vis[now] || ! isprime[now]) continue;
                vis[now] = true;
                pq.push(make_pair(now, deep + 1));
            }
            arr[i] = pre;
        }
    }

    return;
}

int main() {
    init(10000);
    int kase; scanf("%d", &kase);
    int a, b;
    while(kase --) {
        scanf("%d %d", &a, &b);
        finish = b;
        ans = 1e9;
        memset(vis, 0, sizeof vis);
        bfs(a);
        cout << ans << endl;
    }
    return 0;
}
