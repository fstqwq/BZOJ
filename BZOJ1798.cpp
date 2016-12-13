#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;
typedef long long LL;
#define MAXN 100005
int n,m,tcnt=0;
LL MOD;
int a[MAXN];
struct node {
	int l,r;
	LL v,mul,add;
}t[262144];
#define lch t[now].l
#define rch t[now].r
int build(int l,int r) {
	int now=++tcnt;
	t[now].mul=1;
	if (l!=r) {
		int mid=(l+r)>>1;
		lch=build(l,mid);
		rch=build(mid+1,r);
		t[now].v=(t[lch].v+t[rch].v)%MOD;
	}
	else {
		scanf("%lld",&t[now].v);
		t[now].v%=MOD;
	}
	return now;
}

void pushdown(int now,int lsiz,int rsiz) {
	if (t[now].mul!=1) {
		t[lch].add=(t[lch].add*t[now].mul)%MOD;
		t[rch].add=(t[rch].add*t[now].mul)%MOD;
		t[lch].mul=(t[lch].mul*t[now].mul)%MOD;
		t[rch].mul=(t[rch].mul*t[now].mul)%MOD;
		t[lch].v=(t[lch].v*t[now].mul)%MOD;
		t[rch].v=(t[rch].v*t[now].mul)%MOD;
		t[now].mul=1;
	}
	if (t[now].add) {
		t[lch].add+=t[now].add;
		t[rch].add+=t[now].add;
		t[lch].v=(t[lch].v+t[now].add*lsiz)%MOD;
		t[rch].v=(t[rch].v+t[now].add*rsiz)%MOD;
		t[now].add=0;
	}
}

void update_mul(int now,int l,int r,int ql,int qr,LL v) {
	if (l==ql && r==qr) {
		t[now].mul=(t[now].mul*v)%MOD;
		t[now].add=(t[now].add*v)%MOD;
		t[now].v=(t[now].v*v)%MOD;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(now,mid-l+1,r-mid);
	if (ql<=mid) update_mul(lch,l,mid,ql,min(mid,qr),v);
	if (qr>mid) update_mul(rch,mid+1,r,max(mid+1,ql),qr,v);
	t[now].v=(t[lch].v+t[rch].v)%MOD;
}


void update_add(int now,int l,int r,int ql,int qr,LL v) {
	if (l==ql && r==qr) {
		t[now].add=(t[now].add+v)%MOD;
		t[now].v=(t[now].v+(r-l+1)*v)%MOD;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(now,mid-l+1,r-mid);
	if (ql<=mid) update_add(lch,l,mid,ql,min(mid,qr),v);
	if (qr>mid) update_add(rch,mid+1,r,max(mid+1,ql),qr,v);
	t[now].v=(t[lch].v+t[rch].v)%MOD;
}

LL query(int now,int l,int r,int ql,int qr) {
	if (l==ql && r==qr) return t[now].v;
	LL ret=0;
	int mid=(l+r)>>1;
	pushdown(now,mid-l+1,r-mid);
	if (ql<=mid) ret+=query(lch,l,mid,ql,min(mid,qr));
	if (qr>mid) ret+=query(rch,mid+1,r,max(ql,mid+1),qr);
	return ret%MOD;
}

int main() {
	scanf("%d%lld",&n,&MOD);
	build(1,n);
	scanf("%d",&m);
	for (int i=1,op,x,y;i<=m;i++) {
		LL k;
		scanf("%d%d%d",&op,&x,&y);
		if (op==2) {
			scanf("%lld",&k);
			update_add(1,1,n,x,y,k%MOD);
		}
		else if (op==3){
			printf("%lld\n",query(1,1,n,x,y));
		}
		else {
			scanf("%lld",&k);
			update_mul(1,1,n,x,y,k%MOD);
		}
	}
	return 0;
}

