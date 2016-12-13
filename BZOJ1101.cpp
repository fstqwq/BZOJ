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
#define MAXN 50005
typedef long long LL;
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

int n;
int prime[MAXN/5],mu[MAXN+5],pcnt=0;
LL sum[MAXN+5];
bool notprime[MAXN+5];

void shake() {
	sum[1]=mu[1]=1;
	for (int i=2;i<=MAXN;i++) {
		if (!notprime[i]) mu[i]=-1,prime[++pcnt]=i;
		for (int j=1;i*prime[j]<=MAXN && j<=pcnt;j++) {
			notprime[i*prime[j]]=1;
			if (i%prime[j]==0) {mu[i*prime[j]]=0;break;}
			else mu[i*prime[j]]=-mu[i];
		}
		sum[i]=sum[i-1]+mu[i];
	}
}

LL work(int a,int b) {
	int x=min(a,b);
	LL ret=0;
	for (int i=1,j;i<=x;i=j+1) {
		j=min(a/(a/i),b/(b/i));
		ret+=(sum[j]-sum[i-1])*(a/i)*(b/i);
	}
	return ret;
}

int main() {
	shake();
	read(n);
	for (int i=1,a,b,k;i<=n;i++) {
		read(a);read(b);read(k);
		a/=k;b/=k;
		printf("%lld\n",work(a,b));
	}
	return 0;
}

