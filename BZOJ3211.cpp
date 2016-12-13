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
typedef long long LL;
#define MAXN 100005
#define s 131072
int n,m,a[MAXN],tcnt=0;
struct node {
	int l,r,v;
}t[s<<1];
LL sum[s<<1];
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
		t[now].v=a[l]>1;
	}
	return now;
}

void init() {
	for (int i=1;i<=n;i++) {
		sum[s+i]=a[i];
	}
	for (int i=s-1;i;i--) {
		sum[i]=sum[i<<1]+sum[(i<<1)|1];
	}
	build(1,n);
}

LL query(int l,int r) {
	LL ret=0;
	for (l+=s-1,r+=s+1;l^r^1;l>>=1,r>>=1) {
		if (!(l&1)) ret+=sum[l^1];
		if (r&1) ret+=sum[r^1];
	}
	return ret;
}

void dec(int x,int d) {
	for (x+=s;x;x>>=1) sum[x]-=d;
}

void work(int now,int l,int r) {
	if (l==r) {
		int to=int(sqrt(sum[l+s]));
		dec(l,int(sum[l+s])-to);
		if (to<=1) t[now].v=0;
	}
	else {
		int mid=(l+r)>>1;
		if (t[lch].v) work(lch,l,mid);
		if (t[rch].v) work(rch,mid+1,r);
		t[now].v=t[lch].v+t[rch].v;
	}
}

void update(int now,int l,int r,int ql,int qr) {
	if (!t[now].v) return;
	if (l==ql && r==qr) {
		work(now,l,r);
		return;
	}
	int mid=(l+r)>>1;
	if (ql<=mid) update(lch,l,mid,ql,min(qr,mid));
	if (qr>mid) update(rch,mid+1,r,max(ql,mid+1),qr);
	t[now].v=t[lch].v+t[rch].v;
}

int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	init();
	read(m);
	for (int i=1,x,l,r;i<=m;i++) {
		read(x);read(l);read(r);
		if (x==1) {
			printf("%lld\n",query(l,r));
		}
		else {
			update(1,1,n,l,r);
		}
	}
	return 0;
}

