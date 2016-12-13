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
#define MAXN 100005
int n;
char s[MAXN];
int dp[2][4][4][4][4];
int v[4][4][4],cnt[4];
void init() {
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++) 
			for (int k=0;k<4;k++) {
				cnt[1]=cnt[2]=cnt[3]=0;
				cnt[i]++,cnt[j]++,cnt[k]++;
				if (cnt[1]) v[i][j][k]++;
				if (cnt[2]) v[i][j][k]++;
				if (cnt[3]) v[i][j][k]++;
			}
}

int main() {
	scanf("%d",&n);
	scanf("%s",s+1);
	memset(dp[0],200,sizeof(dp[0]));
	dp[0][0][0][0][0]=0;
	init();
	for (int t=1,x,now=1,prev=0;t<=n;t++,now^=1,prev^=1) {
		memset(dp[now],200,sizeof(dp[0]));
		if (s[t]=='M') x=1;
		else if (s[t]=='B') x=2;
		else x=3;
		for (int i=0;i<4;i++)
			for (int j=0;j<4;j++)
				for (int k=0;k<4;k++)
					for (int q=0;q<4;q++) {
						dp[now][x][i][k][q]=max(dp[now][x][i][k][q],dp[prev][i][j][k][q]+v[x][i][j]);
						dp[now][i][j][x][k]=max(dp[now][i][j][x][k],dp[prev][i][j][k][q]+v[x][k][q]);
					}
	}
	int ans=0xc8c8c8c8;
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			for (int k=0;k<4;k++)
				for (int q=0;q<4;q++) 
					ans=max(ans,dp[n&1][i][j][k][q]);
	printf("%d\n",ans);
	return 0;
}

