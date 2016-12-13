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
inline void readop(int &a) {
	while (ch<'A' || ch>'Z') ch=getchar();
	a=int(ch<'D')+int(ch<='D');
}
#define MAXN 10005
#define MAXM 200005
struct Querys {
	int op,u,v,id;
	bool operator < (Querys a) const {
		if (u!=a.u) return u<a.u;
		if (v!=a.v) return v<a.v;
		return id<a.id;
	}
}qq[MAXN];
int n,m,exc[MAXM],f[MAXN],tot=0;

struct Tree_node {
	int l,r,v,head;
}t[524288];

struct Opt_node {
	int next,u,v;
}op[1048576];

struct Reverse {
	int p,v,next;
}sta[2097152];

int tcnt=0,opcnt=0,stacnt=0,A,B;
#define lch t[now].l
#define rch t[now].r
int build(int l,int r) {
	int now=++tcnt;
	if (l!=r) {
		int mid=(l+r)>>1;
		lch=build(l,mid);
		rch=build(mid+1,r);
		t[now].v=t[lch].v+t[rch].v;
	}
	else {
		if (qq[l].op==0) {
			t[now].v=1;
			lch=qq[l].u;
			rch=qq[l].v;
		}
	}
	return now;
}

void add_Exsit(int now,int l,int r,int ql,int qr) {
	if (l==ql && r==qr) {
		op[++opcnt].u=A;
		op[opcnt].v=B;
		op[opcnt].next=t[now].head;
		t[now].head=opcnt;
	}
	int mid=(l+r)>>1;
	if (l<=mid) add_Exsit(lch,l,mid,ql,min(qr,mid));
	if (r>mid) add_Exsit(rch,mid+1,r,max(ql,mid+1),qr);
}

int getf(int x) {
	if (f[x]<0) return x;
	else return getf(f[x]);
}

void merge(int u,int v,int &head) {
	int fu=getf(fu),fv=getf(fv);

}

void dfs(int now,int l,int r) {
	int head=0;
	for (int now=t[now].head;now;now=op[now].next) {
		merge(op[now].u,op[now].v,head);
	}
	if (l==r) {
		if (getf(lch)==getf(rch)) puts("Yes");
		else puts("No");
	}
	for (int now=head;now;now=sta[now].next) {
		f[sta[now].p]=sta[now].v;
	}
}

int main() {
	read(n);read(m);
	for (int i=1,op,u,v;i<=m;i++) {
		readop(qq[i].op);read(qq[i].u);read(qq[i].v);
		qq[i].id=i;
		if (qq[i].u>qq[i].v) swap(qq[i].u,qq[i].v);
	}
	build(1,m);
	sort(qq+1,qq+m+1);
	for (int i=1;i<=m;i++) {
		if (qq[i].u!=qq[i-1].u || qq[i].v!=qq[i-1].v) {
			if (tot && exc[tot]!=-1) {
				A=qq[i-1].u,B=qq[i-1].v;
				add_Exsit(1,m,exc[tot],m);
			}
			tot++;
			exc[tot]=-1;
		}
		if (qq[i].op==2) {
			exc[tot]=qq[i].id;
		}
		else if (qq[i].op){
			A=qq[i].u,B=qq[i].v;
			add_Exsit(1,1,m,exc[tot],qq[i].id);
			exc[tot]=-1;
		}
	}
	if (tot && exc[tot]!=-1) {
		A=qq[m].u,B=qq[m].v;
		add_Exsit(1,1,m,exc[tot],m);
	}
	dfs(1,1,m);
	return 0;
}

