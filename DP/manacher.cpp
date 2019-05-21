/**
 * @Samaritan
 */
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
typedef long long LL;

const int N = 1e5 + 5;
const int M = 1e4 + 5;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;


int kmp_next[N];
void work_next (int a[], int n) {
    int i = 0, j = -1;
    kmp_next[0] = -1;
    while (i < n) {
        if (j == -1 || a[i] == a[j])
            i++, j++, kmp_next[i] = j;
        else
            j = kmp_next[j];
    }
    cout << "next: ";
    for (int i = 0; i <= n; ++i)
        cout << kmp_next[i] << " ";
    cout <<endl;
}
int kmp[N];
void work_kmp (int a[], int b[], int n, int m) {
    int i = 0, j = 0;
    work_next(b, m);
    while (i < n) {
        if (j == -1 || a[i] == b[j])
            i++, j++, kmp[i] = j;
        else
            j = kmp_next[j];
    }
    cout << "kmp: ";
    for (int i = 0; i <= n; ++i)
        cout << kmp[i] << " ";
    cout << endl;
}

char now[N << 1];
int p[N << 1];
int manacher (char a[], int n) {
    for (int i = 0; i < n; ++i) {
        now[2*i + 1] = '#';
        now[2*i + 2] = a[i];
    }
    int len;
    now[len = n*2+1] = '#';
    int R = 0, pos = 0;
    for (int i = 1; i <= len; ++i) {
        if (i < R) {
            p[i] = min(R - i, p[ 2*pos - i ]);
        } else {
            p[i] = 1;
        }
        while (i - p[i] >= 1 && i + p[i] <= len && now[i + p[i]] == now[i - p[i]])
            p[i]++;
        if (i + p[i] > R) {
            R = i + p[i];
            pos = i;
        }
    }
    int ans = 0;
    for (int i = 1; i < len; ++i)
        ans = max(ans, p[i] - 1);
    return ans;
}

int arr[N], brr[N];
char crr[N];
int main () {
    while (~ scanf("%s", crr)) {
        printf("%d\n", manacher(crr, strlen(crr)));
    }

    int n, m;
    while (~ scanf("%d %d", &n, &m)) {
        for (int i = 0; i < n; ++i)
            scanf("%d", &arr[i]);
        for (int i = 0; i < m; ++i)
            scanf("%d", &brr[i]);

        work_kmp(arr, brr, n, m);
    }
    return 0;
}
