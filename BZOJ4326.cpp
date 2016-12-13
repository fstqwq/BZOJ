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

#define MAXN 300005

int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=(a<<3)+(a<<1)+ch-'0';ch=getchar();}
}

struct edge{
	int next,to,w;
}e[MAXN<<1];

int n,m,maxl=0,ecnt=0,head[MAXN],rs[MAXN],rt[MAXN],rd[MAXN],len[MAXN];

int ss[MAXN],maxs[MAXN],son[MAXN],fa[MAXN],dep[MAXN],dis[MAXN];
int top[MAXN],tid[MAXN],dfn=0;

int t[MAXN],rlen[MAXN];

inline void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].w=w;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].w=w;
	head[v]=ecnt;
}

inline void input() {
	read(n);read(m);
	for (int i=1,u,v,w;i<n;i++) {
		read(u);read(v);read(w);
		add(u,v,w);
	}
	for (int i=1;i<=m;i++) {
		read(rs[i]);read(rt[i]);
	}
}

void finds(int x) {
	son[x]=maxs[x]=0;
	ss[x]=1;
	for (int now=head[x],v;now;now=e[now].next) {
		v=e[now].to;
		if (v!=fa[x]) {
			rd[v]=e[now].w;
			dis[v]=dis[x]+e[now].w;
			fa[v]=x;
			dep[v]=dep[x]+1;
			finds(v);
			ss[x]+=ss[v];
			if (ss[v]>maxs[x]) {
				maxs[x]=ss[v];
				son[x]=v;
			}
		}
	}
}

void link(int x,int anc) {
	tid[x]=++dfn;
	rlen[dfn]=rd[x];
	top[x]=anc;
	if (son[x]) {
		link(son[x],anc);
		for (int now=head[x],v;now;now=e[now].next) {
			v=e[now].to;
			if (v!=fa[x] && v!=son[x]) {
				link(v,v);
			}
 		}
	}
}

inline void init() {
	input();
	fa[1]=1;
	dis[1]=0;
	dep[1]=1;
	finds(1);
	link(1,1);
}

int getLCA(int u,int v) {
	while (top[u]!=top[v]) {
		if (dep[top[u]]>dep[top[v]]) {
			swap(u,v);
		}
		v=fa[top[v]];
	}
	if (dep[u]<dep[v]) return u;
	return v;
}

inline void getlen() {
	for (int i=1;i<=m;i++) {
		int lca=getLCA(rs[i],rt[i]);
		len[i]=dis[rs[i]]+dis[rt[i]]-(dis[lca]<<1);
		maxl=max(maxl,len[i]);
	}
}

inline void mark(int x) {
	int u=rs[x],v=rt[x];
	while (top[u]!=top[v]) {
		if (dep[top[u]]>dep[top[v]]) {
			swap(u,v);
		}
		// mark top[v] + ~ v +
		t[tid[top[v]]]++,t[tid[v]+1]--;
		v=fa[top[v]];
	}
	if (dep[u]>dep[v]) {
		swap(u,v);
	}
	// mark u - ~ v +
	t[tid[u]+1]++,t[tid[v]+1]--;
}

inline bool check(int x) {
	memset(t,0,sizeof(t));
	int cnt=0;
	for (int i=1;i<=m;i++) {
		if (len[i]>x) {
			mark(i);
			cnt++;
		}
	}
	for (int i=1;i<=n;i++) {
		t[i]+=t[i-1];
		if (t[i]>=cnt && maxl-x<=rlen[i]) return 1;
	}
	return 0;
}

int main() {
	//freopen("transport.in","r",stdin);
	//freopen("transport.out","w",stdout);
	init();
	getlen();
	int l=0,r=maxl,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}

