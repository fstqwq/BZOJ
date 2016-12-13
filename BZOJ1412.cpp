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
#define MAXM MAXN*4

struct edge {
	int next,to,flow;
}e[MAXM*2];

int n,ecnt=1,head[MAXN],tag[MAXN],cur[MAXN];

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
void add_2(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=1;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=1;
	head[v]=ecnt;
}

int source=0,sink=1;
queue <int> q;
bool bfs() {
	memset(tag,0,sizeof(tag));
	q.push(source);
	tag[source]=1;
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tag[sink]>0;
}
  
int dfs(int x,int flow) {
	if (x==sink) return flow;
	int usd=0;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tag[x]<tag[e[now].to]) {
			int ret=dfs(e[now].to,min(e[now].flow,flow));
			if (ret) {
				usd+=ret;
				e[now].flow-=ret;
				e[now^1].flow+=ret;
				if (usd==flow) return flow;
			}
		}
	}
	return usd;
}
  
int dinic() {
	int ans=0;
	while (bfs()) {
		for (int i=0;i<=n;i++) cur[i]=head[i];
		ans+=dfs(source,12345678);
	}
	return ans;
}


int r,c,m[105][105],ttt[105][105];

int main() {
	scanf("%d%d",&r,&c);
	n=1;
	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++) {
			scanf("%d",m[i]+j);
			if (m[i][j]==0) ttt[i][j]=++n;
		}
	}
	for (int i=2;i<=r;i++)
		for (int j=1;j<=c;j++) {
			if (m[i][j]==m[i-1][j]) {
				if (m[i][j]==0) add_2(ttt[i][j],ttt[i-1][j]);
			}
			else {
				if (m[i][j]==1) {
					if (m[i-1][j]==0) add(0,ttt[i-1][j]);
					else add(0,1);
				}
				else if (m[i][j]==2) {
					if (m[i-1][j]==0) add(ttt[i-1][j],1);
					else add(0,1);
				}
				else {
					if (m[i-1][j]==1) add(0,ttt[i][j]);
					else add(ttt[i][j],1);
				}
			}
		}
	for (int i=1;i<=r;i++)
		for (int j=2;j<=c;j++) {
			if (m[i][j]==m[i][j-1]) {
				if (m[i][j]==0) add_2(ttt[i][j],ttt[i][j-1]);
			}
			else {
				if (m[i][j]==1) {
					if (m[i][j-1]==0) add(0,ttt[i][j-1]);
					else add(0,1);
				}
				else if (m[i][j]==2) {
					if (m[i][j-1]==0) add(ttt[i][j-1],1);
					else add(0,1);
				}
				else {
					if (m[i][j-1]==1) add(0,ttt[i][j]);
					else add(ttt[i][j],1);
				}
			}
		}
	printf("%d\n",dinic());
	return 0;
}

