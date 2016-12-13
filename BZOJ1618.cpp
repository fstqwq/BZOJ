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
#define MAXD 50005
int n,h;
int dp[MAXD];

inline void update(int x,int c) {
	for (int i=0;i<h;i++) {
		dp[min(i+x,h)]=min(dp[min(i+x,h)],dp[i]+c);
	}
}

int main() {
	read(n);read(h);
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for (int i=1,p,c;i<=n;i++) {
		read(p);read(c);
		update(p,c);
	}
	printf("%d\n",dp[h]);
	return 0;
}

