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
typedef long long LL;
struct opt_ {
	int x,v;
	bool operator < (opt_ a) const {
		return x<a.x;
	}
}op[MAXN*2];

struct node {
	int l,r,cnt;
	LL v;
}t[MAXN<<6];

int m,n,opcnt=0,tcnt=0,pp[MAXN],tem[MAXN],rt[MAXN],ntem;

int find(int x) {
	int l=1,r=ntem,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (tem[mid]>=x) r=mid;
		else l=mid+1;
	}
	return l;
}

int inc_(int x,int l,int r,int p) {
	int now=++tcnt;
	t[now]=t[x];
	t[now].cnt++;
	t[now].v+=tem[p];
	if (l!=r) {
		int mid=(l+r)>>1;
		if (p<=mid) t[now].l=inc_(t[x].l,l,mid,p);
		else t[now].r=inc_(t[x].r,mid+1,r,p);
	}
	return now;
}
int dec_(int x,int l,int r,int p) {
	int now=++tcnt;
	t[now]=t[x];
	t[now].cnt--;
	t[now].v-=tem[p];
	if (l!=r) {
		int mid=(l+r)>>1;
		if (p<=mid) t[now].l=dec_(t[x].l,l,mid,p);
		else t[now].r=dec_(t[x].r,mid+1,r,p);
	}
	return now;
}
LL query(int x,int l,int r,int k) {
	if (l==r) {
		return (LL)k*tem[l];
	}
	int mid=(l+r)>>1,lcnt=t[t[x].l].cnt;
	if (lcnt>=k) {
		return query(t[x].l,l,mid,k);
	}
	else {
		return t[t[x].l].v+query(t[x].r,mid+1,r,k-lcnt);
	}
}

int main() {
	read(m);read(n);
	for (int i=1,s,e;i<=m;i++) {
		read(s);read(e);read(pp[i]);
		tem[i]=pp[i];
		op[++opcnt].x=s;
		op[++opcnt].x=e+1;
	}
	sort(tem+1,tem+m+1);
	ntem=int(unique(tem+1,tem+m+1)-tem-1);
	for (int i=1;i<=m;i++) {
		op[i*2-1].v=op[i*2].v=find(pp[i]);
		op[i*2].v=-op[i*2].v;
	}
	sort(op+1,op+opcnt+1);
	rt[0]=0;
	for (int i=1,j=1;i<=n;i++) {
		int rr=rt[i-1];
		while (j<=opcnt && op[j].x==i) {
			if (op[j].v>0) rr=inc_(rr,1,ntem,op[j].v);
			else rr=dec_(rr,1,ntem,-op[j].v);
			j++;
		}
		rt[i]=rr;
	}
	LL pre=1;
	for (int i=1,x,a,b,c,k;i<=n;i++) {
		read(x);read(a);read(b);read(c);
		k=int(1+(a*pre+b)%c);
		if (k<=t[rt[x]].cnt) pre=query(rt[x],1,ntem,k);
		else pre=t[rt[x]].v;
		printf("%lld\n",pre);
	}
	return 0;
}

