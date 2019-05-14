round1 problem2
一个全正数组，被完全分成m段，使最大段的和最小，求最小值
二分答案

round1 problem3
一个可负数组，被完全分成m段，使最大段的和最小，求最小值
DP，dp[i][j] = for (k from 1 to i - 1) min( max(dp[k][j-1], sum(k+1 to i)) )

round2 problem
每个石块会不断扩撒，求起点能否到终点
预处理出每一个空地最早被扩散到的时间，dfs即可


round3 problem1
一个数组有多少个区间能被m整除：O(n)

[1, 2, 3], m = 3

arr[n], int, m 

int work (int *arr, int len, int m) {
	unordered_map<int, int> mp;
  int pre = 0, ans = 0;
  for (int i = 0; i < len; ++i) {
  	pre += arr[i];
    pre = (pre % m + m) % m;
    ans += mp[pre];
    mp[pre]++;
  }
  return ans;
}


round3 problem2
原串1e5，问1e5个查询中，每一个是否子串在原串中出现
倒叙建图，构造字典树

n char arr[], 1e5, dic m 1e5, < 10, 

"abcdefg"
 
 ["ae", "df", "ge"]


const int N = 1e5 + 5;
int tree[26][N];
void work (char *arr, int n, char **brr, int *len, int m) {
  int cur[26];
  memset (cur, -1, sizeof cur);
  
  for (int i = n-1; i >= 0; --i) {
    for (int j = 0; j < 26; ++j) 
      tree[j][i] = cur[j];
    
    cur[ arr[i] - 'a' ] = i;
  }
  
  for (int i = 0; i < 26; ++i)
    tree[i][n] = cur[i];
  
  for (int kase = 0; kase < m; ++kase) {
  	int l = len[kase];
    
    bool flag = true;
    int now_cur = n;
    
    for (int i = 0; i < l; ++i) {
    	int ch = brr[kase][i];
      
      if (tree[ch][now_cur] == -1) {
      	flag = false;
        break;
      }
      
      now_cur = tree[ch][now_cur];
    }
    if (flag) printf("YES");
    else printf("NO");
  }
}
