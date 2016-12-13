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

long long MOD,n,g,x0,a,c;

long long now[2][2],trans[2][2],temp[2][2];

inline long long exp(long long a,long long b) {
	long long ret=0;
	while (b) {
		if (b&1) {
			ret=(ret+a)%MOD;
		}
		a=(a+a)%MOD;
		b>>=1;
	}
	return ret;
}

inline void fuck(long long a[2][2],long long b[2][2]) {
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++) {
			temp[i][j]=0;
			for (int k=0;k<2;k++) {
				temp[i][j]=(temp[i][j]+exp(a[i][k],b[k][j]))%MOD;
			}
		}
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++) {
			a[i][j]=temp[i][j];
		}
}

inline void quickpower(long long x) {
	while (x) {
		if (x&1) {
			fuck(now,trans);
		}
		fuck(trans,trans);
		x>>=1;
	}
}

int main() {
	cin>>MOD>>a>>c>>x0>>n>>g;
	trans[0][0]=a;
	trans[0][1]=0;
	trans[1][0]=c;
	trans[1][1]=1;
	now[0][0]=1;
	now[1][1]=1;
	quickpower(n);
	cout<<((exp(x0,now[0][0])+now[1][0])%MOD)%g<<endl;
	return 0;
}

