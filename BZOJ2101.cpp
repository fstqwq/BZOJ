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
#define MAXN 5005
int n;
int a[MAXN],sum[MAXN],dp[MAXN];

int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		read(a[i]);
		sum[i]=sum[i-1]+a[i];
		dp[i]=a[i];
	}
	for (int len=1;len<n;len++) {
		for (int i=1,j=i+len;j<=n;i++,j++) {
			dp[i]/*[j]*/=sum[j]-sum[i-1]-min(dp[i]/*[j-1]*/,dp[i+1]/*[j]*/);
		}
	}
	printf("%d\n",dp[1]);
	return 0;
}

