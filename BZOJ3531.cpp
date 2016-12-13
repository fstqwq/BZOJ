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

#define MAXN 100005

int ch;
inline void read(int &a) {
	while (ch>'9' || ch<'0') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

inline int readop() {
	while (ch<'A' || ch>'Z') ch=getchar();
	if (ch=='C') {
		ch=getchar();
		if (ch=='C') return 0;
		else return 1;
	}
	else {
		ch=getchar();
		if (ch=='S') return 2;
		else return 3;
	}
}

const int CW=1,QS=3,QM=4;

struct order {
	int opt,x,y,c,time;
	order(){}
	order(int q,int w,int e,int r,int t):opt(q),x(w),y(e),c(r),time(t){}
	bool operator < (order a) const {
		if (c!=a.c) return c<a.c;
		else return time<a.time;
	}
}op[MAXN*3];

int ans[MAXN*3];

struct edge {
	int next,to;
}e[MAXN<<1];

int n,q,ocnt=0;
int col[MAXN],wei[MAXN],head[MAXN],ecnt=0;

inline void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}


int fa[MAXN],son[MAXN],maxs[MAXN],siz[MAXN],dep[MAXN],top[MAXN],tid[MAXN],dfn=0;

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
			if (siz[v]>maxs[x]) {
				maxs[x]=siz[v];
				son[x]=v;
			}
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
			if (v!=fa[x] && v!=son[x]) {
				link(v,v);
			}
		}
	}
}

#define INF 0x1f1f1f1f
#define s 131072
int tmax[s<<1],tsum[s<<1];

void init() {
	dep[1]=fa[1]=1;
	finds(1);
	link(1,1);
	memset(ans,-1,sizeof(ans));
}

void update(int x,int v) {
	x+=s;
	tmax[x]=tsum[x]=v;
	for (x>>=1;x;x>>=1) {
		tmax[x]=max(tmax[x<<1],tmax[(x<<1)^1]);
		tsum[x]=tsum[x<<1]+tsum[(x<<1)^1];
	}
}

int query_s(int l,int r) {
	int ret=0;
	for (l+=s-1,r+=s+1;l^r^1;l>>=1,r>>=1) {
		if ((l&1)^1) ret+=tsum[l^1];
		if (r&1) ret+=tsum[r^1];
	}
	return ret;
}


int query_m(int l,int r) {
	int ret=0;
	for (l+=s-1,r+=s+1;l^r^1;l>>=1,r>>=1) {
		if ((l&1)^1) ret=max(ret,tmax[l^1]);
		if (r&1) ret=max(ret,tmax[r^1]);
	}
	return ret;
}

int query_sum(int u,int v) {
	int ret=0;
	while (top[u]!=top[v]) {
		if (dep[top[u]]<dep[top[v]]) swap(u,v);
		ret+=query_s(tid[top[u]],tid[u]);
		u=fa[top[u]];
	}
	if (dep[u]>dep[v]) swap(u,v);
	ret+=query_s(tid[u],tid[v]);
	return ret;
}

int query_max(int u,int v) {
	int ret=0;
	while (top[u]!=top[v]) {
		if (dep[top[u]]<dep[top[v]]) swap(u,v);
		ret=max(ret,query_m(tid[top[u]],tid[u]));
		u=fa[top[u]];
	}
	if (dep[u]>dep[v]) swap(u,v);
	ret=max(ret,query_m(tid[u],tid[v]));
	return ret;
}

void work(int st,int ed) {
	for (int i=st;i<=ed;i++) {
		if (op[i].opt==CW) {
			update(tid[op[i].x],op[i].y);
		}
		else if (op[i].opt==QS) {
			ans[op[i].time]=query_sum(op[i].x,op[i].y);
		}
		else {
			ans[op[i].time]=query_max(op[i].x,op[i].y);
		}
	}
	for (int i=st;i<=ed;i++) {
		if (op[i].opt==CW && op[i].y!=0) {
			update(tid[op[i].x],0);
		}
	}
}

int main() {
	read(n);read(q);
	for (int i=1,w,c;i<=n;i++) {
		read(w);read(c);
		col[i]=c;
		wei[i]=w;
		++ocnt;
		op[ocnt]=order(CW,i,w,c,ocnt);
	}
	for (int i=1,u,v;i<n;i++) {
		read(u);read(v);
		add(u,v);
	}
	init();
	for (int i=1,x,y;i<=q;i++) {
		int opt=readop();
		read(x);read(y);
		if (opt==0) {
			++ocnt;
			op[ocnt]=order(CW,x,0,col[x],ocnt);
			col[x]=y;
			++ocnt;
			op[ocnt]=order(CW,x,wei[x],y,ocnt);
		}
		else if (opt==1) {
			wei[x]=y;
			++ocnt;
			op[ocnt]=order(CW,x,y,col[x],ocnt);
		}
		else if (opt==2) {
			++ocnt;
			op[ocnt]=order(QS,x,y,col[x],ocnt);
		}
		else {
			++ocnt;
			op[ocnt]=order(QM,x,y,col[x],ocnt);
		}
	}
	sort(op+1,op+ocnt+1);
	for (int i=1,j;i<=ocnt;i=j) {
		for (j=i+1;j<=ocnt && op[j].c==op[i].c;j++);
		work(i,j-1);
	}
	for (int i=1;i<=ocnt;i++) {
		if (ans[i]!=-1) printf("%d\n",ans[i]);
	}
	return 0;
}

