/*This is a source code from FirstLast*/
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

long long t,a,b,x,y;

long long gcd(long long a,long long b) {
	if (b) return gcd(b,a%b);
	return a;
}

inline bool check(long long a,long long b,long long d) {
	return a%d==0 && b%d==0;
}

int main() {
	scanf("%lld",&t);
	for (int i=1;i<=t;i++) {
		scanf("%lld%lld%lld%lld",&a,&b,&x,&y);
		long long  d=gcd(2*a,2*b);
		if (check(x,y,d) || check(x+a,y+b,d) || check(x+b,y+a,d) || check(x+a+b,y+a+b,d))
			puts("Y");
		else puts("N");
	}
	return 0;
}

