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
#define MAXN 20005
#define MAXM 200005

int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

struct edge_read{
	int u,v,w;
}r[MAXM];

struct edge {
	int next,to,flow;
}e[MAXM<<1];

int n,m,s,t,L,ecnt,head[MAXN];
int tag[MAXN];

inline void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].flow=1;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].flow=1;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

queue <int> q;
bool bfs() {
	memset(tag,0,sizeof(tag));
	tag[s]=1;
	q.push(s);
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tag[t]!=0;
}

bool dfs(int x) {
	if (x==t) return 1;
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].flow && tag[e[now].to]>tag[x]) {
			if (dfs(e[now].to)) {
				e[now].flow--;
				e[now^1].flow++;
				return 1;
			}
		}
	}
	return 0;
}

int ans=0;

void dinic() {
	while (bfs()) {
		while (dfs(s)) {
			ans++;
		}
	}
}

int main() {
	read(n);read(m);
	for (int i=1;i<=m;i++) {
		read(r[i].u);read(r[i].v);read(r[i].w);		
	}
	read(s);read(t);read(L);
	ecnt=1;
	memset(head,0,sizeof(head));
	for (int i=1;i<=m;i++) {
		if (r[i].w<L) add(r[i].u,r[i].v);
	}
	dinic();
	ecnt=1;
	memset(head,0,sizeof(head));
	for (int i=1;i<=m;i++) {
		if (r[i].w>L) add(r[i].u,r[i].v); 
	}
	dinic();
	printf("%d\n",ans);
	return 0;
}

