/**
 * @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e5 + 5;
//int arr[N];

/// 横坐标 x， 纵坐标 y， 边长 k， 位置 id
void work (int &x, int &y, int k, int id) {
    if (k == 1) {
        x = y = 1;
        return;
    }
    int unit = (k * k) >> 2, next_k = k >> 1;
    if (id <= unit) {
        work (x, y, next_k, id);
        swap(x, y);
    }
    else if (id <= (unit << 1)) {
        work (x, y, next_k, id - unit);
        y += next_k;
    }
    else if (id <= (unit * 3)) {
        work (x, y, next_k, id - (unit << 1));
        x += next_k;
        y += next_k;
    }
    else {
        work (x, y, next_k, id - (unit * 3));
        int pre = x;
        x = k + 1 - y;
        y = next_k + 1 - pre;
    }
}

int main(){
    int k, id, x, y;
    while (~ scanf("%d %d", &k, &id)) {
        work(x, y, k, id);
        printf("%d %d\n", x, y);
    }
    return 0;
}
