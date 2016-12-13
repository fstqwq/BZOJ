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
#define MAXK 12
#define MAXM 100005

int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}

struct edge {
	int next,to,w;
}e[MAXM];

int n,m,k,s,t,ecnt=0,head[MAXN];

inline void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].w=w;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].w=w;
	head[v]=ecnt;
}

int dis[MAXN][MAXK];
bool inq[MAXN][MAXK];
queue <int> q;
int spfa() {
	memset(dis,127,sizeof(dis));
	q.push(s<<10);
	for (int i=0;i<=k;i++) {
		dis[s][i]=0;
	}
	while (!q.empty()) {
		int x=q.front()>>10,d=q.front()&1023;q.pop();
		inq[x][d]=0;
		for (int now=head[x];now;now=e[now].next) {
			if (dis[e[now].to][d]>dis[x][d]+e[now].w) {
				dis[e[now].to][d]=dis[x][d]+e[now].w;
				if (!inq[e[now].to][d]) {
					inq[e[now].to][d]=1;
					q.push((e[now].to<<10)|d);
				}
			}
			if (d<k && dis[e[now].to][d+1]>dis[x][d]) {
				dis[e[now].to][d+1]=dis[x][d];
				if (!inq[e[now].to][d+1]) {
					inq[e[now].to][d+1]=1;
					q.push((e[now].to<<10)|(d+1));
				}
			}
		}
	}
	int ans=0x7f7f7f7f;
	for (int i=0;i<=k;i++) {
		ans=min(ans,dis[t][i]);
	}
	return ans;
}

int main() {
	read(n);read(m);read(k);read(s);read(t);
	for (int i=1,u,v,w;i<=m;i++) {
		read(u);read(v);read(w);
		add(u,v,w);
	}
	printf("%d\n",spfa());
	return 0;
}

