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
#define MAXN 10005
int T;
struct edge {
	int next,to;
}e[MAXN<<1];

int n,ans=0,ecnt=0,head[MAXN],fa[MAXN],cnt[MAXN];

void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

void init() {
	ecnt=0;
	memset(head,0,sizeof(head));
}

void dfs(int x) {
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].to!=fa[x]) {
			fa[e[now].to]=x;
			dfs(e[now].to);
		}
	}
	if (cnt[x]==0) cnt[fa[x]]++;
	else if (cnt[x]==1) cnt[fa[x]]++,ans--;
	else ans-=2;
	cnt[x]=0;
}

void work() {
	read(n);
	for (int i=1,u,v;i<n;i++) {
		read(u);read(v);
		add(u,v);
	}
	ans=n;
	fa[1]=0;
	dfs(1);
	printf("%d\n",ans);
}

int main() {
	read(T);
	while (T--) {
		init();
		work();
	}
	return 0;
}

