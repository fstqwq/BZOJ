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
int ch;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
inline void read(LL &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MOD 2333
int C[2345][2345],sum[2345][2345];

void init() {
	C[0][0]=sum[0][0]=1;
	for (int i=1;i<=MOD;i++) sum[0][i]=1;
	for (int i=1;i<=MOD;i++) {
		sum[i][0]=C[i][0]=1;
		for (int j=1;j<=i;j++) {
			C[i][j]=C[i-1][j-1]+C[i-1][j];
			if (C[i][j]>=MOD) C[i][j]-=MOD;
		}
		for (int j=1;j<=MOD;j++) {
			sum[i][j]=sum[i][j-1]+C[i][j];
			if (sum[i][j]>=MOD) sum[i][j]-=MOD;
		}
	}
}

int Lucas(LL n,LL k) {
	if (n<k || k<0) return 0;
	if (n<=MOD) return C[n][k];
	return (Lucas(n/MOD,k/MOD)*C[n%MOD][k%MOD])%MOD;
}

int ans(LL n,LL k) {
	if (k<0) return 0;
	return (ans(n/MOD,k/MOD-1)*sum[n%MOD][MOD-1]+Lucas(n/MOD,k/MOD)*sum[n%MOD][k%MOD])%MOD;
}
int main() {
	init();
	int T;
	LL n,k;
	read(T);
	while (T--) {
		read(n);read(k);
		printf("%d\n",ans(n,k));
	}
	return 0;
}

