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
#define MAXN 10005
struct qqq {
	int L,R;
	bool operator < (qqq a) const {
		if (L!=a.L) return L<a.L;
		else return R<a.R;
	}
}q[MAXN];

int n,fun,h,m,d[MAXN];

int main() {
	read(n);read(fun);read(h);read(m);
	for (int i=1;i<=m;i++) {
		read(q[i].L);read(q[i].R);
		if (q[i].L>q[i].R) swap(q[i].L,q[i].R);
	}
	sort(q+1,q+m+1);
	q[0].L=q[0].R=-1;
	for (int i=1;i<=m;i++) {
		if (q[i].L==q[i].R) continue;
		if (q[i].L==q[i-1].L && q[i].R==q[i-1].R) continue;
		d[q[i].L+1]--;d[q[i].R]++;
	}
	int now=h;
	for (int i=1;i<=n;i++) {
		now+=d[i];
		printf("%d\n",now);
	}
	return 0;
}

