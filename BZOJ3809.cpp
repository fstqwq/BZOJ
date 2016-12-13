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
#define MAXN 100005
#define MAXM 1000005

int n,sqn,m;
int a[MAXN],ans[MAXM],cnt[MAXN],blo[MAXN],bloans[MAXN],L[MAXN],R[MAXN];

struct qury {
	int l,r,a,b,x;
	bool operator < (qury q) const {
		if (blo[l]==blo[q.l]) return r<q.r;
		else return l<q.l;
	}
}q[MAXM];

inline int query(int l,int r) {
	int ret=0;
	if (blo[r]-blo[l]<2) {
		for (int i=l;i<=r;i++) {
			if (cnt[i]) ret++;
		}
	}
	else {
		int x=R[blo[l]];
		for (int i=l;i<=x;i++) if (cnt[i]) ret++;
		x=blo[r];
		for (int i=blo[l]+1;i<x;i++) ret+=bloans[i];
		for (int i=L[x];i<=r;i++) if (cnt[i]) ret++;
	}
	return ret;
}

inline void update(int x) {
	if (!cnt[a[x]]) bloans[blo[a[x]]]++;
	cnt[a[x]]++;
}

inline void del(int x) {
	cnt[a[x]]--;
	if (!cnt[a[x]]) bloans[blo[a[x]]]--; 
}

int main() {
	read(n);read(m);
	sqn=(int)sqrt(n)+1;
	for (int i=1;i<=n;i++) {
		blo[i]=(i-1)/sqn+1;
		if (!L[blo[i]]) L[blo[i]]=i;
		R[blo[i]]=i;
	}
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	for (int i=1;i<=m;i++) {
		read(q[i].l);read(q[i].r);read(q[i].a);read(q[i].b);q[i].x=i;
	}
	sort(q+1,q+m+1);
	for (int i=1,l=1,r=0;i<=m;i++) {
		while (l>q[i].l) update(--l);
		while (l<q[i].l) del(l++);
		while (r>q[i].r) del(r--);
		while (r<q[i].r) update(++r);
		ans[q[i].x]=query(q[i].a,q[i].b);
	}
	for (int i=1;i<=m;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}

