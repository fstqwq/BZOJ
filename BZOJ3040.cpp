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
typedef long long LL;
#define MAXN 1048576
#define MAXM 10000005
#define INF 0x3f3f3f3f3f3f3f3fll
struct edge {
	int next,to,w;
}e[MAXM];

int n,m,s,head[MAXN];
LL dis[MAXN],t[MAXN<<1];

inline int query() {
	int x=1;
	while (x<s) {
		x<<=1;
		if (t[x^1]<t[x]) x^=1;
	}
	return x-s;
}

void update(int x,LL v) {
	for (x+=s;x;x>>=1) if (t[x]>v) t[x]=v; else return;
}
void del(int x) {
	x+=s;
	t[x]=INF;
	for (x>>=1;x;x>>=1) t[x]=min(t[x<<1],t[(x<<1)^1]);
}

bool visit[MAXN];
inline long long dijkstra() {
	update(1,0);
	int x=1;
	while (x) {
		visit[x]=1;
		dis[x]=t[x+s];
		if (x==n) return dis[x];
		del(x);
		for (int now=head[x];now;now=e[now].next) {
			if (!visit[e[now].to] && t[e[now].to+s]>dis[x]+e[now].w) {
				update(e[now].to,dis[x]+e[now].w);
			}
		}
		x=query();
	}
	return -1;
}

int main() {
	read(n);read(m);
	int T,rxa,rxc,rya,ryc,rp,a,b;
	read(T);read(rxa);read(rxc);read(rya);read(ryc);read(rp);
	for (int x=0,y=0,i=1;i<=T;i++) {
		x=int(((LL)x*rxa+rxc)%rp);
		y=int(((LL)y*rya+ryc)%rp);
		a=min(x%n+1,y%n+1);
		b=max(y%n+1,y%n+1);
		e[i].to=b;
		e[i].next=head[a];
		e[i].w=100000000-100*a;
		head[a]=i;
	}
	for (int i=T+1,x;i<=m;i++) {
		read(x);read(e[i].to);read(e[i].w);
		e[i].next=head[x];
		head[x]=i;
	}
	for (s=1;s<n+1;s<<=1);
	for (int i=(s<<1)-1;i;i--) t[i]=0x1f1f1f1f1f1f1f1fll;
	printf("%lld\n",dijkstra());
	return 0;
}

