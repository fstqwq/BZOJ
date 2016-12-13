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
#define MAXN 1000005
int n,m,p,q;
int f[MAXN],a[MAXN];
int getf(int x) {
	if (f[x]==x) return x;
	else return f[x]=getf(f[x]);
}
int main() {
	read(n);read(m);read(p);read(q);
	for (int i=n+1;i;i--) f[i]=i;
	for (int i=m;i>=1;i--) {
		int x=(i*p+q)%n+1,y=(i*q+p)%n+1;
		if (x>y) swap(x,y);
		for (int j=getf(x);j<=y;j=getf(j)) {
			a[j]=i;
			f[j]=j+1;
		}
	}
	for (int i=1;i<=n;i++) {
		printf("%d\n",a[i]);
	}
	return 0;
}

