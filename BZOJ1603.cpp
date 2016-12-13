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
int n,head[MAXN],val[MAXN],ecnt=0;
inline void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].w=w;
	head[u]=ecnt;
}

void dfs(int x,int fa) {
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=fa) {
			val[e[now].to]=val[x]^e[now].w;
			dfs(e[now].to,x);
		}
	}
}

int main() {
	scanf("%d",&n);
	for (int i=1,u,v,w;i<n;i++) {
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w^1);add(v,u,w^1);
	}
	val[1]=1;
	dfs(1,0);
	printf("%d\n",val[n]);
	return 0;
}

