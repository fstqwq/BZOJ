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
inline bool readop() {
	while (ch!='A' && ch!='Q') ch=getchar();
	return ch=='A';
}

#define MAXN 600005
#define bitwise 24

struct node {
	int lch,rch,v;
}t[MAXN<<6];

int n,m,tcnt=0;
int sum[MAXN],rt[MAXN];

int update(int pre,int num,int dep) {
	int now=++tcnt;
	t[now].lch=t[pre].lch;
	t[now].rch=t[pre].rch;
	t[now].v=t[pre].v+1;
	if (dep>-1) {
		if ((num>>dep)&1) t[now].rch=update(t[pre].rch,num,dep-1);
		else t[now].lch=update(t[pre].lch,num,dep-1);
	}
	return now;
}

int query(int lx,int rx,int num) {
	int dep=bitwise,ret=0;
	while (dep>-1) {
		if ((num>>dep)&1) {
			if (t[t[rx].lch].v-t[t[lx].lch].v>0) ret|=1<<dep,lx=t[lx].lch,rx=t[rx].lch;
			else lx=t[lx].rch,rx=t[rx].rch;
		}
		else {
			if (t[t[rx].rch].v-t[t[lx].rch].v>0) ret|=1<<dep,lx=t[lx].rch,rx=t[rx].rch;
			else lx=t[lx].lch,rx=t[rx].lch;
		}
		dep--;
	}
	dep=bitwise;
	return ret;
}

int main() {
	read(n);read(m);
	rt[1]=update(0,0,bitwise);
	for (int i=1,a;i<=n;i++) {
		read(a);
		sum[i]=sum[i-1]^a;
		rt[i+1]=update(rt[i],sum[i],bitwise);
	}
	for (int i=1,l,r,x;i<=m;i++) {
		if (readop()) {
			read(x);
			n++;
			sum[n]=sum[n-1]^x;
			rt[n+1]=update(rt[n],sum[n],bitwise);
		}
		else {
			read(l);read(r);read(x);
			l--,x^=sum[n];
			printf("%d\n",query(rt[l],rt[r],x));
		}
	}
	return 0;
}

