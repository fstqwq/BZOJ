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
typedef long long LL;
struct node {
	int l,r,v;
	LL sum;
}t[MAXN<<5];
int n,k,tcnt=0,rt[MAXN];
LL ans=12345678912345678;
int update(int x,int l,int r,int v) {
	int now=++tcnt;
	t[now]=t[x];
	t[now].v++;
	t[now].sum+=v;
	if (l!=r) {
		int mid=(l+r)>>1;
		if (v<=mid) t[now].l=update(t[x].l,l,mid,v);
		else t[now].r=update(t[x].r,mid+1,r,v);
	}
	return now;
}

int kth(int rx,int lx,int l,int r,int p) {
	if (l==r) return l;
	int mid=(l+r)>>1,lv=t[t[rx].l].v-t[t[lx].l].v;
	if (lv>=p) return kth(t[rx].l,t[lx].l,l,mid,p);
	else return kth(t[rx].r,t[lx].r,mid+1,r,p-lv);
}
int query(int rx,int lx,int l,int r,int ql,int qr) {
	if (l==ql && r==qr) return t[rx].v-t[lx].v;
	int mid=(l+r)>>1,ret=0;
	if (ql<=mid) ret+=query(t[rx].l,t[lx].l,l,mid,ql,min(qr,mid));
	if (qr>mid) ret+=query(t[rx].r,t[lx].r,mid+1,r,max(mid+1,ql),qr);
	return ret;
}
LL getSum(int rx,int lx,int l,int r,int ql,int qr) {
	if (l==ql && r==qr) return t[rx].sum-t[lx].sum;
	int mid=(l+r)>>1;
	LL ret=0;
	if (ql<=mid) ret+=getSum(t[rx].l,t[lx].l,l,mid,ql,min(qr,mid));
	if (qr>mid) ret+=getSum(t[rx].r,t[lx].r,mid+1,r,max(mid+1,ql),qr);
	return ret;
}
#define HI 1000001
int main() {
	read(n);read(k);
	for (int i=1,a;i<=n;i++) {
		read(a);
		rt[i]=update(rt[i-1],-1,HI,a);
	}
	int mid=(k+1)>>1;
	for (int R=k;R<=n;R++) {
		int L=R-k;
		int ret=kth(rt[R],rt[L],-1,HI,mid);
		LL pre=query(rt[R],rt[L],-1,HI,-1,ret-1),nxt=query(rt[R],rt[L],-1,HI,ret+1,HI);
		ans=min(ans,getSum(rt[R],rt[L],-1,HI,-1,ret-1)+getSum(rt[R],rt[L],-1,HI,ret+1,HI)+(pre-nxt)*ret);
	}
	printf("%lld\n",ans);
	return 0;
}


