/*	Never stop fighting for what you believe in.	*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;


#define MOD 1000000007
#define MAXN 1000000
typedef long long LL;

int T,n,m;
int fac[MAXN+5],invfac[MAXN+5],dp[MAXN+5];

int quickpower(long long a,int x) {
	long long ret=1;
	while (x) {
		if (x&1) ret=(ret*a)%MOD;
		a=(a*a)%MOD;
		x>>=1;
	}
	return ret;
}

int inv(int x) {
	return quickpower(x,MOD-2);
}

void init() {
	fac[0]=1;
	for (int i=1;i<=MAXN;i++) fac[i]=(LL(fac[i-1])*i)%MOD;
	invfac[MAXN]=inv(fac[MAXN]);
	for (int i=MAXN-1;i>-1;i--) invfac[i]=(LL(invfac[i+1])*(i+1))%MOD;
	dp[0]=1,dp[1]=0;
	for (int i=2;i<=MAXN;i++) {
		dp[i]=(1-((i&1)<<1)+dp[i-1]*LL(i)+MOD)%MOD;
	}
}

int main() {
	init();
	scanf("%d",&T);
	while (T--) {
		scanf("%d%d",&n,&m);
		printf("%d\n",LL(fac[n])*invfac[n-m]%MOD*invfac[m]%MOD*dp[n-m]%MOD);
	}
	return 0;
}

