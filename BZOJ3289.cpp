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
#define MAXN 50005
int n,sqn,m;
int a[MAXN];
LL ans[MAXN],nowans=0;
struct data {
	int l,r,x;
	bool operator < (data q) const {
		if (l/sqn==q.l/sqn) return r<q.r;
		else return l<q.l;
	}
}q[MAXN];

struct lsh {
	int x,v;
	bool operator < (lsh d) const {
		return v<d.v;
	}
}rr[MAXN];

#define s 65536
int t[s<<1];
int query(int l,int r) {
	int ret=0;
	for (l+=s-1,r+=s+1;l^r^1;l>>=1,r>>=1) {
		if (!(l&1)) ret+=t[l^1];
		if (r&1) ret+=t[r^1];
	}
	return ret;
}
void update(int x) {
	for (x+=s;x;x>>=1) t[x]++;
}
void del(int x) {
	for (x+=s;x;x>>=1) t[x]--;
}
int main() {
	read(n);
	sqn=(int)sqrt(n)+1;
	for (int i=1;i<=n;i++) {
		read(rr[i].v);rr[i].x=i;
	}
	sort(rr+1,rr+n+1);
	a[rr[1].x]=1;
	for (int i=2,now=1;i<=n;i++) {
		if (rr[i].v!=rr[i-1].v) now++;
		a[rr[i].x]=now;
	}
	read(m);
	for (int i=1;i<=m;i++) {
		read(q[i].l);read(q[i].r);q[i].x=i;
	}
	sort(q+1,q+m+1);
	for (int i=1,l=1,r=0;i<=m;i++) {
		while (l<q[i].l) nowans-=query(1,a[l]-1),del(a[l]),l++;
		while (l>q[i].l) l--,nowans+=query(1,a[l]-1),update(a[l]);
		while (r<q[i].r) r++,nowans+=query(a[r]+1,n),update(a[r]);
		while (r>q[i].r) nowans-=query(a[r]+1,n),del(a[r]),r--;
		ans[q[i].x]=nowans;
	}
	for (int i=1;i<=m;i++) {
		printf("%lld\n",ans[i]);
	}
	return 0;
}

