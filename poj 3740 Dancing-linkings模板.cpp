#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
//X是点数，N是行数，M是列数
const int X = 100000 + 10, N = 20 + 10, M = 300 + 10, INF = 0x3f3f3f3f;

struct DLX
{
    int U[X], D[X], L[X], R[X], row[X], col[X];
    int H[N], S[M];
    int head, sz, tot, n, m, ans[N];
    void init(int _n, int _m)
    {
        n = _n, m = _m;
        for(int i = 0; i <= m; i++) //初始化列头
            L[i] = i-1, R[i] = i+1, U[i] = D[i] = i, S[i] = 0;
        head = 0, tot = 0, sz = m;
        L[head] = m, R[m] = head;
        for(int i = 1; i <= n; i++) H[i] = -1; //初始化行头
    }
    void link(int r, int c) /*插入一个新点，注意插入的位置和此点在原矩阵中的位置是上下左右都颠倒的，
    但是通过row和col数组记录了点在原矩阵中的位置，所以没有关系*/
    {
        ++S[col[++sz]=c];
        row[sz] = r;
        D[sz] = D[c], U[D[c]] = sz;
        U[sz] = c, D[c] = sz;
        if(H[r] < 0) H[r] = L[sz] = R[sz] = sz;
        else R[sz] = R[H[r]], L[R[H[r]]] = sz, L[sz] = H[r], R[H[r]] = sz;
    }
    void del(int c) //删除在某一列出现1元素的所有行
    {
        L[R[c]] = L[c], R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i])
            for(int j = R[i]; j != i; j = R[j])
                D[U[j]] = D[j], U[D[j]] = U[j], --S[col[j]];
    }
    void recover(int c) //删除的逆过程，注意次序和删除正好一反，但其实次序无所谓，和删除一样也可以
    {
        for(int i = U[c]; i != c; i = U[i])
            for(int j = L[i]; j != i; j = L[j])
                D[U[j]] = U[D[j]] = j, ++S[col[j]];
        R[L[c]] = L[R[c]] = c;
    }
    bool dance(int dep) //核心部分，其实就是dfs
    {
        if(R[head] == head)
        {
            tot = dep-1; return true;
        }
        int c = R[head];
        for(int i = R[head]; i != head; i = R[i])//选取出现1元素次数最少的一列进行删除
            if(S[i] < S[c]) c = i;
        del(c);
        for(int i = D[c]; i != c; i = D[i])
        {
            ans[dep] = row[i];
            for(int j = R[i]; j != i; j = R[j]) del(col[j]);
            if(dance(dep + 1)) return true;
            for(int j = L[i]; j != i; j = L[j]) recover(col[j]);
        }
        recover(c);
        return false;
    }
}dlx;
int main()
{
    int n, m;
    while(~ scanf("%d%d", &n, &m))
    {
        dlx.init(n, m);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
            {
                int val;
                scanf("%d", &val);
                if(val == 1) dlx.link(i, j);
            }
        puts(dlx.dance(1) ? "Yes, I found it" : "It is impossible");
    }
    return 0;
}
