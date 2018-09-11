/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef pair<int, int> P;

int n, m;
map<P, int> counter;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        m = 0; int ans = 0;
        counter.clear();
        for (int i = 0; i < n; i ++) {
            int k; scanf("%d", &k);
            map<P, int> new_counter;
            while (k--) {
                int x, y, t; scanf("%d%d", &x, &y);
                new_counter[{x, y}] = t = counter[{x, y}] + 1;
                ans = max(ans, t);
            }
            counter.swap(new_counter);
        }
        cout << ans << endl;
    }
    return 0;
}
