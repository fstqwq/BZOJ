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
struct edge {
	int next,to;
}e[MAXN];

int n,head[MAXN],sum[MAXN],a[MAXN],s,h,t,ans=0,ecnt=0;

void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
}

void dfs(int x,int fa) {
	int dep=++t;
	sum[dep]=sum[dep-1]+a[x];
	while (sum[dep]-sum[h]>s) h++;
	if (sum[dep]-sum[h]==s) ans++;
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=fa) {
			int hh=h;
			dfs(e[now].to,x);
			h=hh;
		}
	}
	--t;
}


int main() {
	read(n);read(s);
	for (int i=1;i<=n;i++) read(a[i]);
	for (int i=1,u,v;i<n;i++) {
		read(u);read(v);add(u,v);
	}
	sum[0]=0;
	h=t=0;
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}

