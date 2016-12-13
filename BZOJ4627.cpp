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
#define INF 0x7fffffffffffffll
using namespace std;
int ch=0;
inline void read(int &a) {
	bool f=0;
	while (ch<'0' || ch>'9') {if (ch=='-') f=1;ch=getchar();}
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
	if (f) a=-a;
}
#define MAXN 100005
typedef long long LL;
int n,L,R,cnt=0;
#define s 131072
int t[s<<1];
LL sum[MAXN],tem[MAXN],ans=0;

int find_low(LL x) {
	int l=1,r=cnt,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (tem[mid]>=x) r=mid;
		else l=mid+1;
	}
	return l;
}

int find_high(LL x) {
	int l=1,r=cnt,mid;
	while (l<r) {
		mid=(l+r+1)>>1;
		if (tem[mid]<=x) l=mid;
		else r=mid-1;
	}
	return l;
}

int query(int l,int r) {
	int ret=0;
	for (l+=s-1,r+=s+1;l^r^1;l>>=1,r>>=1) {
		if ((l&1)^1) ans+=t[l^1];
		if (r&1) ans+=t[r^1];
	}
	return ret;
}

void update(int x) {
	for (x+=s;x;x>>=1) t[x]++;
}

int main() {
	read(n);read(L);read(R);
	for (int i=1,x;i<=n;i++) {
		read(x);
		sum[i]=sum[i-1]+x;
		tem[i]=sum[i];
	}
	cnt=n;
	tem[++cnt]=-INF;
	tem[++cnt]=INF;
	tem[++cnt]=0;
	sort(tem+1,tem+cnt+1);
	cnt=int(unique(tem+1,tem+cnt+1)-tem-1);
	update(find_low(0));
	for (int i=1;i<=n;i++) {
		int xpos=find_low(sum[i]),lpos=find_low(sum[i]-R),rpos=find_high(sum[i]-L);
		if (lpos<=rpos) ans+=query(lpos,rpos);
		update(xpos);
	}
	printf("%lld\n",ans);
	return 0;
}

