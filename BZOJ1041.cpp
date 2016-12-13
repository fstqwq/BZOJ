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

LL r,rr,sqrt_rr,tot;

LL gcd(LL a,LL b) {
	if (b) return gcd(b,a%b);
	else return a;
}

inline bool check(LL a,LL b) {
	if (gcd(a,b)==1 && a!=b) return 1;
	else return 0;
}

int main() {
	scanf("%lld",&r);
	rr=2*r;
	sqrt_rr=LL(sqrt(rr));
	for (LL d=1;d<=sqrt_rr;d++) {
		if (rr%d==0) {
			LL lim=LL(sqrt(rr/(2*d)));
			for (LL a=1;a<=lim;a++) {
				LL b=(LL)sqrt(rr/d-a*a);
				if (a*a+b*b==rr/d && check(a,b)) tot++;
			}
			if (d*d!=rr) {
				lim=LL(sqrt(d/2));
				for (LL a=1;a<=lim;a++) {
					LL b=LL(sqrt(d-a*a));
					if (a*a+b*b==d && check(a,b)) tot++;
				}
			}
		}
	}
	tot++;
	printf("%lld\n",tot*4);
	return 0;
}

