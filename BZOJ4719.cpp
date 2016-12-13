#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 300005
struct edge {
	int next,to;
}e[MAXN<<1];

int n,m,ecnt=0,head[MAXN];
int f[MAXN],fa[MAXN][20],dep[MAXN],w[MAXN],S[MAXN],lca[MAXN],T[MAXN];
struct Query {
	int next,x,v;
}q[MAXN<<1];
int qhead[MAXN],qcnt=0;
int t[MAXN<<1],ans[MAXN];
void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}
void add_query(int p,int v,int x) {
	q[++qcnt].next=qhead[p];
	q[qcnt].x=x;
	q[qcnt].v=v;
	qhead[p]=qcnt;
}
void dfs(int x) {
	fa[x][0]=f[x];
	for (int i=1;i<=19;i++) {
		fa[x][i]=fa[fa[x][i-1]][i-1];
	}
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=f[x]) {
			f[e[now].to]=x;
			dep[e[now].to]=dep[x]+1;
			dfs(e[now].to);
		}
	}
}
void work_1(int x,int ta) {
	int now=0;
	while (x!=ta) {
		if (now==w[x]) ans[x]++;
		now++;
		x=f[x];
	}
	if (now==w[ta]) ans[ta]++;
}
void work_2(int x,int ta,int now) {
	while (x!=ta) {
		if (now==w[x]) ans[x]++;
		now--;
		x=f[x];
	}
}

int getLCA(int u,int v) {
	if (dep[u]<dep[v]) swap(u,v);
	int x=dep[u]-dep[v];
	for (int i=0;x;i++,x>>=1) {
		if (x&1) {
			u=fa[u][i];
		}
	}
	if (u==v) return u;
	for (int i=19;i>-1;i--) {
		if (fa[u][i]!=fa[v][i]) {
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	return fa[u][0];
}

void vio() {
	for (int i=1;i<=m;i++) {
		work_1(S[i],lca[i]);
	}
	for (int i=1;i<=m;i++) {
		work_2(T[i],lca[i],dep[S[i]]-dep[lca[i]]+dep[T[i]]-dep[lca[i]]);
	}
}


void work_1_p1(int x) {
	int xx=w[x]+dep[x];
	ans[x]-=t[xx];
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=fa[x][0]) {
			work_1_p1(e[now].to);
		}
	}
	for (int now=qhead[x];now;now=q[now].next) {
		if (q[now].v==1) t[q[now].x]++;
	}
	ans[x]+=t[xx];
	for (int now=qhead[x];now;now=q[now].next) {
		if (q[now].v==-1) t[q[now].x]--;
	}
}

void work_2_p1(int x) {
	int xx=w[x]-dep[x]+MAXN;
	ans[x]-=t[xx];
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=fa[x][0]) {
			work_2_p1(e[now].to);
		}
	}
	for (int now=qhead[x];now;now=q[now].next) {
		if (q[now].v==1) t[q[now].x]++;
	}
	ans[x]+=t[xx];
	for (int now=qhead[x];now;now=q[now].next) {
		if (q[now].v==-1) t[q[now].x]--;
	}
}


void work_p1() {
	qcnt=0;
	memset(qhead,0,sizeof(qhead));
	for (int i=1;i<=m;i++) {
		add_query(S[i],1,dep[S[i]]);
		add_query(lca[i],-1,dep[S[i]]);
	}
	work_1_p1(1);
	qcnt=0;
	memset(qhead,0,sizeof(qhead));
	for (int i=1;i<=m;i++) {
		add_query(T[i],1,dep[S[i]]-2*dep[lca[i]]+MAXN);
		add_query(lca[i],-1,dep[S[i]]-2*dep[lca[i]]+MAXN);
	}
	work_2_p1(1);
	for (int i=1;i<=m;i++) {
		int num=dep[S[i]]-dep[lca[i]];
		if (w[lca[i]]==num) ans[lca[i]]--;
	}
}

void dfs_p2(int x) {
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=f[x]) {
			dfs_p2(e[now].to);
			t[x]+=t[e[now].to];
		}
	}
	if (dep[x]==w[x]+1) {
		ans[x]=t[x];
	}
}

void work_p2() {
	qcnt=0;
	memset(qhead,0,sizeof(qhead));
	for (int i=1;i<=m;i++) {
		t[T[i]]++;
	}
	dfs_p2(1);
}

int main() {
	read(n);read(m);
	for (int i=1,u,v;i<n;i++) {
		read(u);read(v);
		add(u,v);
	}
	for (int i=1;i<=n;i++) {
		read(w[i]);
	}
	f[1]=1;
	dep[1]=1;
	dfs(1);
	for (int i=1;i<=m;i++) {
		read(S[i]);read(T[i]);
		lca[i]=getLCA(S[i],T[i]);
	}
	work_p1();	
	for (int i=1;i<n;i++) {
		printf("%d ",ans[i]);
	}
	printf("%d",ans[n]);
	return 0;
}


