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
#include <map>
using namespace std;
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
typedef long long LL;
map<LL,int> M;
LL f[100];

void init() {
	f[0]=0;
	f[1]=1;
	M[0]=1;
	for (int i=2;i<=90;i++) {
		f[i]=f[i-1]+f[i-2];
		M[f[i]]=1;
	}
}

int find(LL x) {
	int l=4,r=90,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (f[mid]>=x) r=mid;
		else l=mid+1;
	}
	return l;
}

int query(LL x) {
	int k=M[x];
	if (k) return k;
	int q=find(x);
	return M[x]=min(query(x-f[q-1]),query(f[q]-x))+1;
}

int main() {
	init();
	int T;
	scanf("%d",&T);
	while (T--) {
		LL x;
		scanf("%lld",&x);
		printf("%d\n",query(x));
	}
	return 0;
}

