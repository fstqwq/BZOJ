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

#define MAXN 256

int a[MAXN][MAXN],n,m,k;

struct edge {
	int next,to,flow;
}e[MAXN*MAXN*4];

const int source=0,sink=1;
int ecnt,head[MAXN*2],tag[MAXN*2];

void init() {
	ecnt=1;
	memset(head,0,sizeof(head));
}

void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=1;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=0;
	head[v]=ecnt;
}

void build(int x) {
	for (int i=1;i<=n;i++) {
		add(0,i+1);
	}
	for (int i=1;i<=m;i++) {
		add(i+n+1,1);
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			if (a[i][j]<=x) add(i+1,j+n+1);
		}
	}
}

queue <int> q;
bool bfs() {
	q.push(0);
	memset(tag,0,sizeof(tag));
	tag[0]=1;
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tag[1]>0;
}

int dfs(int x,int flow) {
	if (x==1) return flow;
	for (int now=head[x];now;now=e[now].next) {
		if (e[now].flow && tag[x]<tag[e[now].to]) {
			if (dfs(e[now].to,1)) {
				e[now].flow--;
				e[now^1].flow++;
				return 1;
			}
		}
	}
	return 0;
}

bool dinic() {
	int ans=0;
	while (k!=ans && bfs()) {
		while (k!=ans && dfs(0,1)) ans++;
	}
	return ans==k;
}

bool check(int x) {
	init();
	build(x);
	if (dinic()) return 1;
	else return 0;
}

int main() {
	scanf("%d%d%d",&n,&m,&k);
	k=n-k+1;
	int MIN=1000000001,MAX=-1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			scanf("%d",a[i]+j);
			MIN=min(MIN,a[i][j]);
			MAX=max(MAX,a[i][j]);
		}
	int l=MIN,r=MAX,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}

