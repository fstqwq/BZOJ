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
int n;
struct cow {
	int t,d;
	bool operator < (cow a) const {
		return t*a.d<d*a.t;
	}
}a[MAXN];

long long ans=0;

int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		read(a[i].t);read(a[i].d);
	}
	sort(a+1,a+n+1);
	long long nowt=0;
	for (int i=1;i<=n;i++) {
		ans+=nowt*a[i].d;
		nowt+=2*a[i].t;
	}
	printf("%lld\n",ans);
	return 0;
}

