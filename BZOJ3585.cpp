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

int n,sqn,Q;
int a[MAXN],cnt[MAXN],ans[MAXN],nowans=0;
struct query {
	int l,r,id;
	bool operator < (query q) const {
		if (l/sqn==q.l/sqn) return r<q.r;
		else return l<q.l;
	}
}q[MAXN];

void add(int x) {
	if (x>n) return;
	cnt[x]++;
	while (cnt[nowans]) nowans++; 
}
void del(int x) {
	if (x>n) return;
	cnt[x]--;
	if (!cnt[x] && nowans>x) nowans=x;
}

int main() {
	read(n);read(Q);
	sqn=int(sqrt(n))+1;
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	for (int i=1;i<=Q;i++) {
		read(q[i].l);read(q[i].r);q[i].id=i;
	}
	sort(q+1,q+Q+1);
	for (int i=1,l=1,r=0;i<=Q;i++) {
		while (r<q[i].r) add(a[++r]);
		while (r>q[i].r) del(a[r--]);
		while (l>q[i].l) add(a[--l]);
		while (l<q[i].l) del(a[l++]);
		ans[q[i].id]=nowans;
	}
	for (int i=1;i<=Q;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}

