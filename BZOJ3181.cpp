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
#define MAXN 1000000
#define INF 1000000000
typedef long long LL;
int n,p;
int prime[200000],lowp[MAXN+5],pcnt=0,pl;

void init() {
	for (int i=2;i<=MAXN;i++) {
		if (!lowp[i]) {
			prime[++pcnt]=i;
			lowp[i]=i;
			if (i==p) pl=pcnt;
			if (i>1000) continue;
			for (int j=i*i;j<=MAXN;j+=i) if (!lowp[j]) lowp[j]=i;
		}
	}
}

void vio() {
	n--;
	for (int i=1;i<=MAXN;i++) {
		if (i*p>INF) break;
		if (lowp[i]>=p) n--;
		if (!n) {printf("%d\n",i*p);return;}
	}
	puts("0");
}

LL tot=0,kk;

void dfs(int x,LL val,int f) {
	if (val>kk) return;
	if (x==pl) {
		tot+=kk/val*f;
	}
	else {
		dfs(x+1,val,f);
		dfs(x+1,val*prime[x],-f);
	}
}

bool check(int mid) {
	tot=0;kk=mid/p;
	dfs(1,1,1);
	return tot>=n;
}

void work() {
	int l=1,r=INF+1,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	if (l>INF) puts("0");
	else printf("%d\n",l);
}

int main() {
	read(n);read(p);
	init();
	if (p>1000) vio();
	else work();
	return 0;
}

