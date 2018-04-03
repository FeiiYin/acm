/*
 * @Samaritan_infi
 */
//#include<bits/stdc++.h>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;

const int maxn = 200000 + 5;
int block;
int read[maxn];
int to[maxn];
int step[maxn];

int query(int pos) {
    int ans = 0;
    while(~ pos) {
        ans += step[pos];
        pos = to[pos];
    }
    return ans;
}
int n;
void update(int pos, int val) {
    int start = pos / block * block;
    int last = (pos / block + 1) * block - 1;
    read[pos] = val;
    for(int i = pos; i >= start; -- i) {
        if(i + read[i] >= n) {
            to[i] = -1;
            step[i] = 1;
        } else if(i + read[i] > last) {
            to[i] = i + read[i];
            step[i] = 1;
        } else {
            to[i] = to[ i + read[i] ];
            step[i] = step[i + read[i]] + 1;
        }
    }
}

int main() {
    scanf("%d", &n);
    block = (int) sqrt(n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &read[i]);
    for(int i = n - 1; ~ i; i --) {
        /// this block
        int last = (i / block + 1)* block - 1;
        if(i + read[i] >= n) {
            to[i] = -1;
            step[i] = 1;
        } else if(i + read[i] > last) {
            to[i] = i + read[i];
            step[i] = 1;
        } else {
            to[i] = to[ i + read[i] ];
            step[i] = step[i + read[i]] + 1;
        }
    }
    int operation; scanf("%d", &operation);
    int a, b, op;
    while(operation --) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d", &a);
            printf("%d\n", query(a));
        } else {
            scanf("%d %d", &a, &b);
            update(a, b);
        }
    }
    return 0;
}
