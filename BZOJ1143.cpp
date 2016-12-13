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

struct edge {
	int next,to,flow;
}e[MAXN*MAXN*4];

int n,m,ecnt=1,head[MAXN<<1],tag[MAXN<<1],cur[MAXN<<1];
bool G[MAXN][MAXN];

void add(int u,int v,int f) {
	e[++ecnt].to=v;
	e[ecnt].flow=f;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].flow=0;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

int q[MAXN<<1];
bool bfs() {
	memset(tag,0,sizeof(tag));
	int he=1,ta=2;
	q[1]=0;
	tag[0]=1;
	while (he!=ta) {
		int x=q[he++];
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q[ta++]=e[now].to;
			}
		}
	}
	return tag[1]>0;
}
  
int dfs(int x,int flow) {
	if (x==1) return flow;
	int usd=0;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tag[x]<tag[e[now].to]) {
			int ret=dfs(e[now].to,min(e[now].flow,flow-usd));
			if (ret) {
				usd+=ret;
				e[now].flow-=ret;
				e[now^1].flow+=ret;
				if (usd==flow) return flow;
			}
		}
	}
	return usd;
}
  
int dinic() {
	int ans=0;
	while (bfs()) {
		for (int i=0,ta=(n<<1)^1;i<=ta;i++) cur[i]=head[i];
		ans+=dfs(0,n<<1);
	}
	return ans;
}

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1,u,v;i<=m;i++) {
		scanf("%d%d",&u,&v);
		G[u][v]=1;
	}
	for (int k=1;k<=n;k++) 
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) {
				G[i][j]=G[i][j]|(G[i][k]&G[k][j]);
			}
	for (int i=1;i<=n;i++) {
		add(0,i<<1,1);
		add((i<<1)^1,1,1);
		for (int j=1;j<=n;j++) {
			if (G[i][j]) add(i<<1,(j<<1)^1,1);
		}
	}
	printf("%d\n",n-dinic());
	return 0;
}

