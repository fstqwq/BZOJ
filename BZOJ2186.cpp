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

#define MAXN 10000000

typedef long long LL;

int T,MOD;
int fac[MAXN+5],inv[MAXN+5],ans[MAXN+5];
int prime[1000005],pcnt=0;
bool notprime[MAXN+5];

void exgcd(int a,int b,int &x,int &y) {
	if (b==0) {
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	int t=x;
	x=y;
	y=t-a/b*y;
}

int getinv(int a) {
	int x,y;
	exgcd(a,MOD,x,y);
	x%=MOD;
	if (x<0) x+=MOD;
	return x;
}

void init() {
	fac[1]=1;
	for (int i=2;i<=MAXN;i++) fac[i]=int(((LL)fac[i-1]*i)%MOD);
	for (int i=2;i<=MAXN;i++) {
		if (!notprime[i]) {
			prime[++pcnt]=i;
			inv[i]=getinv(i);
		}
		for (int j=1;prime[j]*i<=MAXN && j<=pcnt;j++) {
			notprime[prime[j]*i]=1;
			if (i%prime[j]==0) break;
		}
	}
	ans[1]=1;
	for (int i=2;i<=MAXN;i++) {
		if (notprime[i]) ans[i]=ans[i-1];
		else {
			ans[i]=int(((((LL)ans[i-1]*(i-1))%MOD)*inv[i])%MOD);
		}
	}
}


int main() {
	scanf("%d%d",&T,&MOD);
	init();
	while (T--) {
		int n,m;
		scanf("%d%d",&n,&m);
		printf("%d\n",int((LL(fac[n])*ans[m])%MOD));
	}
	return 0;
}

