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
	while (ch>='0'&&ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
inline void readpp(bool &a) {
	while (ch!='.' && ch!='*') ch=getchar();
	a=(ch=='.');
	ch=getchar();
}
int n,m,T,Sx,Sy,Tx,Ty;
int dp[20][105][105];
bool map[105][105];
int main() {
	read(n);read(m);read(T);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			readpp(map[i][j]);
		}
	}
	read(Sx);read(Sy);read(Tx);read(Ty);
	dp[0][Sx][Sy]=1;
	for (int t=1;t<=T;t++) {
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++) {
				if (map[i][j]) dp[t][i][j]=dp[t-1][i-1][j]+dp[t-1][i+1][j]+dp[t-1][i][j-1]+dp[t-1][i][j+1];
			}
	}
	printf("%d\n",dp[T][Tx][Ty]);
	return 0;
}

