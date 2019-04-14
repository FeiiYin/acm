/**
`* @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define PII pair<int, int>
#define mp make_pair
#define pb push_back
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
#define fi  first
#define se second

const int N = 1e4 + 5;
const int M = 10;
LL dp[N];
LL pr[M]; int pos[M];
void humble (int n) {
    int m = 4;
    pr[0] = 2; pr[1] = 3; pr[2] = 5; pr[3] = 7;
    dp[1] = 1;
    fill(pos, pos + m, 1);
    int tmp = 0;
    for (int i = 2; i <= n; ++i) {
        dp[i] = INF_LL;
        for (int j = 0; j < m; ++j)
            dp[i] = min(dp[i], pr[j] * dp[ pos[j] ]);
        for (int j = 0; j < m; ++j)
            if (pr[j] * dp[ pos[j] ] == dp[i])
                pos[j]++;
    }
}

int main () {
    humble(10000);
    int n; while (~ scanf("%d", &n)) {
        if (! n) break;
        printf("The %d", n);
        if (n % 100 != 11 && n % 10 == 1){
			printf("st");
		}else if (n % 100 != 12 && n % 10 == 2){
			printf("nd");
		}else if (n % 100 != 13 && n % 10 == 3){
			printf("rd");
		}else{
			printf("th");
		}
		printf(" humble number is %d.\n", dp[n]);
    }
    return 0;
}
