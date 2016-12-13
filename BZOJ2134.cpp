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
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

int n,A,B,C,a[10000005];
double ans=0;
int main() {
	read(n);read(A);read(B);read(C);read(a[1]);
	for (int i=2;i<=n;i++) {
		a[i] = int(((long long)a[i-1] * A + B) % 100000001);
	}
	for (int i=1;i<=n;i++) a[i] = a[i] % C + 1;
	a[0]=a[n];
	for (int i=1;i<=n;i++) {
		ans+=1.0/max(a[i-1],a[i]);
	}
	printf("%.3lf\n",ans);
	return 0;
}

