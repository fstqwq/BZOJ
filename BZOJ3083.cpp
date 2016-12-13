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

#define MAXN 200005

struct edge {
	int next,to;
}e[MAXN<<1];

int n,m,ecnt=0,head[MAXN],a[MAXN],val[MAXN];
int maxs[MAXN],siz[MAXN],son[MAXN],fa[MAXN],dep[MAXN],top[MAXN],tid[MAXN],dfn=0;
int lt[MAXN],rt[MAXN];
int t[524288],lazy[524288],lch[524288],rch[524288],tcnt=0;

inline void pushdown(int x) {
	if (lazy[x]) {
		t[lch[x]]=t[rch[x]]=lazy[x];
		lazy[x]=0;
	}
}

inline void pushup(int x) {
	t[x]=min(t[lch[x]],t[rch[x]]);
}

int build(int l,int r) {
	int now=++tcnt;
	if (l==r) {
		t[now]=val[l];
		return now;
	}
	int mid=(l+r)>>1;
	lch[now]=build(l,mid);
	rch[now]=build(mid+1,r);
	pushup(now);
	return now;
}

void update(int x,int l,int r,int L,int R,int v) {
	if (l==L && r==R) {
		t[x]=lazy[x]=v;
		return;
	}
	pushdown(x);
	int mid=(L+R)>>1;
	if (l<=mid) update(lch[x],l,min(mid,r),L,mid,v);
	if (r>mid) update(rch[x],max(mid+1,l),r,mid+1,R,v);
	pushup(x);
}

int query(int x,int l,int r,int L,int R) {
	if (l==L && r==R) return t[x];
	if (lazy[x]) return t[x];
	pushdown(x);
	int mid=(L+R)>>1;
	int ret=0x7fffffff;
	if (l<=mid) ret=query(lch[x],l,min(mid,r),L,mid);
	if (r>mid) ret=min(ret,query(rch[x],max(mid+1,l),r,mid+1,R));
	return ret;
}

void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

void finds(int x) {
	siz[x]=1;
	maxs[x]=son[x]=0;
	for (int now=head[x];now;now=e[now].next) {
		int v=e[now].to;
		if (v!=fa[x]) {
			fa[v]=x;
			dep[v]=dep[x]+1;
			finds(v);
			siz[x]+=siz[v];
			if (siz[v]>=maxs[x]) {
				maxs[x]=siz[v];
				son[x]=v;
			}
		}
	}
}

void link(int x,int anc) {
	tid[x]=++dfn;
	lt[x]=dfn;
	top[x]=anc;
	val[dfn]=a[x];
	if (son[x]) {
		link(son[x],anc);
		for (int now=head[x];now;now=e[now].next) {
			int v=e[now].to;
			if (v!=fa[x] && v!=son[x]) {
				link(v,v);
			}
		}
	}
	rt[x]=dfn;
}

void init() {
	fa[1]=1;dep[1]=1;
	finds(1);
	link(1,1);
	build(1,n);
}

int nowrt=1;

void __update(int u,int v,int w) {
	while (top[u]!=top[v]) {
		if (dep[top[u]]<dep[top[v]]) swap(u,v);
		update(1,tid[top[u]],tid[u],1,n,w);
		u=fa[top[u]];
	}
	if (dep[v]<dep[u]) {
		swap(u,v);
	}
	update(1,tid[u],tid[v],1,n,w);
}

int findtheson(int x,int r) {
	while (top[r]!=top[x]) {
		r=top[r];
		if (fa[r]!=x) r=fa[r];
		else break;
	}
	if (fa[r]==x) return tid[r];
	else return tid[x]+1;
}

int __query(int x) {
	if (nowrt==x) {
		return t[1];
	}
	else if (tid[nowrt]<lt[tid[x]] || tid[nowrt]>rt[tid[x]]) {
		return query(1,lt[tid[x]],rt[tid[x]],1,n);
	}
	else {
		int theson=findtheson(x,nowrt);
		int ret=0x7fffffff;
		if (lt[theson]>1) ret=query(1,1,lt[theson]-1,1,n);
		if (rt[theson]<n) ret=min(ret,query(1,rt[theson]+1,n,1,n));
		return ret;
	}
}

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1,u,v;i<n;i++) {
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	for (int i=1;i<=n;i++) {
		scanf("%d",a+i);
	}
	init();
	scanf("%d",&nowrt);
	for (int i=1,opt,u,v,w;i<=m;i++) {
		scanf("%d",&opt);
		if (opt==1) {
			scanf("%d",&nowrt);
		}
		else if (opt==2) {
			scanf("%d%d%d",&u,&v,&w);
			__update(u,v,w);
		}
		else {
			scanf("%d",&u);
			printf("%d\n",__query(u));
		}
	}
	return 0;
}

