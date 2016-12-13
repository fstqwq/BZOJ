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

struct cow {
	int w,s;
	bool operator < (cow a) const {
		return w+s<a.w+a.s;
	}
}a[50005];

int n;

int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		read(a[i].w);read(a[i].s);
	}
	sort(a+1,a+n+1);
	int ans=-0x7fffffff,tot=0;
	for (int i=1;i<=n;i++) {
		ans=max(ans,tot-a[i].s);
		tot+=a[i].w;
	}
	printf("%d\n",ans);
	return 0;
}

