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
#include <bitset>
using namespace std;
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

int n,bg,ml;
int c[55];
bitset<1005> dp[55];

int main() {
	read(n);read(bg);read(ml);
	dp[0].reset();
	dp[0][bg]=1;
	for (int i=1;i<=n;i++) {
		read(c[i]);
		dp[i].reset();
		dp[i]|=dp[i-1]<<c[i];
		dp[i]|=dp[i-1]>>c[i];
		for (int j=ml+1;j<1005;j++) dp[i][j]=0;
	}
	int ans=-1;
	for (int i=0;i<=ml;i++) if (dp[n][i]) ans=i;
	printf("%d\n",ans);
	return 0;
}

