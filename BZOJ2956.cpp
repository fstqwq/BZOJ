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
inline void read(LL &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MOD 19940417
#define inv2 9970209
#define inv6 3323403
LL getsum(LL x) {
	LL ret=0;
	for (LL i=1,j;i<=x;i=j+1) {
		j=x/(x/i);
		ret=(ret+(((x/i)*(i+j))%MOD)*(((j-i+1)*inv2)%MOD))%MOD;
	}
	return (x*x-ret+MOD)%MOD;
}
LL powersum(LL x) {
	return (((x*(x+1)%MOD)*(2*x+1))%MOD*inv6)%MOD;
}

LL fuck(LL x,LL y) {
	LL ret=0,fret=0;
	LL mm=min(x,y),xy=(x*y)%MOD;
	for (LL i=1,j;i<=mm;i=j+1) {
		j=min(x/(x/i),y/(y/i));
		LL a=x/i,b=y/j,sum=(((i+j)*(j-i+1))%MOD*inv2)%MOD,ab=(a*b)%MOD;
		ret=(ret+xy*(j-i+1)+(MOD+powersum(j)-powersum(i-1))*ab)%MOD;
		fret=(fret+(a*y+b*x)%MOD*sum)%MOD;
	}
	if (ret<fret) return MOD+ret-fret;
	else return ret-fret;
}

LL n,m,ans=0;
int main() {
	read(n);read(m);
	LL sumn=getsum(n),summ=getsum(m);
	ans=(sumn*summ)%MOD;
	ans=(ans-fuck(n,m)+MOD)%MOD;
	printf("%d\n",int(ans));
	return 0;
}

