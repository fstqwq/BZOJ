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
int n,q;
int a[MAXN];
int Minv[MAXN][20],Maxv[MAXN][20];

int log_2(int x) {
	int ret=0;
	if (x&0xffff0000) x>>=16,ret+=16;
	if (x&0x0000ff00) x>>=8,ret+=8;
	if (x&0x000000f0) x>>=4,ret+=4;
	if (x&0x0000000c) x>>=2,ret+=2;
	return ret+(x>>1);
}


int query(int l,int r) {
	int x=r-l+1;
	int tt=log_2(x);
	return max(Maxv[l][tt],Maxv[r-(1<<tt)+1][tt])-min(Minv[l][tt],Minv[r-(1<<tt)+1][tt]);
}

int main() {
	read(n);read(q);
	for (int i=1;i<=n;i++) read(a[i]),Minv[i][0]=a[i],Maxv[i][0]=a[i];
	for (int k=1;1<<k <=n;k++) {
		int tt=1<<(k-1);
		for (int i=1,ta=n-(1<<k)+1;i<=ta;i++) {
			Minv[i][k]=min(Minv[i][k-1],Minv[i+tt][k-1]);
			Maxv[i][k]=max(Maxv[i][k-1],Maxv[i+tt][k-1]);
		}
	}
	for (int i=1,l,r;i<=q;i++) {
		read(l);read(r);
		printf("%d\n",query(l,r));
	}
	return 0;
}

