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
#define INF 0x3f3f3f3f
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 50005
struct rrr {
	int u,v,A,B;
	bool operator < (rrr a) const {
		return B<a.B;
	}
}r[MAXN<<1];
struct edge {
	int next,to,w;
}e[MAXN<<2];

int n,m,ans=INF,head[MAXN],dis[MAXN],ecnt;

void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].w=w;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].w=w;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}

bool inq[MAXN];
queue<int> q;

void spfa(int st) {
	q.push(st);
	while (!q.empty()) {
		int x=q.front();q.pop();inq[x]=0;
		for (int now=head[x];now;now=e[now].next) {
			if (dis[e[now].to]>max(dis[x],e[now].w)) {
				dis[e[now].to]=max(dis[x],e[now].w);
				if (!inq[e[now].to]) {
					inq[e[now].to]=1;
					q.push(e[now].to);
				}
			}
		}
	}
}

int main() {
	read(n);read(m);
	for (int i=1;i<=m;i++) {
		read(r[i].u);read(r[i].v);read(r[i].A);read(r[i].B);
	}
	sort(r+1,r+m+1);
	memset(dis,31,sizeof(dis));
	dis[1]=0;
	for (int i=1;i<=m;i++) {
		add(r[i].u,r[i].v,r[i].A);
		if (dis[r[i].u]<dis[r[i].v]) spfa(r[i].u);
		else if (dis[r[i].v]<dis[r[i].u]) spfa(r[i].v);
		ans=min(ans,dis[n]+r[i].B);
	}
	if (ans<100005) printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}

