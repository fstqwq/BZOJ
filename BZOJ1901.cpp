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

inline void readop(int &a) {
	while (ch!='Q' && ch!='C') ch=getchar();
	a=(ch=='C');
	ch=getchar();
}

#define MAXN 10005

int n,m;
int a[MAXN],t[MAXN];


inline void work(int l,int r,int k) {
	int cnt=0;
	for (int i=l;i<=r;i++) {
		t[++cnt]=a[i];
	}
	nth_element(t+1,t+k,t+cnt+1);
	printf("%d\n",t[k]);
}

int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	for (int i=1,op,x,y,z;i<=m;i++) {
		readop(op);
		if (op) {
			read(x);read(y);
			a[x]=y;
		}
		else {
			read(x);read(y);read(z);
			work(x,y,z);
		}
	}

	return 0;
}

