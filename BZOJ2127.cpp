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
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 100005
struct edge {
	int next,to,flow;
}e[MAXN<<3];
int S=0,T=1,head[MAXN],tg[MAXN],cur[MAXN],ecnt=1;
int n,m,tot=0,tcnt=1,tag[105][105];
inline void add(int u,int v,int flow) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=flow;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=flow;
	head[v]=ecnt;
}

void init() {
	read(n);read(m);
	for (int i=1,a;i<=n;i++) 
		for (int j=1;j<=m;j++) {
			tag[i][j]=++tcnt;
			read(a);
			tot+=a;
			add(S,tag[i][j],a);
		}
	for (int i=1,a;i<=n;i++)
		for (int j=1;j<=m;j++) {
			read(a);
			tot+=a;
			add(tag[i][j],T,a);
		}
	for (int i=1,a;i<n;i++)
		for (int j=1;j<=m;j++) {
			read(a);
			tot+=a;
			add(S,++tcnt,a);
			add(tcnt,tag[i][j],a);
			add(tcnt,tag[i+1][j],a);
		}
	for (int i=1,a;i<n;i++)
		for (int j=1;j<=m;j++) {
			read(a);
			tot+=a;
			add(++tcnt,T,a);
			add(tag[i][j],tcnt,a);
			add(tag[i+1][j],tcnt,a);
		}
	for (int i=1,a;i<=n;i++)
		for (int j=1;j<m;j++) {
			read(a);
			tot+=a;
			add(S,++tcnt,a);
			add(tcnt,tag[i][j],a);
			add(tcnt,tag[i][j+1],a);
		}
	for (int i=1,a;i<=n;i++)
		for (int j=1;j<m;j++) {
			read(a);
			tot+=a;
			add(++tcnt,T,a);
			add(tag[i][j],tcnt,a);
			add(tag[i][j+1],tcnt,a);
		}
}
queue <int> q;

bool bfs() {
	q.push(S);
	memset(tg,0,sizeof(tg));
	tg[S]=1;
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tg[e[now].to]) {
				tg[e[now].to]=tg[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tg[T]>0;
}

int dfs(int x,int flow) {
	if (x==T) return flow;
	int used=0;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tg[e[now].to]>tg[x]) {
			int ret=dfs(e[now].to,min(flow-used,e[now].flow));
			if (ret) {
				used+=ret;
				e[now].flow-=ret;
				e[now^1].flow+=ret;
				if (used==flow) return flow;
			}
		}
	}
	return used;
}

int dinic() {
	int ret=0;
	while (bfs()) {
		for (int i=0;i<=tcnt;i++) cur[i]=head[i];
		ret+=dfs(S,0x7fffffff);
	}
	return ret;
}

int main() {
	init();
	printf("%d\n",tot-dinic());
	return 0;
}

