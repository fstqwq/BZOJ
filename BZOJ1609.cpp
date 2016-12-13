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

#define MAXN 30005

int n;
int dp[MAXN][4],a[MAXN];
int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",a+i);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=3;j++) {
			dp[i][j]=0x7fffffff;
			for (int k=1;k<=j;k++) {
				dp[i][j]=min(dp[i-1][k]+(a[i]!=j),dp[i][j]);
			}
		}
	}
	int ans1=min(min(dp[n][1],dp[n][2]),dp[n][3]);
	reverse(a+1,a+n+1);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=3;j++) {
			dp[i][j]=0x7fffffff;
			for (int k=1;k<=j;k++) {
				dp[i][j]=min(dp[i-1][k]+(a[i]!=j),dp[i][j]);
			}
		}
	}
	int ans2=min(min(dp[n][1],dp[n][2]),dp[n][3]);
	printf("%d\n",min(ans1,ans2));
	return 0;
}

