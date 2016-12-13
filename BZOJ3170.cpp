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
typedef long long LL;
int ch=0;
template <class T> inline void read(T &a) {
	bool f=0;
	while (ch<'0' || ch>'9') {if (ch=='-') f=1;ch=getchar();}
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
	if (f) a=-a;
}
#define MAXN 100005
struct point {
	LL x,y;
	void input() {
		LL tx,ty;
		read(tx);read(ty);
		x=tx+ty;
		y=tx-ty;
	}
}p[MAXN];

int n;
LL xx[MAXN],sumx[MAXN],yy[MAXN],sumy[MAXN],ans=12345678901234567;

int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		p[i].input();
		xx[i]=p[i].x;yy[i]=p[i].y;
	}
	sort(xx+1,xx+n+1);
	sort(yy+1,yy+n+1);
	for (int i=1;i<=n;i++) sumx[i]=sumx[i-1]+xx[i];
	for (int i=1;i<=n;i++) sumy[i]=sumy[i-1]+yy[i];
	for (int i=1;i<=n;i++) {
		LL ret=0;
		int px=int(lower_bound(xx+1,xx+n+1,p[i].x)-xx-1);
		ret+=p[i].x*px-sumx[px]+sumx[n]-sumx[px]-(n-px)*p[i].x;
		int py=int(lower_bound(yy+1,yy+n+1,p[i].y)-yy-1);
		ret+=p[i].y*py-sumy[py]+sumy[n]-sumy[py]-(n-py)*p[i].y;
		ans=min(ans,ret);
	}
	printf("%lld\n",ans>>1);
	return 0;
}

