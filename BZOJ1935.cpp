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

struct point {
	int x,y;
	bool operator < (point a) const {
		return x<a.x;
	}
}p[MAXN];

struct data {
	int x,l,r,v,id;
	data(){}
	data(int a,int b,int c,int d,int e):x(a),l(b),r(c),v(d),id(e){}
	bool operator < (data a) const {
		return x<a.x;
	}
}q[MAXN<<1];

int n,m,qcnt=0,temx[MAXN],temy[MAXN],cntx=0,cnty=0;
int ans[MAXN];

int lessx(int x) {
	int l=0,r=cntx,mid;
	while (l<r) {
		mid=(l+r+1)>>1;
		if (temx[mid]<x) l=mid;
		else r=mid-1;
	}
	return l;
}

int leqx(int x) {
	int l=0,r=cntx,mid;
	while (l<r) {
		mid=(l+r+1)>>1;
		if (temx[mid]<=x) l=mid;
		else r=mid-1;
	}
	return l;
}

int geqy(int x) {
	int l=0,r=cnty,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (temy[mid]>=x) r=mid;
		else l=mid+1;
	}
	return l;
}

int leqy(int x) {
	int l=0,r=cnty,mid;
	while (l<r) {
		mid=(l+r+1)>>1;
		if (temy[mid]<=x) l=mid;
		else r=mid-1;
	}
	return l;
}

#define s 524288
int t[s<<1];

void update(int x) {
	for (x+=s;x;x>>=1) t[x]++;
}

int query(int l,int r) {
	int ret=0;
	for (l+=s-1,r+=s+1;l^r^1;l>>=1,r>>=1) {
		if ((l&1)^1) ret+=t[l^1];
		if (r&1) ret+=t[r^1];
	}
	return ret;
}

int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++) {
		read(p[i].x);read(p[i].y);
		temx[i]=p[i].x;
		temy[i]=p[i].y;
	}
	sort(p+1,p+n+1);
	sort(temx+1,temx+n+1);
	sort(temy+1,temy+n+1);
	cntx=int(unique(temx+1,temx+n+1)-temx);
	cnty=int(unique(temy+1,temy+n+1)-temy);
	temx[0]=-1,temx[cntx]=10000001;
	temy[0]=-1,temy[cnty]=10000001;
	for (int i=1,a,b,c,d;i<=m;i++) {
		read(a);read(b);read(c);read(d);
		a=lessx(a),c=leqx(c);
		b=geqy(b),d=leqy(d);
		q[++qcnt]=data(a,b,d,-1,i);
		q[++qcnt]=data(c,b,d,1,i);
	}
	sort(q+1,q+qcnt+1);
	int qpos=1,ppos=1;
	while (qpos<=qcnt && q[qpos].x==0) qpos++;
	for (int i=1;i<=cntx;i++) {
		while (ppos<=n && p[ppos].x==temx[i]) update(leqy(p[ppos++].y));
		while (qpos<=qcnt && q[qpos].x==i) {
			ans[q[qpos].id]+=q[qpos].v*query(q[qpos].l,q[qpos].r);
			qpos++;
		}
	}
	for (int i=1;i<=m;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}

