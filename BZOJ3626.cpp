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

#define MAXN 50005
#define MOD 201314
int ch;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

struct edge {
	int next,to;
}e[MAXN];

struct query {
	int x,p,z;
	query(){}
	query(int a,int b,int c):x(a),p(b),z(c){}
	bool operator < (query a) const {
		return p<a.p;
	}
}q[MAXN*2];

int n,Q,ecnt=0,qcnt=0;
int head[MAXN],fa[MAXN],son[MAXN],top[MAXN],tid[MAXN],dep[MAXN],siz[MAXN],maxs[MAXN],dfn=0;
int ans[MAXN];
#define s 65536
int t[s<<1],lazy[s<<1],L[s<<1],R[s<<1];

inline void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
}

void finds(int x) {
	maxs[x]=son[x]=0;
	siz[x]=1;
	for (int now=head[x];now;now=e[now].next) {
		int v=e[now].to;
		dep[v]=dep[x]+1;
		finds(v);
		siz[x]+=siz[v];
		if (siz[v]>maxs[x]) {
			maxs[x]=siz[v];
			son[x]=v;
		}
	}
}

void link(int x,int anc) {
	tid[x]=++dfn;
	top[x]=anc;
	if (son[x]) {
		link(son[x],anc);
		for (int now=head[x];now;now=e[now].next) {
			int v=e[now].to;
			if (v!=son[x]) {
				link(v,v);
			}
		}
	}
}

void init() {
	dep[1]=1;
	finds(1);
	link(1,1);
	for (int i=1;i<s;i++) {
		L[s+i]=R[s+i]=i;
	}
	for (int i=s-1;i;i--) {
		L[i]=L[i<<1];
		R[i]=R[(i<<1)^1];
	}
}

inline void pushdown(int x) {
	int val=int(((R[x<<1]-L[x<<1]+1)*(long long)lazy[x])%MOD);
	t[x<<1]=t[x<<1]+val;
	if (t[x<<1]>=MOD) t[x<<1]-=MOD;
	t[(x<<1)^1]=t[(x<<1)^1]+val;
	if (t[(x<<1)^1]>=MOD) t[(x<<1)^1]-=MOD;
	lazy[x<<1]+=lazy[x];
	lazy[(x<<1)^1]+=lazy[x];
	lazy[x]=0;
}

void update(int x,int l,int r) {
	if (L[x]==l && R[x]==r) {
		t[x]+=r-l+1;
		lazy[x]++;
		if (t[x]>=MOD) t[x]-=MOD;
		return;
	}
	if (x<s && lazy[x]) pushdown(x);
	int mid=(L[x]+R[x])>>1;
	if (l<=mid) update(x<<1,l,min(r,mid));
	if (r>mid) update((x<<1)^1,max(mid+1,l),r);
	t[x]=t[x<<1]+t[(x<<1)^1];
	if (t[x]>=MOD) t[x]-=MOD;
}

int query_(int x,int l,int r) {
	if (L[x]==l && R[x]==r) {
		return t[x];
	}
	if (x<s && lazy[x]) pushdown(x);
	int mid=(L[x]+R[x])>>1,ret=0;
	if (l<=mid) ret+=query_(x<<1,l,min(r,mid));
	if (r>mid) ret+=query_((x<<1)^1,max(mid+1,l),r);
	if (ret>=MOD) ret-=MOD;
	return ret;
}

void __update(int x) {
	while (top[x]!=1) {
		update(1,tid[top[x]],tid[x]);
		x=fa[top[x]];
	}
	update(1,1,tid[x]);
}

int __query(int x) {
	int ret=0;
	while (top[x]!=1) {
		ret+=query_(1,tid[top[x]],tid[x]);
		x=fa[top[x]];
	}
	return (ret+query_(1,1,tid[x]))%MOD;
}

int main() {
	read(n);read(Q);
	for (int i=2;i<=n;i++) {
		read(fa[i]);
		++fa[i];
		add(fa[i],i);
	}
	for (int i=1,l,r,z;i<=Q;i++) {
		read(l);read(r);read(z);
		r++,z++;
		if (l!=0) q[++qcnt]=query(-i,l,z);
		q[++qcnt]=query(i,r,z);
	}
	sort(q+1,q+qcnt+1);
	init();
	int nowq=1;
	for (int i=1;i<=n;i++) {
		__update(i);
		while (nowq<=qcnt && q[nowq].p==i) {
			int ret=__query(q[nowq].z);
			if (q[nowq].x<0) ans[-q[nowq].x]-=ret;
			else ans[q[nowq].x]+=ret;
			nowq++;
		}
	}
	for (int i=1;i<=Q;i++) {
		if (ans[i]<0) printf("%d\n",ans[i]+MOD);
		else printf("%d\n",ans[i]);
	}
	return 0;
}

