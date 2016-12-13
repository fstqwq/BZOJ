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
#define MAXN 1005
struct task {
	int c,d;
	bool operator < (task a) const {
		return d<a.d;
	}
}t[MAXN];
int n;
int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		read(t[i].c);read(t[i].d);
	}
	sort(t+1,t+n+1);
	int now=0,minleft=0x7fffffff;
	for (int i=1;i<=n;i++) {
		now+=t[i].c;
		minleft=min(minleft,t[i].d-now);
	}
	if (minleft<0) puts("-1");
	else printf("%d\n",minleft);
	return 0;
}

