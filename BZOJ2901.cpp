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
int ch=0;
template <class T> inline void read(T &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 2005
int n,m;
LL a[MAXN][MAXN],b[MAXN][MAXN];

int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) {
			read(a[i][j]);a[i][j]+=a[i-1][j];
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) {
			read(b[i][j]);b[i][j]+=b[i][j-1];
		}
	for (int i=1,x1,y1,x2,y2;i<=m;i++) {
		read(x1);read(y1);read(x2);read(y2);
		if (x1>x2) swap(x1,x2);
		if (y1>y2) swap(y1,y2);
		x1--,y1--;
		LL ret=0;
		for (int k=1;k<=n;k++) {
			ret+=(a[x2][k]-a[x1][k])*(b[k][y2]-b[k][y1]);
		}
		printf("%lld\n",ret);
	}
	return 0;
}

