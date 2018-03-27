/*
 * @Samaritan_infi
 */
///双向bfs，注意每次搜索一层
/// 540 ms
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;
int w, h, n, s[3], t[3];
char dataset[20][20];
int G[200][5], color[200][200][200], dist[200][200][200], redist[200][200][200];
int deg[200];   //记录每个编号为i的空格周围可以走的步数

int dx[] = {0, -1, 1, 0, 0};
int dy[] = {0, 0, 0, -1, 1};

inline int ID(int a, int b, int c) {    //对状态进行编码
    return (a << 16) | (b << 8) | c;
}

inline bool conflict(int a, int b, int a2, int b2) {
    return ((a2 == b2) || (a == b2 && b == a2));
}

int bfs() {
    queue<int> qf;  //记录正向bfs
    queue<int> qb;  //记录反向bfs

    dist[s[0]][s[1]][s[2]] = 0;
    dist[t[0]][t[1]][t[2]] = 1; //分别记录正反两种遍历走了多少步数

    qf.push(ID(s[0], s[1], s[2]));
    qb.push(ID(t[0], t[1], t[2]));  //起点终点分别压入队列

    color[s[0]][s[1]][s[2]] = 1;
    color[t[0]][t[1]][t[2]] = 2;    //分别标注正反两种遍历已经走过的

    while(!qf.empty() || !qb.empty()) {
        int fnum = qf.size(), bnum = qb.size();
        while(fnum--) {
            int u = qf.front(); qf.pop();
            int a = (u >> 16) & 0xff, b = (u >> 8) & 0xff, c = u & 0xff;

            for(int i = 0; i < deg[a]; i++) {
                int a2 = G[a][i];
                for(int j = 0; j < deg[b]; j++) {
                    int b2 = G[b][j];
                    if(conflict(a, b, a2, b2))  continue;

                    for(int k = 0; k < deg[c]; k++) {
                        int c2 = G[c][k];
                        if(conflict(a, c, a2, c2) || conflict(b, c, b2, c2))    continue;

                        if(color[a2][b2][c2] == 0) {
                            dist[a2][b2][c2] = dist[a][b][c] + 1;
                            color[a2][b2][c2] = 1;
                            qf.push(ID(a2, b2, c2));
                        }
                        else if(color[a2][b2][c2] == 2) {
                            return dist[a][b][c] + dist[a2][b2][c2];
                        }
                    }
                }
            }
        }

        while(bnum--) {
            int u = qb.front(); qb.pop();
            int a = (u >> 16) & 0xff, b = (u >> 8) & 0xff, c = u & 0xff;

            for(int i = 0; i < deg[a]; i++) {
                int a2 = G[a][i];
                for(int j = 0; j < deg[b]; j++) {
                    int b2 = G[b][j];
                    if(conflict(a, b, a2, b2))  continue;

                    for(int k = 0; k < deg[c]; k++) {
                        int c2 = G[c][k];
                        if(conflict(a, c, a2, c2) || conflict(b, c, b2, c2))    continue;

                        if(color[a2][b2][c2] == 0) {
                            dist[a2][b2][c2] = dist[a][b][c] + 1;
                            color[a2][b2][c2] = 2;
                            qb.push(ID(a2, b2, c2));
                        }
                        else if(color[a2][b2][c2] == 1) {
                            return dist[a][b][c] + dist[a2][b2][c2];
                        }
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    //freopen("input.txt", "r", stdin);
    while(~scanf("%d%d%d\n", &w, &h, &n) && n) {
        for(int i = 0; i < h; i++)  gets(dataset[i]); //fgets(dataset[i], 20, stdin);   //此处不能用scanf来处理输入，会TLE

        int cnt = 0, x[200], y[200], id[20][20];    //从图中抽取出空间并求出初始状态和目标状态
        for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++) {
            if(dataset[i][j] != '#') {
                x[cnt] = i; y[cnt] = j; id[i][j] = cnt;
                if(islower(dataset[i][j]))  s[dataset[i][j] - 'a'] = cnt;       //初始状态
                else if(isupper(dataset[i][j])) t[dataset[i][j] - 'A'] = cnt;   //目标状态
                cnt++;  //注意这里的cnt++不能偷懒在上面一行末尾，因为这样有时候cnt++会没有执行
            }
        }


        for(int i = 0; i < cnt; i++) {  //利用空格建立图
            deg[i] = 0;
            for(int j = 0; j < 5; j++) {
                int nx = x[i] + dx[j];  int ny = y[i] + dy[j];
                if(dataset[nx][ny] != '#')  G[i][deg[i]++] = id[nx][ny];
            }
        }

        if(n <= 2)  { deg[cnt] = 1; G[cnt][0] = cnt; s[2] = t[2] = cnt++; }
        if(n <= 1)  { deg[cnt] = 1; G[cnt][0] = cnt; s[1] = t[1] = cnt++; }

        memset(dist, 0, sizeof(dist));
        memset(color, 0, sizeof(color));

        if(s[0] == t[0] && s[1] == t[1] && s[2] == t[2])    printf("0\n");
        else    printf("%d\n", bfs());
    }
    return 0;
}
