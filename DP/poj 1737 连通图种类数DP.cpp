/**
h[i] full set
f[i] connected set
g[i] not connected set

clearly h[i] = f[i] + g[i] = 2^{C_n^2}
g[i] = \sum_{k = 1}^{i - 1}{C_{n - 1}^{k - 1} * f[k] * h[i - k]}
f[i] = h[i] - g[i]
ans = f[n]
*/

import java.math.*;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        BigInteger h[]=new BigInteger [55],C[][]=new BigInteger[55][55];
        C[0][0]=BigInteger.ONE;
        for(int i=0;i<=50;i++){//预处理组合数
            C[i][0]=C[i][i]=BigInteger.ONE;
            for(int j=1;j<i;j++){
                C[i][j]=C[i-1][j].add(C[i-1][j-1]);
            }
        }
        for(int i=1;i<=50;i++) h[i]=BigInteger.valueOf(2).pow(i*(i-1)/2);
        BigInteger f[]=new BigInteger[55],g[]=new BigInteger[55];
        f[1]=BigInteger.ONE;
        for(int i=1;i<=50;i++) {
            g[i]=BigInteger.ZERO;
            for(int j=1;j<i;j++) {
                g[i]=g[i].add(C[i-1][j-1].multiply(f[j]).multiply(h[i-j]));
            }
            f[i]=h[i].subtract(g[i]);
        }
        Scanner in=new Scanner(System.in);
        while(in.hasNext()){
            int n=in.nextInt();
            if(n==0) break;
            System.out.println(f[n]);
        }
    }

}
