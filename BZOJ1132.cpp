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

#define MAXN 3005

typedef long long LL;
struct point {
	LL x,y;
	point(){}
	point(int _x,int _y):x(_x),y(_y){}
	bool operator < (point a) const {
		if (x!=a.x) return x<a.x;
		else return y<a.y;
	}
}a[MAXN],t[MAXN];

bool cmp(point p,point q) {
	return p.x*q.y-p.y*q.x>0;
}

int n;
LL ans=0;

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%lld%lld",&a[i].x,&a[i].y);
	}
	sort(a+1,a+n+1);
	for (int i=1;i<n;i++) {
		LL sumx=0,sumy=0,cnt=0;
		for (int j=i+1;j<=n;j++) {
			t[++cnt].x=a[j].x-a[i].x,t[cnt].y=a[j].y-a[i].y;
			sumx+=t[cnt].x,sumy+=t[cnt].y;
		}
		sort(t+1,t+cnt+1,cmp);
		for (int j=1;j<=cnt;j++) {
			sumx-=t[j].x,sumy-=t[j].y;
			ans-=sumx*t[j].y-sumy*t[j].x;
		}
	}
	if (ans&1) printf("%lld.5\n",ans>>1);
	else printf("%lld.0\n",ans>>1);
	return 0;
}

