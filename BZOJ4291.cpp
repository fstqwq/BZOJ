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
#define MAXN 1000005
int n,ans=0,odcnt=0,minod=1000000;

int main() {
	read(n);
	for (int i=1,a;i<=n;i++) {
		read(a);
		ans+=a;
		if (a&1) odcnt++,minod=min(a,minod);
	}
	if (n==1 && odcnt==1) puts("NIESTETY");
	else if (odcnt&1) printf("%d\n",ans-minod);
	else printf("%d\n",ans);
	return 0;
}

