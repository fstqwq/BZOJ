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
LL temp[3][3],n,MOD;
void mul(LL a[3][3],LL b[3][3],LL c[3][3]) {
	for (int i=0;i<3;i++)
		for (int j=0;j<3;j++) {
			temp[i][j]=0;
			for (int k=0;k<3;k++) {
				temp[i][j]=(temp[i][j]+a[i][k]*b[k][j])%MOD;
			}
		}
	for (int i=0;i<3;i++)
		for (int j=0;j<3;j++) {
			c[i][j]=temp[i][j];
		}
}

LL a[3][3],b[3][3];

void work(LL t,LL to) {
	memset(b,0,sizeof(b));
	b[0][0]=t%MOD;b[1][0]=1;b[2][0]=1;
	b[1][1]=1;b[2][1]=1;b[2][2]=1;
	LL y=to-t/10+1;
	while (y) {
		if (y&1) mul(a,b,a);
		mul(b,b,b);
		y>>=1;
	}
}

int main() {
	cin>>n>>MOD;
	LL t=10;
	for (int i=0;i<3;i++) a[i][i]=1;
	while (n>=t) {
		work(t,t-1);
		t=t*10;
	}
	work(t,n);
	cout<<a[2][0]<<endl;
	return 0;
}

