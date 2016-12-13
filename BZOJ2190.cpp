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

LL phi(LL x) {
	LL ret=x,sqx=LL(sqrt(x));
	for (LL i=2;i<=sqx;i++) {
		if (x%i==0) {
			ret=ret/i*(i-1);
			while (x%i==0) x/=i;
			sqx=LL(sqrt(x));
		}
	}
	if (x!=1) ret=ret/x*(x-1);
	return ret;
}

LL n,ans=0;

int main() {
	cin>>n;
	if (n<2) puts("0");
	else {
		for (int i=1;i<n;i++) {
			ans+=phi(i);
		}
		cout<<ans*2+1<<endl;
	}
	return 0;
}

