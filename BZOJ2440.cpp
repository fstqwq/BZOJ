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
#define MAXN 1000000
int T,K;
int prime[MAXN>>2],mu[MAXN+5],pcnt=0;
bool notprime[MAXN+5];

void shake() {
	mu[1]=1;
	for (int i=2;i<=MAXN;i++) {
		if (!notprime[i]) prime[++pcnt]=i,mu[i]=-1;
		for (int j=1;j<=pcnt && i*prime[j]<=MAXN;j++) {
			if (i%prime[j]) {
				notprime[i*prime[j]]=1;
				mu[i*prime[j]]=mu[i]*mu[prime[j]];
			}
			else {
				notprime[i*prime[j]]=1;
				mu[i*prime[j]]=0;
				break;
			}
		}
	}
}

bool check(LL mid) {
	LL ans=0;
	for (int i=1,ta=int(sqrt(mid));i<=ta;i++) {
		ans+=mu[i]*(mid/i/i);
	}
	return ans>=K;
}
int main() {
	shake();
	scanf("%d",&T);
	for (int i=1;i<=T;i++) {
		scanf("%d",&K);
		LL l=1,r=K*2+1,mid;
		while (l<r) {
			mid=(l+r)>>1;
			if (check(mid)) r=mid;
			else l=mid+1;
		}
		printf("%d\n",l);
	}

	return 0;
}

