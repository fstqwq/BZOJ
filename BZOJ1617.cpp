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
#define MAXN 2505

int n,m,t[MAXN],dp[MAXN];

int main() {
	read(n);read(m);
	t[0]=m*2;
	for (int i=1;i<=n;i++) {
		read(t[i]);
		t[i]+=t[i-1];
	}
	memset(dp,31,sizeof(dp));
	dp[0]=0;
	for (int i=1;i<n;i++) {
		for (int j=0;j<=i;j++) {
			dp[i]=min(dp[i],dp[j]+t[i-j]);
		}
	}
	for (int i=0;i<=n;i++) {
		dp[n]=min(dp[n],dp[i]+t[n-i]);
	}
	printf("%d\n",dp[n]-m);
	return 0;
}

