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
#define INF 0x3f3f3f3f
#define MAXN 205

struct edge {
	int next,to,flow;
}e[MAXN*MAXN*4];

int n,ecnt=1,head[MAXN];
inline void add(int u,int v,int flow) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=flow;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=0;
	head[v]=ecnt;
}
int tag[MAXN],cur[MAXN];
queue <int> q;
bool bfs() {
	q.push(1);
	memset(tag,0,sizeof(tag));
	tag[1]=1;
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tag[n]>0;
}

int dfs(int x,int flow) {
	if (x==n) return flow;
	int used=0;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tag[e[now].to]>tag[x]) {
			int ret=dfs(e[now].to,min(flow-used,e[now].flow));
			if (ret) {
				used+=ret;
				e[now].flow-=ret;
				e[now^1].flow+=ret;
				if (used==flow) return flow;
			}
		}
	}
	return used;
}

int dinic() {
	int ans=0;
	while (bfs()) {
		for (int i=1;i<=n;i++) cur[i]=head[i];
		ans+=dfs(1,INF);
	}
	return ans;
}

int main() {
	read(n);
	for (int i=1,cnt;i<n;i++) {
		read(cnt);
		for (int j=1,x;j<=cnt;j++) {
			read(x);
			if (i==1 || x==n) add(i,x,1);
			else add(i,x,INF);
		}
	}
	printf("%d\n",dinic());
	return 0;
}

