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
int ch=0;
inline void read(LL &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 1000005
int prime[MAXN],phi[MAXN+5],pcnt=0;
LL sum[MAXN+5];
bool notprime[MAXN+5];

void shake() {
	sum[1]=phi[1]=1;
	for (int i=2;i<=MAXN;i++) {
		if (!notprime[i]) prime[++pcnt]=i,phi[i]=i-1;
		for (int j=1;j<=pcnt && i*prime[j]<=MAXN;j++) {
			notprime[i*prime[j]]=1;
			if (i%prime[j]==0) {phi[i*prime[j]]=phi[i]*prime[j];break;}
			else phi[i*prime[j]]=(prime[j]-1)*phi[i];
		}
		sum[i]=sum[i-1]+phi[i];
	}
}
int main() {
	shake();
	LL n,m;
	read(n);read(m);
	LL x=min(n,m);
	LL ans=0;
	for (LL i=1,j;i<=x;i=j+1) {
		j=min(n/(n/i),m/(m/i));
		ans+=(sum[j]-sum[i-1])*(n/i)*(m/i);
	}
	printf("%lld\n",ans*2-LL(n)*m);
	return 0;
}

