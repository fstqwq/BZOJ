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

typedef long long LL;

int ch=0;
inline bool read(int &a) {
	while (ch<'0' || ch>'9') {
		ch=getchar();
		if (ch==-1) return 0;
	}
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();} 
	return 1;
}
inline void read(LL &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();} 
}

LL quickpower(LL a,LL x,LL MOD) {
	a%=MOD;
	LL ans=1;
	while (x) {
		if (x&1) ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		x>>=1;
	}
	return ans;
}

LL exgcd(LL a,LL b,LL &x,LL &y) {
	if (!b) {
		x=1;
		y=0;
		return a;
	}
	LL g=exgcd(b,a%b,x,y);
	LL t=x;
	x=y;
	y=t-a/b*y;
	return g;
}

void solve2(LL a,LL z,LL p) {
	LL x,y;
	// solve ax - py == Z (mod P)
	LL g=exgcd(a,-p,x,y);
	if (z%g!=0) puts("Orz, I cannot find x!");
	else {
		x=(x*(z/g))%p;
		if (x<0) printf("%lld\n",x+p);
		else printf("%lld\n",x);
	}
}

map<LL,LL> Hash;

void solve3(LL y,LL z,LL p) {
	// solve y^x==z -> y ^ (km + i) == z
	y%=p;
	if (z==1) {
		puts("0");
		return;
	}
	if (y==0) {
		if (z==0) puts("1");
		else puts("Orz, I cannot find x!");
		return;
	}
	LL m=(LL)sqrt(p)+1;
	Hash.clear();
	Hash[1]=-1;
	for (LL i=1,t=1;i<m;i++) {
		t=(t*y)%p;
		if (!Hash[t]) Hash[t]=i;
	}
	LL temp=quickpower(y,p-m-1,p),ine=1;
	for (LL k=0;k<m;k++) {
		LL x=Hash[(z*ine)%p];
		if (x) {
			if (x==-1) x=0;
			printf("%lld\n",k*m+x);
			return;
		}
		ine=(ine*temp)%p;
	}
	puts("Orz, I cannot find x!");
}

int main() {
	int T;
	while (scanf("%d",&T)!=EOF) {
		LL y,z,p;
		int k;
		scanf("%d",&k);
		while (T--) {
			scanf("%lld%lld%lld",&y,&z,&p);
			if (k==1) {
				printf("%lld\n",quickpower(y,z,p));
			}
			else if (k==2) {
				solve2(y,z,p);
			}
			else {
				solve3(y,z,p);
			}
		}
	}
	return 0;
}

