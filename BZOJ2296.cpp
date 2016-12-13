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
LL ans=1234567890000000;

int main() {
	int t;
	scanf("%d",&t);
	while (t--) {
		LL x;
		scanf("%lld",&x);
		if (!x) puts("-1");
		else printf("%lld\n",(ans/x+1)*x);
	}

	return 0;
}

