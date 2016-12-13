/*  Never stop fighting for what you believe in.	*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <string>
#define INF 12345678
using namespace std;
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 215
 
struct edge {
	int next,to,flow;
}ee[MAXN<<10],e[MAXN<<11];
 
int S,T,SS,TT,eecnt=0,ehead[MAXN],ecnt=1,head[MAXN],cur[MAXN],tag[MAXN],in[MAXN];
 
void add(int u,int v,int flow) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=flow;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=0;
	head[v]=ecnt;
}
 
void add_1(int u,int v) {
	ee[++eecnt].to=v;
	ee[eecnt].next=ehead[u];
	ehead[u]=eecnt;
}

int n;
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
	return tag[T]>0;
}
int dfs(int x,int flow) {
	if (x==T) return flow;
	int used=0;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tag[e[now].to]>tag[x]) {
			int ret=dfs(e[now].to,min(e[now].flow,flow-used));
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
		for (int i=0;i<=T;i++) cur[i]=head[i];
		ret+=dfs(S,INF);
	}
	return ret;
}

int work() {
	ecnt=1;
	for (int i=1;i<=n;i++) {
		for (int now=ehead[i];now;now=ee[now].next) {
			add(i,ee[now].to,INF),in[i]--,in[ee[now].to]++;
		}
	}
	SS=n+1;TT=SS+1;S=TT+1;T=S+1;
	for (int i=1;i<=n;i++) {
		add(SS,i,INF);
		add(i,TT,INF);
		if (in[i]>0) add(S,i,in[i]);
		else if (in[i]<0) add(i,T,-in[i]);
	}
	add(TT,SS,INF);
	dinic();
	int ans=e[ecnt].flow;
	head[SS]=e[head[SS]].next;
	head[TT]=e[head[TT]].next;
	for (int now=head[S];now;now=e[now].next) {
		e[now].flow=e[now^1].flow=0;
	}
	for (int now=head[T];now;now=e[now].next) {
		e[now].flow=e[now^1].flow=0;
	}
	add(S,TT,INF);add(SS,T,INF);
	return ans-dinic();
}

int main() {
	scanf("%d",&n);
	for (int i=1,x;i<=n;i++) {
		scanf("%d",&x);
		for (int j=1,p;j<=x;j++) {
			scanf("%d",&p);
			add_1(i,p);
		}
	}
	printf("%d\n",work());
	return 0;
}
