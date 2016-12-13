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
#define MAXN 40010
struct Read {
	int u,v;
}re[MAXN];

struct edge {
	int next,to,flow;
}e[MAXN<<3];

int n,m,ecnt,S=0,T=1,head[MAXN],tag[MAXN],cur[MAXN];

void add(int u,int v,int flow) {
	e[++ecnt].to=v;e[ecnt].next=head[u];e[ecnt].flow=flow;head[u]=ecnt;
	e[++ecnt].to=u;e[ecnt].next=head[v];e[ecnt].flow=0;head[v]=ecnt;
}


queue <int> q;

bool bfs() {
	memset(tag,0,sizeof(tag));
	tag[S]=1;
	q.push(S);
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tag[T]>0;
}

int dfs(int x,int flow) {
	if (x==T) return flow;
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
	int ret=0;
	while (bfs()) {
		for (int i=n+m+1;i>=0;i--) cur[i]=head[i];
		ret+=dfs(S,0x7ffffff);
	}
	return ret;
}

bool check(int mid) {
	memset(head,0,sizeof(head));
	ecnt=1;
	for (int i=1;i<=n;i++) {
		add(i+1,T,mid);
	}
	for (int i=1;i<=m;i++) {
		add(S,n+i+1,1);
		add(n+i+1,re[i].u+1,1);
		add(n+i+1,re[i].v+1,1);
	}
	return dinic()==m;
}

int main() {
	read(n);read(m);
	for (int i=1;i<=m;i++) {
		read(re[i].u);read(re[i].v);
	}
	int l=(m>0),r=m,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}

