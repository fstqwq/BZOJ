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

int ch;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

#define MAXN 15005
#define MAXM 30005
#define MAXK 15005

struct data {
	int u,v,w;
	data(){}
	data(int a,int b,int c):u(a),v(b),w(c){}
	bool operator < (data a) const {
		return w<a.w;
	}
}E[MAXM];

struct edge {
	int next,to,w;
}e[MAXM<<1];

int n,m,K,ecnt,head[MAXN],f[MAXN],fa[MAXN][20],maxe[MAXN][20],dep[MAXN];

int getf(int x) {
	if (f[x]<0) return x;
	return f[x]=getf(f[x]);
}

bool merge(int u,int v) {
	int fu=getf(u),fv=getf(v);
	if (fu==fv) return 0;
	if (f[fu]<f[fv]) {
		f[fu]+=f[fv];
		f[fv]=fu;
	}
	else {
		f[fv]+=f[fu];
		f[fu]=fv;
	}
	return 1;
}

void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].w=w;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].w=w;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

void dfs(int x) {
	for (int i=1;i<=18;i++) {
		fa[x][i]=fa[fa[x][i-1]][i-1];
		maxe[x][i]=max(maxe[x][i-1],maxe[fa[x][i-1]][i-1]);
	}
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=fa[x][0]) {
			fa[e[now].to][0]=x;
			maxe[e[now].to][0]=e[now].w;
			dep[e[now].to]=dep[x]+1;
			dfs(e[now].to);
		}
	}
}

int getLCA(int u,int v) {
	if (dep[u]<dep[v]) swap(u,v);
	int x=dep[u]-dep[v];
	for (int k=18;k>-1;k--) {
		if ((x>>k)&1) {
			u=fa[u][k];
		}
	}
	if (u==v) return u;
	for (int k=18;k>-1;k--) {
		if (fa[u][k]!=fa[v][k]) {
			u=fa[u][k];
			v=fa[v][k];
		}
	}
	return fa[u][0];
}

int query(int x,int anc) {
	int ans=0;
	if (x==anc) return ans;
	int d=dep[x]-dep[anc]-1;
	for (int k=18;k>-1;k--) {
		if ((d>>k)&1) {
			ans=max(ans,maxe[x][k]);
			x=fa[x][k];
		}
	}
	return max(ans,maxe[x][0]);
}

int main() {
	read(n);read(m);read(K);
	for (int i=1;i<=m;i++) {
		read(E[i].u);read(E[i].v);read(E[i].w);
	}
	sort(E+1,E+m+1);
	memset(f,-1,sizeof(f));
	for (int i=1;i<=m;i++) {
		if (merge(E[i].u,E[i].v)) {
			add(E[i].u,E[i].v,E[i].w);
		}
	}
	fa[1][0]=1;
	maxe[1][0]=0;
	dep[1]=1;
	dfs(1);
	for (int i=1,u,v,LCA;i<=K;i++) {
		read(u);read(v);
		LCA=getLCA(u,v);
		printf("%d\n",max(query(u,LCA),query(v,LCA)));
	}
	return 0;
}

