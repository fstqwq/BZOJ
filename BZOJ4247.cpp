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
	bool f=0;
	while (ch<'0' || ch>'9') {if (ch=='-') f=1;ch=getchar();}
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
	if (f) a=-a;
}
#define MAXN 2005
#define INF 2012345678
struct Obj {
	int v,g;
	bool operator < (Obj a) const {
		return g>a.g;
	}
}a[MAXN];

int n,f[MAXN];

int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		read(a[i].g);read(a[i].v);
	}
	sort(a+1,a+n+1);
	for (int i=0;i<=n;i++) f[i]=-INF;
	f[1]=0;
	for (int i=1;i<=n;i++) {
		if (a[i].g) {
			for (int j=n;j>=1;j--) f[min(n,j+a[i].g-1)]=max(f[min(n,j+a[i].g-1)],f[j]+a[i].v);
		}
		else {
			for (int j=0;j<n;j++) f[j]=max(f[j],f[j+1]+a[i].v);
		}
	}
	int ans=0;
	for (int i=0;i<=n;i++) ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}

