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
#define MAXM 250005
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

struct data {
	int u,v;
}y[MAXM];

struct edge {
	int next,to,flow;
}e[MAXM<<2];

int n,m,r,t,k,S=0,T,head[MAXN],cur[MAXN],tag[MAXN],ecnt=1;

void add(int u,int v,int flow) {
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
		for (int i=0;i<=T;i++) cur[i]=head[i];
		ret+=dfs(S,0x7fffffff);
	}
	return ret;
}

bool act[MAXN];

int check() {
	for (int i=1;i<=n;i++) {
		if (act[i]) add(S,i,1);
	}
	int ret=dinic();
	for (int i=1;i<=n;i++) {
		if (act[i] && !e[head[i]].flow) {
			act[i]=0;
		}
	}
	return ret;
}

int main() {
	read(n);read(m);read(r);read(t);read(k);
	T=n+m+1;
	for (int i=1;i<=k;i++) {
		read(y[i].u);read(y[i].v);
		y[i].v+=n;
	}
	int lim=t/r,score=0,penal=0;
	for (int i=1;i<=n;i++) act[i]=1;
	for (int i=1;i<=m;i++) add(i+n,T,1);
	for (int i=1;i<=k;i++) add(y[i].u,y[i].v,1);
	for (int i=1;i<=lim;i++) {
		int ret=check();
		if (ret) {
			score+=ret;
			penal+=ret*i*r;
		}
		else break;
	}
	printf("%d %d\n",score,penal);
	return 0;
}
