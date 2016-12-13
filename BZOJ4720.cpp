#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define MAXN 2005
#define MAXV 305
#define INF 1e12
int n,m,V,E,head[MAXN];

int c[MAXN],d[MAXN],map[MAXV][MAXV];
double ans=INF,dp[MAXN][MAXN][2],k[MAXN];

void work() {
	for (int i=1;i<=n;i++)
		for (int j=0;j<=m;j++) 
			dp[i][j][0]=dp[i][j][1]=INF;
	dp[1][0][0]=0,dp[1][1][1]=0;
	for (int i=1;i<n;i++) {
		for (int j=0;j<=m;j++) {
			// 0 -> 0
			dp[i+1][j][0]=min(dp[i+1][j][0],dp[i][j][0]+map[c[i]][c[i+1]]);
			// 1 -> 0
			dp[i+1][j][0]=min(dp[i+1][j][0],dp[i][j][1]+(1-k[i])*map[c[i]][c[i+1]]+k[i]*map[d[i]][c[i+1]]);
			// 0 -> 1
			dp[i+1][j+1][1]=min(dp[i+1][j+1][1],dp[i][j][0]+(1-k[i+1])*map[c[i]][c[i+1]]+k[i+1]*map[c[i]][d[i+1]]);
			// 1 -> 1
			dp[i+1][j+1][1]=min(dp[i+1][j+1][1],dp[i][j][1]+(1-k[i])*(1-k[i+1])*map[c[i]][c[i+1]]+k[i]*(1-k[i+1])*map[d[i]][c[i+1]]+(1-k[i])*k[i+1]*map[c[i]][d[i+1]]+k[i]*k[i+1]*map[d[i]][d[i+1]]);
		}
	}
	for (int i=0;i<=m;i++) {
		ans=min(ans,dp[n][i][0]);
		ans=min(ans,dp[n][i][1]);
	}
}

int main() {
	scanf("%d%d%d%d",&n,&m,&V,&E);
	for (int i=1;i<=n;i++) {
		scanf("%d",c+i);
	}
	for (int i=1;i<=n;i++) {
		scanf("%d",d+i);
	}
	k[0]=1;
	for (int i=1;i<=n;i++) {
		scanf("%lf",k+i);
	}
	memset(map,63,sizeof(map));
	for (int i=1;i<=V;i++) {
		map[i][i]=0;
	}
	for (int i=1,u,v,w;i<=E;i++) {
		scanf("%d%d%d",&u,&v,&w);
		if (w<map[u][v]) {
			map[u][v]=map[v][u]=w;
		}
	}
	for (int kk=1;kk<=V;kk++) 
		for (int i=1;i<=V;i++)
			for (int j=1;j<=V;j++) {
				if (map[i][j]>map[i][kk]+map[kk][j]) {
					map[i][j]=map[i][kk]+map[kk][j];
				}
			}
/*	if (n<=20 && m!=0) {
		int top=1<<n;
		f[1][0]=0;
		f[1][1]=0;
		for (int i=0;i<top;i++) 
			check(i<<1);
	}
	else {
		ans=0;
		for (int i=2;i<=n;i++) {
			ans+=map[c[i-1]][c[i]];
		}
	}*/
	work();
	printf("%.2lf\n",ans);
	return 0;
}

