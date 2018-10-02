/*************************************************************************
    > File Name: e.cpp
    > Author: BlockChanZJ
    > Mail: 386636627@qq.com 
    > Created Time: 2018/10/2 12:35:08
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <cassert>
#include <iomanip>
using namespace std;

#define rep(i,a,b) for(int i = (a); i <= (b); ++i)
#define per(i,a,b) for(int i = (a); i >= (b); --i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first 
#define se second
#define SZ(x) ((int)(x).size())
#define sqr(x) (x) * (x)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef pair<PII,int> PIII;
const int N = 100005;
const int P = 1000000007;
const ll mod = P;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const ld eps = 1e-8;
ll qmod(ll a,ll n,ll mod){ll ans=1;while(n){assert(ans>0);if(n&1ll)ans=ans*a%mod;n>>=1;a=a*a%mod;}return ans%mod;}

//head

//your code goes there
 
//用于计算多项式相乘
const double PI = 3.14159265358979323846264338327950288L;
struct Complex {
        double x, y;
        Complex(double _x = 0.0, double _y = 0.0) {
                x = _x, y = _y;
        }
        Complex operator - (const Complex &b) const {
                return Complex(x-b.x, y-b.y);
        }
        Complex operator + (const Complex &b) const {
                return Complex(x+b.x, y+b.y);
        }
        Complex operator * (const Complex &b) const {
                return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
        }
};
//FFT和IFFT的反转变换,len为2的幂
void change(Complex y[], int len) {
        int i, j, k;
        for(i = 1, j = len/2; i < len-1; ++i) {
                if(i < j) swap(y[i], y[j]);
                k = len/2;
                while(j >= k) j-=k, k/=2;
                if(j < k) j += k;
        }
}
//len为2的幂, on==1是DFT, on==-1是IDFT
void fft(Complex y[], int len, int on) {
        change(y,len);
        for(int h = 2; h <= len; h <<= 1) {
                Complex wn(cos(-on*2*PI/h), sin(-on*2*PI/h));
                for(int j = 0; j < len; j += h) {
                        Complex w(1,0);
                        for(int k = j; k < j+h/2; ++k) {
                                Complex u = y[k];
                                Complex t = w*y[k+h/2];
                                y[k] = u+t;
                                y[k+h/2] = u-t;
                                w = w*wn;
                        }
                }
        }
        if(on==-1) for(int i = 0; i < len; ++i) y[i].x /= len;
}
const int maxn = 4000005;
char s1[maxn], s2[maxn];
Complex x1[maxn], x2[maxn];
int ans[maxn];
int main() {
        while(scanf("%s",s1)!=EOF) {
		int len=1,l1=strlen(s1),l2;
		for(int i=0;i<l1;++i) s2[i]=s1[i];
		l2=strlen(s2); reverse(s2,s2+l2);
                while(len < l1*2 || len < l2*2) len <<= 1;
		for(int i=0;i<l1;++i) {
			if(s1[i]=='A') x1[i]=Complex(0,0);
			else x1[i]=Complex(1,0);
		}
		for(int i=0;i<l2;++i) {
			if(s2[i]=='A') x2[i]=Complex(1,0);
			else x2[i]=Complex(0,0);
		}
                for(int i = l1; i < len; ++i) x1[i] = Complex(0, 0);
                for(int i = l2; i < len; ++i) x2[i] = Complex(0, 0);
                fft(x1, len, 1);
                fft(x2, len, 1);
                for(int i = 0; i < len; ++i) x1[i] = x1[i]*x2[i];
                fft(x1, len, -1);
                for(int i = 0; i < len; ++i) ans[i] = int(x1[i].x + 0.5);
                //for(int i = 0; i < len; ++i) if(ans[i]>=10) ans[i+1] += ans[i]/10, ans[i]%=10;
                len = l1+l2-1;
                while(ans[len]<=0&&len>0) --len;
		for(int i=l1-2;i>=0;--i) printf("%d\n",ans[i]); printf("\n");
        }
        return 0;
}
