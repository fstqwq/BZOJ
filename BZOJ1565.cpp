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

#define MAXN 605
#define pos(i,j) ((i)*m+(j))
#define INF 0x7fffffff
struct eeee {
	int next,to;
}f[MAXN*MAXN];

struct edge {
	int next,to,flow;
}e[MAXN*MAXN*2];

int n,m,nm,S,T,ecnt=1,fcnt=0;
int s[MAXN],head[MAXN],fh[MAXN],in[MAXN],tag[MAXN],cur[MAXN];
inline void add_(int u,int v) {
	f[++fcnt].to=v;
	f[fcnt].next=fh[u];
	fh[u]=fcnt;
	in[v]++;
}
inline void add(int u,int v,int flow) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=flow;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=0;
	head[v]=ecnt;
}
queue <int> q;
void topo() {
	for (int i=0;i<nm;i++) {
		if (!in[i]) {
			tag[i]=1;
			q.push(i);
		}
	}
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=fh[x];now;now=f[now].next) {
			in[f[now].to]--;
			if (in[f[now].to]==0) {
				tag[f[now].to]=tag[x]+1;
				q.push(f[now].to);
			}
		}
	}
}

int tot=0,ans=0;

bool bfs() {
	memset(tag,0,sizeof(tag));
	q.push(S);
	tag[S]=1;
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tag[T]>0;
}

int dfs(int x,int flow) {
	if (x==T) return flow;
	int used=0;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tag[e[now].to]>tag[x]) {
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
		for (int i=0;i<=nm+1;i++) cur[i]=head[i];
		ret+=dfs(S,INF);
	}
	return ret;
}

int main() {
	scanf("%d%d",&n,&m);nm=n*m;
	for (int i=0,w,x,y;i<n;i++)
		for (int j=0;j<m;j++) {
			scanf("%d%d",s+pos(i,j),&w);
			for (int k=1;k<=w;k++) {
				scanf("%d%d",&x,&y);
				add_(pos(i,j),pos(x,y));
			}
		}
	for (int i=0;i<n;i++) {
		for (int j=1;j<m;j++) {
			add_(pos(i,j),pos(i,j-1));
		}
	}
	topo();
	S=nm,T=nm+1;
	for (int i=0;i<nm;i++) {
		if (tag[i]) {
			if (s[i]>0) {
				add(S,i,s[i]);
				tot+=s[i];
			}
			else {
				add(i,T,-s[i]);
			}
		}
	}
	for (int x=0;x<nm;x++) {
		if (tag[x]) {
			for (int now=fh[x];now;now=f[now].next) {
				if (tag[f[now].to]) {
					add(f[now].to,x,INF);
				}
			}
		}
	}
	ans=tot-dinic();
	printf("%d\n",ans);
	return 0;
}

