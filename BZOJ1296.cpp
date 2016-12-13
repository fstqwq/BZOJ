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
int n,m,T,sum[55],dp[2505][55],val[2505],pack[2505];
char s[55];
void update() {
	for (int i=T;i>0;i--) {
		for (int j=i-1,ta=max(i-m,0);j>=ta;j--) {
			pack[i]=max(pack[i],pack[j]+val[i-j]);
		}
	}
}
int main() {
	scanf("%d%d%d",&n,&m,&T);
	for (int ca=1;ca<=n;ca++) {
		scanf("%s",s+1);
		for (int i=1;i<=m;i++) sum[i]=sum[i-1]+(s[i]=='1');
		memset(dp,0,sizeof(dp));
		for (int t=1;t<=m;t++) {
			int ret=0;
			for (int i=1;i<=m;i++) {
				dp[t][i]=dp[t-1][i];
				for (int j=0;j<i;j++) {
					dp[t][i]=max(dp[t][i],dp[t-1][j]+max(sum[i]-sum[j],i-j-sum[i]+sum[j]));
				}
				ret=max(ret,dp[t][i]);
			}
			val[t]=ret;
		}
		update();
	}
	int ans=0;
	for (int i=1;i<=T;i++) ans=max(ans,pack[i]);
	printf("%d\n",ans);
	return 0;
}

