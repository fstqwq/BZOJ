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
#define MAXN 1000005
struct edge{
	int next,to,w;
}e[MAXN<<1];

int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=(a<<3)+(a<<1)+ch-48;ch=getchar();}
}

long long ans=0;
int n,ecnt=0,head[MAXN],fa[MAXN];
int q[MAXN],siz[MAXN];
inline void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].w=w;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].w=w;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

inline void bfs() {
	int h=1,t=2;
	q[1]=1;
	while (h^t) {
		int x=q[h++];
		for (int now=head[x],v;now;now=e[now].next) {
			v=e[now].to;
			if (v!=fa[x]) {
				fa[v]=x;
				q[t++]=v;
			}
		}
	}
}


inline void work() {
	bfs();
	for (int i=n;i;i--) {
		int x=q[i];
		siz[x]=1;
		for (int now=head[x],v;now;now=e[now].next) {
			v=e[now].to;
			if (v!=fa[x]) {
				ans+=(long long)e[now].w*(long long)abs(n-(siz[v]<<1));
				siz[x]+=siz[v];
			}
		}
	}
	printf("%lld\n",ans);
}

int main() {
	read(n);
	for (int i=1,u,v,w;i<n;i++) {
		read(u);read(v);read(w);
		add(u,v,w);
	}
	work();
	return 0;
}

