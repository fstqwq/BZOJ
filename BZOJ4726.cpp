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
#define MAXN 500005
struct edge {
	int next,to;
}e[MAXN];
int n,k,head[MAXN],siz[MAXN],ecnt=0;
int fa[MAXN];
double ans[MAXN];
void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
}
void dfs(int x) {
	siz[x]=1;
	if (!head[x]) ans[x]=1;
	else {
		ans[x]=0;
		for (int now=head[x];now;now=e[now].next) {
			dfs(e[now].to);
			siz[x]+=siz[e[now].to];
		}
		for (int now=head[x];now;now=e[now].next) {
			ans[x]=max(ans[x],min(ans[e[now].to],double(siz[e[now].to])/(siz[x]-1)));
		}
	}
}

int main() {
	read(n);read(k);
	for (int i=2;i<=n;i++) {
		read(fa[i]);
		add(fa[i],i);
	}
	dfs(1);
	double pr=0;
	for (int i=1;i<=n;i++) {
		if (siz[i]>k) pr=max(pr,ans[i]);
	}
	printf("%.7lf\n",pr);
	return 0;
}

