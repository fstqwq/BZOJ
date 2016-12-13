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
#define INF 0x3f3f3f3f
#define MAXN 500005
struct Range {
	int l,r,len;
	bool operator < (Range a) const {
		return len<a.len;
	}
}a[MAXN];
struct node {
	int l,r,lazy,v;
}t[2097152];
int n,m,tem[MAXN<<1],ntem=0,tcnt=0,ans=INF;
int find(int x) {
	int l=1,r=ntem,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (tem[mid]>=x) r=mid;
		else l=mid+1;
	}
	return l;
}
#define lch t[x].l
#define rch t[x].r
int build(int l,int r) {
	int x=++tcnt;
	t[x].lazy=t[x].v=0;
	if (l!=r) {
		int mid=(l+r)>>1;
		lch=build(l,mid);
		rch=build(mid+1,r);
	}
	else lch=rch=0;
	return x;
}

void pushdown(int x) {
	t[lch].v+=t[x].lazy;
	t[lch].lazy+=t[x].lazy;
	t[rch].v+=t[x].lazy;
	t[rch].lazy+=t[x].lazy;
	t[x].lazy=0;
}

void inc(int x,int l,int r,int ql,int qr) {
	if (l==ql && r==qr) {
		t[x].lazy++;
		t[x].v++;
		return;
	}
	if (t[x].lazy) pushdown(x);
	int mid=(l+r)>>1;
	if (ql<=mid) inc(lch,l,mid,ql,min(mid,qr));
	if (qr>mid) inc(rch,mid+1,r,max(mid+1,ql),qr);
	t[x].v=max(t[lch].v,t[rch].v);
}

void dec(int x,int l,int r,int ql,int qr) {
	if (l==ql && r==qr) {
		t[x].lazy--;
		t[x].v--;
		return;
	}
	if (t[x].lazy) pushdown(x);
	int mid=(l+r)>>1;
	if (ql<=mid) dec(lch,l,mid,ql,min(mid,qr));
	if (qr>mid) dec(rch,mid+1,r,max(mid+1,ql),qr);
	t[x].v=max(t[lch].v,t[rch].v);
}

int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++) {
		read(a[i].l);read(a[i].r);a[i].len=a[i].r-a[i].l;
		tem[++ntem]=a[i].l;tem[++ntem]=a[i].r;
	}
	sort(tem+1,tem+ntem+1);
	ntem=int(unique(tem+1,tem+ntem+1)-tem-1);
	for (int i=1;i<=n;i++) {
		a[i].l=find(a[i].l);
		a[i].r=find(a[i].r);
	}
	build(1,ntem);
	sort(a+1,a+n+1);
	int i=1,j=0;
	while (j<n) {
		while (j<n && t[1].v<m) j++,inc(1,1,ntem,a[j].l,a[j].r);
		while (i<=n && t[1].v>=m) ans=min(a[j].len-a[i].len,ans),dec(1,1,ntem,a[i].l,a[i].r),i++;
	}
	if (ans==INF) puts("-1");
	else printf("%d\n",ans);
	return 0;
}

