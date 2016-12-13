/*This is a source code from FirstLast*/
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
#define MAXM 50005
#define MAXN 10005

struct edge {
	int next,to;
}e[MAXM],f[MAXM];

int n,m,scc=0,head[MAXN],belong[MAXN],dfn[MAXN],low[MAXN],siz[MAXN],cnt=0;
int sta[MAXN],top=0;
bool inq[MAXN];
void dfs(int x) {
	dfn[x]=low[x]=++cnt;
	sta[++top]=x;
	inq[x]=1;
	for (int now=head[x],v;now;now=e[now].next) {
		v=e[now].to;
		if (!dfn[v]) dfs(v),low[x]=min(low[x],low[v]);
		else if (inq[v]) low[x]=min(low[x],low[v]);
	}
	if (dfn[x]==low[x]) {
		siz[++scc]=0;
		int now=0;
		while (now!=x) {
			now=sta[top--];
			belong[now]=scc;
			inq[now]=0;
			siz[scc]++;
		}
	}
}

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1,u,v;i<=m;i++) {
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	dfs(1);
	return 0;
}

