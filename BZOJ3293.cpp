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
#define MAXN 100005

long long n,sum;
long long a[MAXN],c[MAXN];

int main() {
	scanf("%lld",&n);
	for (int i=1;i<=n;i++) {
		scanf("%lld",a+i);
		sum+=a[i];
	}
	long long avr=sum/n;
	for (int i=2;i<=n;i++) {
		c[i]=c[i-1]+a[i]-avr;
	}
	sort(c+1,c+n+1);
	long long mid=c[(n+1)/2];
	long long ans=0;
	for (int i=1;i<=n;i++) {
		ans+=abs(c[i]-mid);
	}
	printf("%lld\n",ans);
	return 0;
}

