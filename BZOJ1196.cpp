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

#define MAXN 10005
#define MAXM 20005

struct edge {
	int u,v,c1,c2;
}e[MAXM];

int n,k,m,f[MAXN];

int getf(int x) {
	if (f[x]<0) return x;
	else return f[x]=getf(f[x]);
}

bool merge(int a,int b) {
	int fa=getf(a),fb=getf(b);
	if (fa==fb) return 0;
	if (f[fa]<f[fb]) {
		f[fa]+=f[fb];
		f[fb]=fa;
	}
	else {
		f[fb]+=f[fa];
		f[fa]=fb;
	}
	return 1;
}

bool check(int x) {
	memset(f+1,-1,4*n);
	int cnt=1;
	for (int i=1;i<m;i++) {
		if (e[i].c1<=x && merge(e[i].u,e[i].v)) cnt++;
	}
	if (cnt<=k) return 0;
	for (int i=1;i<m && cnt<n;i++) {
		if (e[i].c2<=x && merge(e[i].u,e[i].v)) cnt++;
	}
	if (cnt==n) return 1;
	else return 0;
}

int main() {
	scanf("%d%d%d",&n,&k,&m);
	for (int i=1;i<m;i++) {
		scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].c1,&e[i].c2);
	}
	int l=0,r=30001,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}

