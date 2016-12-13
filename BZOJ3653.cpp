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

typedef long long LL;
int ch;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 300005
struct edge {
	int next,to;
}e[MAXN<<1];

struct node {
	int lch,rch;
	LL v;
}t[MAXN<<5];

int head[MAXN],fa[MAXN],dep[MAXN],siz[MAXN],L[MAXN],R[MAXN],rt[MAXN],tid[MAXN];
int n,q,ecnt=0,dfn=0,tcnt=0;
inline void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

void dfs(int x) {
	siz[x]=1;
	L[x]=++dfn;
	tid[dfn]=x;
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=fa[x]) {
			fa[e[now].to]=x;
			dep[e[now].to]=dep[x]+1;
			dfs(e[now].to);
			siz[x]+=siz[e[now].to];
		}
	}
	R[x]=dfn;
}

int update(int x,int l,int r,int p,int v) {
	int now=++tcnt;
	t[now].lch=t[x].lch,t[now].rch=t[x].rch,t[now].v=t[x].v+v;
	if (l!=r) {
		int mid=(l+r)>>1;
		if (p<=mid) t[now].lch=update(t[x].lch,l,mid,p,v);
		else t[now].rch=update(t[x].rch,mid+1,r,p,v);
	}
	return now;
}

LL query(int lrt,int rrt,int l,int r,int ql,int qr) {
	if (l==ql && r==qr) {
		return t[rrt].v-t[lrt].v;
	}
	int mid=(l+r)>>1;
	LL ret=0;
	if (ql<=mid) ret+=query(t[lrt].lch,t[rrt].lch,l,mid,ql,min(mid,qr));
	if (qr>mid) ret+=query(t[lrt].rch,t[rrt].rch,mid+1,r,max(mid+1,ql),qr);
	return ret;
}


int main() {
	read(n);read(q);
	for (int i=1,u,v;i<n;i++) {
		read(u);read(v);
		add(u,v);
	}
	rt[0]=0;
	fa[0]=0;
	fa[1]=0;
	dep[1]=1;
	dfs(1);
	for (int i=1;i<=n;i++) {
		rt[i]=update(rt[i-1],1,n,dep[tid[i]],siz[tid[i]]-1);
	}
	for (int i=1,x,k;i<=q;i++) {
		read(x);read(k);
		LL ans=min(k,dep[x]-1)*LL(siz[x]-1)+query(rt[L[x]-1],rt[R[x]],1,n,dep[x]+1,min(dep[x]+k,n));
		printf("%lld\n",ans);
	}
	return 0;
}

