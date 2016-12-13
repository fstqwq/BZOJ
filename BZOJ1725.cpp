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
#define MOD 100000000
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

int n,m;
int st[15],dp[15][400];
int can[400],ccnt=0;

inline void init() {
	int top=1<<m;
	for (int i=0;i<top;i++) {
		if (!(i&(i>>1))) can[++ccnt]=i;
	}
}

int main() {
	read(n);read(m);
	init();
	for (int i=1,x;i<=n;i++) {
		st[i]=0;
		for (int j=1;j<=m;j++) {
			read(x);
			st[i]=(st[i]<<1)|(x^1);
		}
	}
	dp[0][1]=1;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=ccnt;j++) {
			if (!dp[i-1][j]) continue;
			for (int k=1;k<=ccnt;k++) {
				if (!(can[j]&can[k]) && !(can[k]&st[i])) {
					dp[i][k]+=dp[i-1][j];
					if (dp[i][k]>=MOD) dp[i][k]-=MOD;
				}
			}
		}
	}
	int ans=0;
	for (int i=1;i<=ccnt;i++) {
		ans+=dp[n][i];
		if (ans>=MOD) ans-=MOD;
	}
	printf("%d\n",ans);
	return 0;
}

