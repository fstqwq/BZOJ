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

#define MAXN 205

struct point {
	int x,y;
}p[MAXN];

int n,ans=0,cnt=0;
double k[MAXN*MAXN];

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&p[i].x,&p[i].y);
	}
	for (int i=1;i<=n;i++) {
		for (int j=i+1;j<=n;j++) {
			if (p[i].x==p[j].x) {
				ans=1;
			}
			else {
				k[++cnt]=double(p[i].y-p[j].y)/double(p[i].x-p[j].x);
			}
		}
	}
	sort(k+1,k+cnt+1);
	k[0]=k[1]-1;
	for (int i=1;i<=cnt;i++) {
		if (k[i]-k[i-1]>10e-8) ans++;
	}
	printf("%d\n",ans);
	return 0;
}

