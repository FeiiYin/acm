O(n)

int __max__ (int a[],int n) {
    int sum = 0, maxsum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
        if (sum > maxsum) maxsum = sum;
        else if (sum < 0) sum = 0;
    }
    return maxsum;
}


把矩阵投影到行，相当于求N*(N+1)/2个最大子段和的最大值
一维 dp， 另一维暴力枚举 O(n3)

for (i = 1; i <= m; i++) for (j = 1; j <= n; j++)
    rowsum[i][j] = rowsum[i][j-1] + matrix[i][j];
for (first = 1; first <= n; first++) for (last = first; last <= n; last++) {
      area=0;
      for (i = 1; i <= m; i++) {
            area += rowsum[i][last] -rowsum[i][first-1];
            if (area > ans) ans = area;
            if (area < 0) area = 0;
       }
}

