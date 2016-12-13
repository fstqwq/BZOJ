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
#define MAXN 1005
struct edge {
	int next,to,w;
}e[MAXN<<1];
int n,ecnt=0,q,fa[MAXN][15],dep[MAXN],dis[MAXN],head[MAXN];
inline void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].w=w;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].w=w;
	head[v]=ecnt;
}

void dfs(int x) {
	for (int k=1;k<=12;k++) {
		fa[x][k]=fa[fa[x][k-1]][k-1];
	}
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=fa[x][0]) {
			fa[e[now].to][0]=x;
			dep[e[now].to]=dep[x]+1;
			dis[e[now].to]=dis[x]+e[now].w;
			dfs(e[now].to);
		}
	}
}

int getLCA(int u,int v) {
	if (dep[u]<dep[v]) swap(u,v);
	int x=dep[u]-dep[v];
	for (int k=12;k>-1;k--) {
		if ((x>>k)&1) u=fa[u][k];
	}
	if (u==v) return u;
	for (int k=12;k>-1;k--) {
		if (fa[u][k]!=fa[v][k]) {
			u=fa[u][k];
			v=fa[v][k];
		}
	}
	return fa[u][0];
}

int main() {
	scanf("%d%d",&n,&q);
	for (int i=1,u,v,w;i<n;i++) {
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	fa[1][0]=1;
	dis[1]=0;
	dep[1]=0;
	dfs(1);
	for (int i=1,u,v;i<=q;i++) {
		scanf("%d%d",&u,&v);
		printf("%d\n",dis[u]+dis[v]-2*dis[getLCA(u,v)]);
	}
	return 0;
}

