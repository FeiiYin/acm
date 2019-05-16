/**
 * @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 2e5 + 5;
const int M = 1e6 + 5;

int arr[N];

int main() {
	int n;
	while (~ scanf("%d", &n)) {
        for (int i = 0; i < n; ++i)
            scanf("%d", &arr[i]);

        int l = 0, r = 0, tmp_l = 0, tmp_r = 0;
        for (int i = 0; i < n; ++i) {
            /// plus
            tmp_l = r + arr[i];
            /// minus
            tmp_r = l - arr[i];
            l = max(l, tmp_l);
            r = max(r, tmp_r);
        }
        printf("%d\n", max(l, r));
	}
	return 0;
}
