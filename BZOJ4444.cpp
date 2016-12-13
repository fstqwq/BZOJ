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

#define MAXN 200005

struct data {
	int l,r,x;
	bool operator < (data a) const {
		return l<a.l;
	}
}a[MAXN<<1];
int n,m;
int ls[MAXN<<1],fa[MAXN<<1][20],ans[MAXN];

int find(int x) {
	int l=1,r=m,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (ls[mid]>=x) r=mid;
		else l=mid+1;
	}
	return l;
}

int work(int x) {
	int target=x+n,ret=0;
	for (int k=19;k>-1;k--) {
		if (fa[x][k]<target) {
			ret|=1<<k;
			x=fa[x][k];
		}
	}
	return ret+1;
}

int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++) {
		read(a[i].l);read(a[i].r);
		a[i].x=i;
		ls[(i<<1)-1]=a[i].l,ls[i<<1]=a[i].r;
	}
	sort(a+1,a+n+1);
	sort(ls+1,ls+n+n+1);
	m=int(unique(ls+1,ls+n+n+1)-ls-1);
	for (int i=1;i<=n;i++) {
		a[i].l=find(a[i].l);
		a[i].r=find(a[i].r);
		if (a[i].l>a[i].r) a[i].r+=m;
		a[i+n].l=a[i].l+m;a[i+n].r=a[i].r+m;
	}
	for (int i=1,j=1;i<=n;i++) {
		while (a[j+1].l<=a[i].r) j++;
		fa[i][0]=j;
	}
	for (int i=1;i<=n;i++) {
		fa[i+n][0]=min(fa[i][0]+n,n+n+1);
	}
	fa[n+n+1][0]=n+n+1;
	for (int k=1;k<=19;k++) {
		for (int i=1;i<=n+n+1;i++) {
			fa[i][k]=fa[fa[i][k-1]][k-1];
		}
	}
	for (int i=1;i<=n;i++) {
		ans[a[i].x]=work(i);
	}
	for (int i=1;i<=n;i++) {
		printf("%d ",ans[i]);
	}
	return 0;
}

