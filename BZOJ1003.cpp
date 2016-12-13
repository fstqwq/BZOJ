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

#define MAXN 105
#define MAXM 25

int n,m,K,E,D;
int minc[MAXN][MAXN],G[MAXM][MAXM],dis[MAXM];
bool fuck[MAXN][MAXM],ban[MAXM];
int ans[MAXN];

queue <int> q;
bool inq[MAXN];
int work(int ti) {
	for (int i=1;i<=m;i++) {
		if (fuck[ti][i]) ban[i]=1;
	}
	memset(dis,63,sizeof(dis));
	dis[1]=0;
	q.push(1);
	while (!q.empty()) {
		int x=q.front();q.pop();
		inq[x]=0;
		for (int i=1;i<=m;i++) {
			if (!ban[i] && dis[i]>G[x][i]+dis[x]) {
				dis[i]=G[x][i]+dis[x];
				if (!inq[i]) {
					inq[i]=1;
					q.push(i);
				}
			}
		}
	}
	return dis[m];
}

int main() {
	scanf("%d%d%d%d",&n,&m,&K,&E);
	memset(G,63,sizeof(G));
	for (int i=1;i<=m;i++) G[i][i]=0;
	for (int i=1,u,v,w;i<=E;i++) {
		scanf("%d%d%d",&u,&v,&w);
		if (G[u][v]>w) G[u][v]=G[v][u]=w;
	}
	scanf("%d",&D);
	for (int i=1,P,a,b;i<=D;i++) {
		scanf("%d%d%d",&P,&a,&b);
		for (int j=a;j<=b;j++) {
			fuck[j][P]=1;
		}
	}
	ans[0]=0;
	for (int i=1;i<=n;i++) {
		memset(ban,0,sizeof(ban));
		for (int j=i;j<=n;j++) {
			minc[i][j]=work(j);
		}
	}
	for (int i=1;i<=n;i++) {
		ans[i]=0x3f3f3f3f;
		for (int j=0;j<i;j++) {
			if (minc[j+1][i]<0x3f3f3f3f) ans[i]=min(ans[i],ans[j]+minc[j+1][i]*(i-j)+K);
		}
	}
	printf("%d\n",ans[n]-K);
	return 0;
}

