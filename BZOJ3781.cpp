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

int n,sqn,m,k;
int a[MAXN],cnt[MAXN];
struct query {
	int l,r,x;
	bool operator < (query q) const {
		if (l/sqn==q.l/sqn) return r<q.r;
		else return l<q.l;
	}
}q[MAXN];

LL tot=0,ans[MAXN];

void add(int x) {
	tot+=cnt[a[x]]*2+1;
	cnt[a[x]]++;
}
void del(int x) {
	tot-=cnt[a[x]]*2-1;
	cnt[a[x]]--;
}
int main() {
	read(n);read(m);read(k);
	sqn=(int)sqrt(n)+1;
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	for (int i=1;i<=m;i++) {
		read(q[i].l);read(q[i].r);q[i].x=i;
	}
	sort(q+1,q+m+1);
	for (int i=1,l=1,r=0;i<=m;i++) {
		while (l<q[i].l) del(l++);
		while (l>q[i].l) add(--l);
		while (r<q[i].r) add(++r);
		while (r>q[i].r) del(r--);
		ans[q[i].x]=tot;
	}
	for (int i=1;i<=m;i++) {
		printf("%lld\n",ans[i]);
	}
	return 0;
}

