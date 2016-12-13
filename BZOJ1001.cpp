/*This is a source code from FirstLast*/
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

#define s 65536

typedef unsigned int ui;

ui n,t[s<<1],full[s<<1],sum[s<<1],lazy[s<<1];
int L[s<<1],R[s<<1],M[s<<1];
int ch;
inline void read(ui &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') ch=getchar();
}

inline void init() {
	sum[0]=0;
	for (ui i=s,j=1;j<=s;j++) {
		L[i]=R[i]=M[i]=j;
		full[i]=j;
		sum[j]=sum[j-1]+j;
	}
	for (ui i=s-1;i;i--) {
		full[i]=full[i<<1]+full[(i<<1)|1];
		L[i]=L[i<<1];
		M[i]=R[i<<1];
		R[i]=R[(i<<1)|1];
	}
}

inline void pushdown(int x) {
	if (x==1) {
		t[x<<1]=t[(x<<1)|1]=full[x<<1];
	}
	else {
		t[x<<1]=t[(x<<1)|1]=0;
	}
	lazy[x<<1]=lazy[(x<<1)|1]=lazy[x];
}

void fill(int x,int l,int r) {
	if (L[x]==l && R[x]==r) {
		t[x]=full[x];
		lazy[x]=1;
		return;
	}
	if (lazy[x]) pushdown(x);
	lazy[x]=0;
	int mid=M[x];
	if (l<=mid) fill(x<<1,l,min(mid,r));
	if (r>mid) fill((x<<1)|1,max(mid+1,l),r);
	t[x]=t[x<<1]+t[(x<<1)|1];
}

void clear(int x,int l,int r) {
	if (L[x]==l && R[x]==r) {
		t[x]=0;
		lazy[x]=-1;
		return;
	}
	if (lazy[x]) pushdown(x);
	lazy[x]=0;
	int mid=M[x];
	if (l<=mid) clear(x<<1,l,min(mid,r));
	if (r>mid) clear((x<<1)|1,max(mid+1,l),r);
	t[x]=t[x<<1]+t[(x<<1)|1];
}

ui query(int x,int l,int r) {
	if (lazy[x]) {
		if (x==1) {
			return sum[r]-sum[l-1];
		}
		else {
			return 0;
		}
	}
	if (L[x]==l && R[x]==r) {
		return t[x];
	}
	if (lazy[x]) pushdown(x);
	int mid=M[x];
	ui ret=0;
	if (l<=mid) ret=query(x<<1,l,min(mid,r));
	if (r>mid) ret=ret+query((x<<1)|1,max(mid+1,l),r);
	return ret;
}

int main() {
	init();
	read(n);
	ui op,l,r;
	for (ui i=1;i<=n;i++) {
		read(op);read(l);read(r);
		if (op) {
			if (op==1) {
				fill(1,l,r);
			}
			else {
				clear(1,l,r);
			}
		}
		else {
			printf("%u\n",query(1,l,r));
		}
	}
	return 0;
}
