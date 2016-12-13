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

int ch;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

#define MAXN 405
#define MAXM MAXN*MAXN*2
struct edge {
	int next,to,flow;
}e[MAXM];

const int src=0,sink=1;
int n,head[MAXN],cur[MAXN],tag[MAXN],ecnt;

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

void init() {
	memset(head,0,sizeof(head));
	ecnt=1;
	for (int i=1;i<=n;i++) {
		add(0,i<<1);
		add((i<<1)|1,1);
	}
	for (int i=1,fun;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			read(fun);
			if (fun) {
				add(i<<1,(j<<1)|1);
			}
		}
	}
}


queue <int> q;
bool bfs() {
	memset(tag,0,sizeof(tag));
	tag[0]=1;
	q.push(0);
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tag[1]!=0;
}

int dfs(int x,int flow) {
	if (x==sink) return flow;
	int used=0;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tag[x]<tag[e[now].to]) {
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
		for (int i=0;i<=((n<<1)^1);i++) cur[i]=head[i];
		ans+=dfs(0,n);
	}
	return ans;
}

int main() {
	int T;
	read(T);
	while (T--) {
		read(n);
		init();
		if (dinic()==n) puts("Yes");
		else puts("No");
	}
	return 0;
}

