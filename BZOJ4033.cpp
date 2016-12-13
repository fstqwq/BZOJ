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
#define MAXN 2005

typedef long long LL;

struct edge {
	int next,to;
	LL w;
}e[MAXN<<1];

int n,k,head[MAXN],siz[MAXN],ecnt=0;
LL dp[MAXN][MAXN],temp[MAXN];

void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].w=w;
	head[u]=ecnt;
}

void dfs(int x,int fa) {
	siz[x]=1;
	dp[x][0]=dp[x][1]=0;
	for (int now=head[x];now;now=e[now].next) {
		int v=e[now].to;
		if (v!=fa) {
			dfs(v,x);
			int topx=min(siz[x],k),topv=min(siz[v],k);
			for (int i=0;i<=k;i++) temp[i]=dp[x][i];
			for (int i=0;i<=topx;i++)
				for (int j=0;j<=topv && i+j<=k;j++) {
					temp[i+j]=max(temp[i+j],dp[x][i]+dp[v][j]+e[now].w*(j*(k-j)+(siz[v]-j)*(n-k-siz[v]+j)));
				}
			siz[x]+=siz[v];
			topx=min(siz[x],k);
			for (int i=0;i<=topx;i++) dp[x][i]=temp[i];
		}
	}
}


int main() {
	scanf("%d%d",&n,&k);
	for (int i=1;i<n;i++) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	printf("%lld\n",dp[1][k]);
	return 0;
}

