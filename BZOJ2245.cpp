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
typedef long long LL;
#define MAXN 256
#define INF 0x7f7f7f7f
struct edge {
	int next,to,w,flow;
}e[MAXN*MAXN*64];

int m,n,S=0,T=1,ecnt=1;
int L[MAXN],t[MAXN][MAXN],W[MAXN][MAXN],dis[MAXN*2],head[MAXN*2],pre[MAXN*2],pos[MAXN*2];
#define task(i) (i+1)
#define worker(i) (i+n+1)
bool inq[MAXN*2];
void add(int u,int v,int flow,int w) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=flow;
	e[ecnt].w=w;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=0;
	e[ecnt].w=-w;
	head[v]=ecnt;
}

void init() {
	read(m);read(n);
	for (int i=1,C;i<=n;i++) read(C),add(task(i),T,C,0);;
	for (int i=1,A;i<=m;i++) for (int j=1;j<=n;j++) {
		read(A);
		if (A) add(worker(i),task(j),INF,0);
	}
	for (int i=1;i<=m;i++) {
		read(L[i]);
		for (int j=0;j<L[i];j++) read(t[i][j]);
		for (int j=0;j<=L[i];j++) read(W[i][j]);
	}
	for (int i=1;i<=m;i++) {
		for (int j=0;j<L[i];j++) {
			add(S,worker(i),t[i][j]-t[i][j-1],W[i][j]);
		}
		add(S,worker(i),INF,W[i][L[i]]);
	}
}
queue <int> q;
bool spfa() {
	q.push(S);
	memset(dis,0x7f,sizeof(dis));
	dis[S]=0;
	memset(pre,0,sizeof(pre));
	memset(pos,0,sizeof(pos));
	while (!q.empty()) {
		int x=q.front();q.pop();inq[x]=0;
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && dis[e[now].to]>dis[x]+e[now].w) {
				dis[e[now].to]=dis[x]+e[now].w;
				pre[e[now].to]=x;
				pos[e[now].to]=now;
				if (!inq[e[now].to]) {
					q.push(e[now].to);
					inq[e[now].to]=1;
				}
			}
		}
	}
	return pos[T]>0;
}

void work() {
	LL ans=0;
	while (spfa()) {
		int Minflow=INF;
		for (int x=1;x;x=pre[x]) {
			Minflow=min(Minflow,e[pos[x]].flow);
		}
		ans+=LL(Minflow)*dis[T];
		for (int x=T;x;x=pre[x]) {
			e[pos[x]].flow-=Minflow;
			e[pos[x]^1].flow+=Minflow;
		}
	}
	printf("%lld\n",ans);
}

int main() {
	init();
	work();
	return 0;
}

