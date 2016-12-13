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
	int next,to,w;
}e[MAXN<<2];

int m,n,S,A,B,ecnt=0,head[MAXN],dis[MAXN];

void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].w=w;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].w=w;
	head[v]=ecnt;
}

struct statu {
	int x,v;
	statu(){}
	statu(int a,int b):x(a),v(b){}
	bool operator < (statu a) const {
		return v>a.v;
	}
};

priority_queue<statu> q;
void dijkstra(int st) {
	memset(dis,127,sizeof(dis));
	dis[st]=0;
	q.push(statu(st,0));
	while (!q.empty()) {
		int x=q.top().x,d=q.top().v;q.pop();
		if (d!=dis[x]) continue;
		for (int now=head[x];now;now=e[now].next) {
			if (dis[e[now].to]>d+e[now].w) {
				dis[e[now].to]=d+e[now].w;
				q.push(statu(e[now].to,dis[e[now].to]));
			}
		}
	}
}

int main() {
	read(m);read(n);read(S);read(A);read(B);
	for (int i=1,u,v,w;i<=m;i++) {
		read(u);read(v);read(w);
		add(u,v,w);
	}
	dijkstra(S);
	int ans=min(dis[A],dis[B]);
	dijkstra(A);
	printf("%d\n",ans+dis[B]);
	return 0;
}

