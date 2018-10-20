/*
 * @Samaritan_infi
 * 签到
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e6+10;

char s[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n, ans; char c; scanf("%d %c", &n, &c); ans = n;
		scanf("%s", s); ans = n*2;
		int i = 0;
		while(i<n && s[i]==c) {
			++i; ans-=2;
		}
		if(i<n && abs(s[i]-c)<10) --ans;
		printf("%d\n", max(ans, 1));
	}
	return 0;
}
