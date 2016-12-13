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
LL gcd(LL a,LL b) {
	if (b) return gcd(b,a%b);
	else return a;
}

#define MAXN 50005

int n,sqn,m;
int a[MAXN],cnt[MAXN];

struct query {
	int l,r,x;
	bool operator < (query z) const {
		if (l/sqn==z.l/sqn) return r<z.r;
		else return l<z.l;
	}
}q[MAXN];

LL ans=0,ansa[MAXN],ansb[MAXN];

void update(int x) {
	ans+=cnt[a[x]]*2+1;
	cnt[a[x]]++;
}
void del(int x) {
	cnt[a[x]]--;
	ans-=cnt[a[x]]*2+1;
}

int main() {
	read(n);read(m);
	sqn=(int)sqrt(n)+1;
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	for (int i=1;i<=m;i++) {
		read(q[i].l);read(q[i].r);q[i].x=i;
	}
	sort(q+1,q+m+1);
	for (int i=1,l=1,r=0;i<=m;i++) {
		while (r<q[i].r) r++,update(r);
		while (r>q[i].r) del(r),r--;
		while (l<q[i].l) del(l),l++;
		while (l>q[i].l) l--,update(l);
		LL x=ans-(r-l+1),y=LL(r-l+1)*LL(r-l);
		if (x!=0) {
			LL g=gcd(x,y);
			x/=g,y/=g;
		}
		else y=1;
		ansa[q[i].x]=x,ansb[q[i].x]=y;
	}
	for (int i=1;i<=m;i++) {
		printf("%lld/%lld\n",ansa[i],ansb[i]);
	}
	return 0;
}

