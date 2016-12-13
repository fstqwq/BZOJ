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

#define MAXN 200005
#define MAXM 500005

struct data {
	int u,v;
	bool exist;
	data(){}
	data(int a,int b):u(a),v(b),exist(false){}
	bool operator < (data a) const {
		if (u!=a.u) return u<a.u;
		return v<a.v;
	}
	bool operator == (data a) const {
		return u==a.u && v==a.v;
	}
}e[MAXM];

struct query {
	int op,x,y;
}q[MAXM];

int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;	
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

inline void readop(int &a) {
	while (ch!='!' && ch!='+' && ch!='-') ch=getchar();
	if (ch=='!') a=0;
	else if (ch=='+') a=1;
	else a=2;
}

int n,m,cnt=0;
int tot[MAXN],lazy[MAXN];


int find(data x) {
	int l=1,r=cnt,mid;
	while (l<r) {
		mid=(l+r+1)>>1;
		if (x<e[mid]) r=mid-1;
		else l=mid;
	}
	return l;
}

int main() {
	read(n);read(m);
	for (int i=1;i<=m;i++) {
		readop(q[i].op);read(q[i].x);
		if (q[i].op) {
			read(q[i].y);
			if (q[i].x>q[i].y) swap(q[i].x,q[i].y);
			if (q[i].op==1) {
				e[++cnt]=data(q[i].x,q[i].y);
			}
		}
	}
	sort(e+1,e+cnt+1);
	cnt=int(unique(e+1,e+cnt+1)-e-1);
	for (int i=1;i<=m;i++) {
		if (q[i].op) {
			int tag=find(data(q[i].x,q[i].y));
			if (q[i].op==1) {
				tot[q[i].x]-=lazy[q[i].y];
				tot[q[i].y]-=lazy[q[i].x];
				e[tag].exist=1;
			}
			else {
				tot[q[i].x]+=lazy[q[i].y];
				tot[q[i].y]+=lazy[q[i].x];
				e[tag].exist=0;
			}
		}
		else {
			lazy[q[i].x]++;
		}
	}
	for (int i=1;i<=cnt;i++) {
		if (e[i].exist) {
			tot[e[i].u]+=lazy[e[i].v];
			tot[e[i].v]+=lazy[e[i].u];
		}
	}
	for (int i=1;i<n;i++) {
		printf("%d ",tot[i]);
	}
	printf("%d\n",tot[n]);
	return 0;
}

