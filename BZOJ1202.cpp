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
#define MAXM 1005

struct edge {
	int next,to,w;
}e[MAXM];

int T,n,m,ecnt=0,head[MAXN],val[MAXN];

void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].w=w;
	e[ecnt].next=head[u];
	head[u]=ecnt;
}

bool check(int x) {
	for (int now=head[x];now;now=e[now].next) {
		if (val[e[now].to]==-1) {
			val[e[now].to]=val[x]+e[now].w;
		}
		if (val[e[now].to]!=val[x]+e[now].w) return 1;
	}
	return 0;
}

int main() {
	scanf("%d",&T);
	while (T--) {
		scanf("%d%d",&n,&m);
		memset(head,0,sizeof(head));
		ecnt=0;
		for (int i=1,u,v,w;i<=m;i++) {
			scanf("%d%d%d",&u,&v,&w);
			add(u-1,v,w);
		}
		memset(val,-1,sizeof(val));
		bool flag=1;
		for (int i=0;i<=n;i++) {
			if (val[i]==-1) val[i]=0;
			if (check(i)) {flag=0;break;}
		}
		if (flag) puts("true");
		else puts("false");
	}
	return 0;
}

