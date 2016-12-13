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

struct query {
	int x,id,p,k,f;
	query(){}
	query(int a,int b,int c,int d,int e):x(a),id(b),p(c),k(d),f(e){}
	bool operator < (query a) const {
		return x<a.x;
	}
}q[MAXN<<1];

int n,m,qcnt=0;
int a[MAXN];
int rec[105][105],tot[MAXN],ans[MAXN];

int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	for (int i=1,l,r,p,k;i<=m;i++) {
		read(l);read(r);read(p);read(k);
		if (l>1) q[++qcnt]=query(l-1,i,p,k,-1);
		q[++qcnt]=query(r,i,p,k,1);
	}
	sort(q+1,q+qcnt+1);
	int now=1;
	for (int i=1;i<=n;i++) {
		tot[a[i]]++;
		for (int j=1;j<=100;j++) rec[j][a[i]%j]++;
		while (now<=qcnt && q[now].x==i) {
			int f=q[now].f,ret=0;
			int p=q[now].p,k=q[now].k;
			if (p>100) {
				for (int w=k;w<=10001;w+=p) {
					ret+=tot[w];
				}
			}
			else {
				ret=rec[p][k];
			}
			ans[q[now].id]+=f*ret;
			now++;
		}
	}
	for (int i=1;i<=m;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}

