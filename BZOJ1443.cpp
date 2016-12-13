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
#include <fstream>
using namespace std;

#define MAXN 105

int n,m,S,T;
char map[MAXN][MAXN];
struct edge {
	int next,to,flow;
}e[(MAXN*MAXN)<<4];

int ecnt=1,head[MAXN*MAXN],cur[MAXN*MAXN],tag[MAXN*MAXN];

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

queue <int> q;
bool bfs() {
	q.push(S);
	memset(tag,0,sizeof(tag));
	tag[S]=1;
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tag[T]!=0;
}

bool dfs(int x) {
	if (x==T) return 1;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tag[e[now].to]>tag[x])
			if (dfs(e[now].to)) {
				e[now].flow^=1;
				e[now^1].flow^=1;
				return 1;
			}
	}
	return 0;
}

void dinic() {
	while (bfs()) {
		for (int i=S;i<=T;i++) cur[i]=head[i];
		while (dfs(S));
	}
}

#define pos(i,j) ((i-1)*m+j)

bool ans[MAXN*MAXN];
bool visit[MAXN*MAXN];

void update(int x,bool st) {
	visit[x]=1;
	if (st) {
		ans[x]=1;
	}
	for (int now=head[x];now;now=e[now].next) {
		if (!e[now].flow && e[now].to!=S && e[now].to!=T && !visit[e[now].to]) {
			update(e[now].to,st^1);		
		}
	}
}

void build(int x) {
	memset(head,0,sizeof(head));
	ecnt=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (map[i][j]=='.' && (((i^j)&1)==x)) {
				if (i>1 && map[i-1][j]=='.') add(pos(i,j),pos(i-1,j));
				if (i<n && map[i+1][j]=='.') add(pos(i,j),pos(i+1,j));
				if (j>1 && map[i][j-1]=='.') add(pos(i,j),pos(i,j-1));
				if (j<m && map[i][j+1]=='.') add(pos(i,j),pos(i,j+1));
				add(S,pos(i,j));
			}
	x^=1;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			if (map[i][j]=='.' && (((i^j)&1)==x)) {
				add(pos(i,j),T);
			}
		}
	}
}

bool flag=0;
void work(int x) {
	build(x);
	dinic();
	memset(visit,0,sizeof(visit));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			if (((i^j)&1)!=x && map[i][j]=='.' && head[pos(i,j)] && e[head[pos(i,j)]].flow && !visit[pos(i,j)]) {
				flag=1;
				update(pos(i,j),1);
			}
		}
}

int main() {
	scanf("%d%d",&n,&m);
	S=0;T=n*m+1;
	for (int i=1;i<=n;i++) {
		scanf("%s",map[i]+1);
	}
	work(0);
	work(1);
	if (flag) {
		puts("WIN");
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++) {
				if (ans[pos(i,j)]) {
					printf("%d %d\n",i,j);
				}
			}
	}
	else puts("LOSE");
	return 0;
}

