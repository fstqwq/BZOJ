/*	Never stop fighting for what you believe in.	*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

#define MAXN 100005
#define MAXM 2000005

struct edge {
	int next,to;
}e[MAXM<<1];

int n,m,head[MAXN],ecnt=0;
int nxt[MAXN],pre[MAXN],tot[MAXN],ans=0;
bool mark[MAXN];
void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

void del(int x) {
	nxt[pre[x]]=nxt[x];
	pre[nxt[x]]=pre[x];
}

int q[MAXN];
void bfs() {
	int he=0,ta=1;
	q[he]=nxt[0];
	del(nxt[0]);
	ans++;
	tot[ans]=1;
	while (he<ta) {
		int x=q[he++];
		for (int now=head[x];now;now=e[now].next) mark[e[now].to]=1;
		for (int to=nxt[0];to<=n;to=nxt[to]) {
			if (!mark[to]) {
				del(to);
				tot[ans]++;
				q[ta++]=to;
			}
		}
		for (int now=head[x];now;now=e[now].next) mark[e[now].to]=0;
	}
}

int main() {
	read(n);read(m);
	for (int i=1,u,v;i<=m;i++) {
		read(u);read(v);
		add(u,v);
	}
	for (int i=0;i<=n;i++) nxt[i]=i+1;
	for (int i=n+1;i;i--) pre[i]=i-1;
	while (nxt[0]<=n) bfs();
	printf("%d\n",ans);
	sort(tot+1,tot+ans+1);
	for (int i=1;i<=ans;i++) printf("%d ",tot[i]);
	return 0;
}

