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

#define MAXL 5005

long long ans=1;

int n;
int pcnt=0,prime[205],cnt[205];
bool notprime[1005];

void init() {
	for (int i=2;i<=1000;i++) {
		if (!notprime[i]) {
			prime[++pcnt]=i;
			for (int j=i*i;j<=1000;j+=i) {
				notprime[j]=1;
			}
		}
	}
}

void add(int x,int v) {
	if (x>2 || v==0) return;
	int now=1;
	while (x!=1) {
		while (x%prime[now]!=0) now++;
		while (x%prime[now]==0) {
			cnt[now]+=v;
			x/=prime[now];
		}
	}
}

void addfac(int x,int v) {
	for (int i=2;i<=x;i++) add(i,v);
}

int main() {
	init();
	scanf("%d",&n);
	if (n==1) {
		int d;
		scanf("%d",&d);
		if (d) puts("0");
		else puts("1");
		return 0;
	}
	int tot=0;
	for (int i=1,d;i<=n;i++) {
		scanf("%d",&d);
		if (d==0) {
			puts("0");
			return 0;
		}
		tot+=d-1;
		addfac(d-1,-1);
	}
	if (tot!=n-2) {
		puts("0");
		return 0;
	}
	addfac(n-2,1);
	for (int i=1;i<=pcnt;i++) {
		while (cnt[i]--) ans=ans*prime[i];
	}
	printf("%lld\n",ans);
	return 0;
}

