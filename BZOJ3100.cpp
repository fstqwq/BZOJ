/*  Never stop fighting for what you believe in.	*/
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
int n;
int a[MAXN],cnt[MAXN];
 
bool check(int x) {
	printf("x = %d\n",x);
	memset(cnt,0,sizeof(cnt));
	int need=x,more=0;
	for (int i=1;i<=x;i++) {
		if (a[i]>x) more++;
		else {
			cnt[a[i]]++;
			if (cnt[a[i]]==1) need--;
			else if (cnt[a[i]]>1) more++;
		}
	}
	printf("%d %d\n",need,more);
	if (need==0 && more==0) return 1;
	for (int i=x+1;i<=n;i++) {
		if (a[i-x]>x) more--;
		else{
			cnt[a[i-x]]--;
			if (cnt[a[i-x]]==1) more--;
			else if (cnt[a[i-x]]==0) need++;
			if (a[i-x]>x) more--;
		}
		cnt[a[i]]++;
		if (a[i]>x) {
			more++;
		}
		else {
			if (cnt[a[i]]==1) need--;
			else if (cnt[a[i]]>1) more++;
		}

	printf("%d %d\n",need,more);
		if (need==0 && more==0) return 1;
	}
	return 0;
}
 
int main() {
	freopen("read.in","r",stdin);
//	freopen("cmp.out","w",stdout);
	read(n);
	for (int i=1;i<=n;i++) {
		read(a[i]);
	}
	int l=0,r=n,mid;
	while (l<r) {
		mid=(l+r+1)>>1;
		if (check(mid)) l=mid;
		else r=mid-1;
	}
	printf("%d\n",l);
	return 0;
}
