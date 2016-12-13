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

int n;
struct delta {
	int x,pos;
	bool operator < (delta a) const {
		return pos<a.pos;
	}
}a[100005];
int cnt=0;
int main() {
	read(n);
	for (int i=1,l,r;i<=n;i++) {
		read(l);read(r);
		a[++cnt].pos=l;a[cnt].x=1;
		a[++cnt].pos=r+1;a[cnt].x=-1;
	}
	sort(a+1,a+cnt+1);
	int now=0,ans=0;
	for (int i=1;i<=cnt;) {
		int nowp=a[i].pos;
		while (i<=cnt && a[i].pos==nowp) now+=a[i++].x;
		ans=max(ans,now);
	}
	printf("%d\n",ans);
	return 0;
}

