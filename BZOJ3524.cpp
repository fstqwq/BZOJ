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
#define MAXN 500005
struct node {
	int l,r,v;
}t[MAXN<<5];
int n,m,tcnt=0,rt[MAXN];

int update(int x,int l,int r,int v) {
	int now=++tcnt;
	t[now]=t[x];
	t[now].v++;
	if (l!=r) {
		int mid=(l+r)>>1;
		if (v<=mid) t[now].l=update(t[x].l,l,mid,v);
		else t[now].r=update(t[x].r,mid+1,r,v);
	}
	return now;
}

int kth(int rx,int lx,int l,int r,int p) {
	if (l==r) return l;
	int mid=(l+r)>>1,lv=t[t[rx].l].v-t[t[lx].l].v;
	if (lv>=p) return kth(t[rx].l,t[lx].l,l,mid,p);
	else return kth(t[rx].r,t[lx].r,mid+1,r,p-lv);
}
int query(int rx,int lx,int l,int r,int p) {
	if (l==r) return t[rx].v-t[lx].v;
	int mid=(l+r)>>1;
	if (p<=mid) return query(t[rx].l,t[lx].l,l,mid,p);
	else return query(t[rx].r,t[lx].r,mid+1,r,p);
}

int main() {
	read(n);read(m);
	for (int i=1,a;i<=n;i++) {
		read(a);
		rt[i]=update(rt[i-1],1,n,a);
	}
	for (int i=1,l,r;i<=m;i++) {
		read(l);read(r);
		int mid=(r-l+2)>>1,ret=kth(rt[r],rt[l-1],1,n,mid);
		if (query(rt[r],rt[l-1],1,n,ret)>((r-l+1)>>1)) printf("%d\n",ret);
		else puts("0");
	}
	return 0;
}

