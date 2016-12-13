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

LL n,sqn,ans=0;

LL phi(LL x) {
	LL sqx=LL(sqrt(x)),ret=x;
	for (int i=2;i<=sqx;i++) {
		if (x%i==0) {
			ret=ret/i*(i-1);
			while (x%i==0) {
				x/=i;
			}
			sqx=LL(sqrt(x));
		}
	}
	if (x!=1) ret=ret/x*(x-1);
	return ret;
}

int main() {
	cin>>n;
	sqn=LL(sqrt(n));
	for (LL i=1;i<=sqn;i++) {
		if (n%i==0) {
			ans+=i*phi(n/i)+(n/i)*phi(i);
		}
	}
	cout<<ans<<endl;
	return 0;
}

