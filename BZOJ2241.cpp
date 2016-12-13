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
int ans=0x7fffffff,m,n;
int a[105][105],sum[105][105];

void check(int x,int y) {
	int ret=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) sum[i][j]=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) {
		sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		int xx=max(0,i-x),yy=max(0,j-y);
		int v=a[i][j]-(sum[i][j]-sum[xx][j]-sum[i][yy]+sum[xx][yy]);
		if (v<0) return;
		ret+=v;sum[i][j]+=v;
	}
	ans=min(ret,ans);
}

int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) read(a[i][j]);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) check(i,j);	
	printf("%d\n",ans);
	return 0;
}

