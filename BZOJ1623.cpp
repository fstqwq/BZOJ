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
#define MAXN 50005
int n,m,d,l,ans=0;
int s[MAXN];

int main() {
	read(n);read(m);read(d);read(l);
	for (int i=1;i<=n;i++) read(s[i]);
	sort(s+1,s+n+1);
	int k=0,tot=0;
	for (int i=1;i<=n;i++) {
		if (s[i]-k*d<l) continue;
		ans++;
		tot++;
		if (tot==m) {
			tot=0;
			k++;
		}
	}
	printf("%d\n",ans);
	return 0;
}

