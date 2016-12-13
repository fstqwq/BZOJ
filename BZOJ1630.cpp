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
#define MOD 1000000
int T,A,S,B;
int dp[2][100005],sum[2][100005],N[1005];

int main() {
	read(T);read(A);read(S);read(B);
	for (int i=1,x;i<=A;i++) {
		read(x);
		N[x]++;
	}
	dp[0][0]=1;
	for (int i=0;i<=A;i++) sum[0][i]=1; 
	for (int i=1;i<=T;i++) {
		int now=i&1,prev=now^1;
		sum[now][0]=1;
		dp[now][0]=1;
		for (int j=1;j<=A;j++) {
			if (j>N[i]) dp[now][j]=MOD+sum[prev][j]-sum[prev][j-N[i]-1];
			else dp[now][j]=sum[prev][j];
			if (dp[now][j]>=MOD) dp[now][j]-=MOD;
			sum[now][j]=sum[now][j-1]+dp[now][j];
			if (sum[now][j]>=MOD) sum[now][j]-=MOD;
		}
	}
	int ans=0;
	for (int i=S;i<=B;i++) {
		ans+=dp[T&1][i];
		if (ans>=MOD) ans-=MOD;
	}
	printf("%d\n",ans);
	return 0;
}

