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
	int next,to;
}e[MAXN<<1];

struct node {
	int l,r,v;
}t[MAXN<<5];

struct lsh {
	int x,v;
	bool operator < (lsh a) const {
		return v<a.v;
	}
}tem[MAXN];

int n,m,ecnt=0,tcnt=0;
int h[MAXN],rec[MAXN],head[MAXN],rt[MAXN],lr[MAXN],rr[MAXN],dfn=0;

void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}
#define lch t[now].l
#define rch t[now].r
int update(int x,int l,int r,int v) {
	int now=++tcnt;
	t[now]=t[x];
	t[now].v++;
	if (l!=r) {
		int mid=(l+r)>>1;
		if (v<=mid) lch=update(lch,l,mid,v);
		else rch=update(rch,mid+1,r,v);
	}
	return now;
}

void dfs(int x,int fa) {
	lr[x]=++dfn;
	rt[dfn]=update(rt[dfn-1],1,n,h[x]);
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=fa) dfs(e[now].to,x);
	}
	rr[x]=dfn;
}

int kth(int lx,int rx,int l,int r,int k) {
	if (l==r) return rec[l];
	int mid=(l+r)>>1,lv=t[t[rx].l].v-t[t[lx].l].v;
	if (lv>=k) return kth(t[lx].l,t[rx].l,l,mid,k);
	else return kth(t[lx].r,t[rx].r,mid+1,r,k-lv);
}

int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		read(h[i]);tem[i].v=h[i];tem[i].x=i;
	}
	sort(tem+1,tem+n+1);
	for (int i=1;i<=n;i++) {
		h[tem[i].x]=i;
		rec[i]=tem[i].x;
	}
	for (int i=1,u,v;i<n;i++) {
		read(u);read(v);add(u,v);
	}
	dfs(1,0);
	read(m);
	for (int i=1,x,k;i<=m;i++) {
		read(x);read(k);
		printf("%d\n",kth(rt[lr[x]-1],rt[rr[x]],1,n,k));
	}
	return 0;
}

