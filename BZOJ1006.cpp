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

#define MAXN 10005
#define MAXM 2000005

struct edge {
	int next,to;
}e[MAXM];

int n,m,head[MAXN],ecnt=0;

inline void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

struct node {
	int next,x;
}p[MAXM+MAXN];
int pcnt=0,level[MAXN],seq[MAXN],label[MAXN];
int visit[MAXN];
inline void Push(int lev,int x) {
	p[++pcnt].x=x;
	p[pcnt].next=level[lev];
	level[lev]=pcnt;
}
inline void Pop(int lev) {level[lev]=p[level[lev]].next;}

void MCS() {
	for (int i=1;i<=n;i++) {
		label[i]=0;
		Push(0,i);
	}
	int top=0;
	for (int i=n;i>0;i--) {
		while (1) {
			while (level[top] && visit[p[level[top]].x]) Pop(top);
			if (level[top]) break;
			else top--;
		}
		int x=p[level[top]].x;Pop(top);seq[i]=x;
		visit[x]=1;
		for (int now=head[x];now;now=e[now].next) {
			if (!visit[e[now].to]) {
				label[e[now].to]++;
				if (label[e[now].to]>top) top=label[e[now].to];
				Push(label[e[now].to],e[now].to);
			}
		}
	}
}

int main() {
	read(n);read(m);
	for (int i=1,u,v;i<=m;i++) {
		read(u);read(v);
		add(u,v);
	}
	MCS();
	memset(visit,0,sizeof(visit));
	memset(level,0,sizeof(level));
	int ans=0;
	for (int i=n;i>=1;i--) {
		int x=seq[i];
		for (int now=head[x];now;now=e[now].next) {
			visit[level[e[now].to]]=x;
		}
		int col;
		for (col=1;;col++) if (visit[col]!=x) break;
		level[x]=col;
		ans=max(col,ans);
	}
	printf("%d\n",ans);
	return 0;
}

