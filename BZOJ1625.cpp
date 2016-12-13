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

int n,m;
int dp[13000];

int main() {
	read(n);read(m);
	for (int i=1,w,d;i<=n;i++) {
		read(w);read(d);
		for (int j=m;j>=w;j--) {
			dp[j]=max(dp[j],dp[j-w]+d);
		}
	}
	int ans=0;
	for (int i=0;i<=m;i++) {
		ans=max(ans,dp[i]);
	}
	printf("%d\n",ans);
	return 0;
}

