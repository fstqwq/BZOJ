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
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 105
int n,T;
int vv[105],cc[105];
int dp[40005];

void bp(int v,int w) {
	for (int i=T;i>=v;i--) {
		dp[i]=min(dp[i],dp[i-v]+w);
	}
}

void full_bp(int v) {
	for (int i=T-v;i>=0;i--) {
		dp[i]=min(dp[i],dp[i+v]+1);
	}
}

int main() {
	read(n);read(T);
	T<<=2;
	for (int i=1;i<=n;i++) read(vv[i]);
	for (int i=1;i<=n;i++) read(cc[i]);
	memset(dp,63,sizeof(dp));
	dp[0]=0;
	for (int i=1;i<=n;i++) {
		int now=0;
		for (int j=1;now+j<=cc[i];j<<=1) {
			now+=j;
			bp(vv[i]*j,j);
		}
		if (now!=cc[i]) bp(vv[i]*(cc[i]-now),cc[i]-now);
	}
	for (int i=1;i<=n;i++) {
		full_bp(vv[i]);
	}
	T>>=2;
	if (dp[T]<0x3f3f3f3f) printf("%d\n",dp[T]);
	else printf("-1\n");
	return 0;
}

