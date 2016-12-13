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
int ch=0;
inline void read(int &a) {
	bool f=0;
	a=0;
	while (ch<'0' || ch>'9') {if (ch=='-') f=1;ch=getchar();}
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
	if (f) a=-a;
}
typedef long long LL;
int n,X;

int main() {
	read(n);read(X);
	LL l=0,r=0,p=0;
	for (int i=1,to,L,R;i<=n;i++) {
		read(to);read(L);read(R);
		l=max(LL(L+1),l-to+p);
		r=min(LL(R-1),r+to-p);
		p=to;
		if (p&1) {
			if (!(l&1)) l++;
			if (!(r&1)) r--;
		}
		else {
			if (l&1) l++;
			if (r&1) r--;
		}
		if (l>r) {puts("NIE");return 0;}
	}
	l-=X-p;
	printf("%lld\n",(l+X)>>1);
	return 0;
}

