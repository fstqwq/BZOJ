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
#define MAXN 100005

struct flower {
	int x,y,z,siz,ans;
	bool operator < (flower a) const {
		if (x!=a.x) return x<a.x;
		else if (y!=a.y) return y<a.y;
		else return z<a.z;
	}
}a[MAXN],p[MAXN];

bool cmp(flower x,flower y) {
	if (x.z!=y.z) return x.y<y.y;
	else return x.z<y.z;
}

int n,k,tot[MAXN];
#define s 262144
int t[s<<1];

void update(int x,int v) {
	for (x+=s;x;x>>=1) t[x]+=v;
}
void del(int x) {
	for (x+=s;x;x>>=1) t[x]=0;
}
int query(int x) {
	int ret=0;
	for (int l=s,r=x+s+1;l^r^1;l>>=1,r>>=1) {
		if ((l&1)^1) ret+=t[l^1];
		if (r&1) ret+=t[r^1];
	}
	return ret;
}

void cdq(int l,int r) {
	if (l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	sort(p+l,p+mid+1,cmp);sort(p+mid+1,p+r+1,cmp);
	int i=l,j=mid+1;
	while (j<=r) {
		while (i<=mid && p[i].y<=p[j].y) {
			update(p[i].z,p[i].siz);
			i++;
		}
		p[j].ans+=query(p[j].z);
		j++;
	}
	for (i=l;i<=mid;i++) del(p[i].z);
}

int main() {
	read(n);read(k);
	for (int i=1;i<=n;i++) {
		read(a[i].x);read(a[i].y);read(a[i].z);a[i].ans=0;
	}
	sort(a+1,a+n+1);
	int wu=0;
	for (int i=1,cnt=0;i<=n;i++) {
		cnt++;
		if (a[i].x!=a[i+1].x || a[i].y!=a[i+1].y || a[i].z!=a[i+1].z) {
			p[++wu]=a[i];
			p[wu].siz=cnt;
			cnt=0;
		}
	}
	n=wu;
	cdq(1,n);
	for (int i=1;i<=n;i++) {
		tot[p[i].ans+p[i].siz-1]+=p[i].siz;
	}
	for (int i=0;i<n;i++) {
		printf("%d\n",tot[i]);
	}
	return 0;
}

