/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 20015 ;
const int maxm = 121111 ;
const int inf = 0x3f3f3f3f;

struct node{int v, w, next;} edge[maxm];
int no, head[maxn];

int t, n, m;
int deg[maxn], val[maxn];
queue<int> q;
void init()
{
	no = 0;
	memset(head, -1, sizeof head);
	memset(deg, 0, sizeof deg);
	memset(val, 0, sizeof val);
}
inline void add(int u, int v, int w)
{
	edge[no].v = v; edge[no].w = w;
	edge[no].next = head[u]; head[u] = no++;
}
int topsort()
{
	while(!q.empty()) q.pop();
	for(int i = 1; i <= n; ++i)
	if(! deg[i]) q.push(i);
	int ans = 0;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for(int k = head[u]; k + 1; k = edge[k].next)
		{
			int v = edge[k].v;
			val[v] = max(val[v], edge[k].w+val[u]);
			if(--deg[v] == 0) q.push(v);
		}
	}
	int aaa = 0 ;
	for(int i = 1 ; i <= n ; i ++) {
        aaa = max(val[i] , aaa) ;
	}
	return aaa + 1 ;
	//printf("%d\n", *max_element(val+1, val+n+1) + 1);
}
int main()
{
    int kase ; scanf("%d" , &kase) ;
	while(kase --) {
		scanf("%d %d", &n, &m); init();
		for(int i = 1; i <= m; ++i)
		{
			int u, v, w;
			scanf("%d %d", &u, &v);
			add(u + 1 , v + 1 , 1); ++deg[v + 1];
		}
		int ans = topsort();
		printf("%d\n" , ans) ;
	}
	return 0;
}
