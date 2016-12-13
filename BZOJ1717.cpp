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
#define P 1000081
typedef unsigned long long LL;
int n,k;
LL ha[20005],a[20005],val[20005],ls[20005];

bool check(int mid) {
	int cnt=0,ans=0;
	for (int l=0,r=mid;r<=n;l++,r++) {
		ls[++cnt]=ha[r]-ha[l]*val[mid];
	}
	sort(ls+1,ls+cnt+1);
	LL now=-1llu;
	int tot=0;
	for (int i=1;i<=cnt;i++) {
		if (now==ls[i]) tot++;
		else ans=max(ans,tot),now=ls[i],tot=1;
	}
	ans=max(ans,tot);
	return ans>=k;
}

int main() {
	read(n);read(k);
	ha[0]=0;
	for (int i=1,x;i<=n;i++) {
		read(x);
		ha[i]=ha[i-1]*P+x;
	}
	val[0]=1;
	for (int i=1;i<=n;i++) {
		val[i]=val[i-1]*P;
	}
	int l=0,r=n;
	while (l<r) {
		int mid=(l+r+1)>>1;
		if (check(mid)) l=mid;
		else r=mid-1;
	}
	printf("%d\n",l);
	return 0;
}

