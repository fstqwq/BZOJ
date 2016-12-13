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

#define INF 123456789
#define MAXN 2005

struct point {
	int x,y;
	point(){}
	point(int a,int b):x(a),y(b){}
	bool operator < (point a) const {
		if (x!=a.x) return x<a.x;
		return y<a.y;
	}
}p[MAXN];

struct edge {
	int next,to,w,flow;
}e[MAXN*MAXN];

const int source=0,sink=1;

int n,ecnt=1,head[MAXN<<1];

void add(int u,int v,int w,int flow) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].w=w;
	e[ecnt].flow=flow;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].w=-w;
	e[ecnt].flow=0;
	head[v]=ecnt;
}


int pos[MAXN<<1],pre[MAXN<<1],dis[MAXN<<1];
bool inq[MAXN<<1];

queue <int> q;
void spfa() {
	memset(dis,-1,sizeof(dis));
	dis[0]=0;
	q.push(0);
	while (!q.empty()) {
		int x=q.front();q.pop();inq[x]=0;
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && dis[e[now].to]<dis[x]+e[now].w) {
				dis[e[now].to]=dis[x]+e[now].w;
				pre[e[now].to]=x;
				pos[e[now].to]=now;
				if (!inq[e[now].to]) {
					inq[e[now].to]=1;
					q.push(e[now].to);
				}
			}
		}
	}
}


int work() {
	int ans=0;
	for (int f=2;f;f--) {
		spfa();
		ans+=dis[1];
		for (int x=1;x!=0;x=pre[x]) {
			e[pos[x]].flow--;
			e[pos[x]^1].flow++;
		}
	}
	return ans;
}

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&p[i].x,&p[i].y);
	}
	sort(p+1,p+n+1);
	for (int i=1;i<=n;i++) {
		add(source,i*2,0,2);
		add(i*2,i*2+1,1,1);
		add(i*2,i*2+1,0,1);
		add(i*2+1,sink,0,2);
	}
	for (int i=1;i<=n;i++) {
		int maxy=INF;
		for (int j=i+1;j<=n;j++) {
			if (p[j].y>=p[i].y && p[j].y<maxy) {
				add(i*2+1,j*2,0,2);
				maxy=p[j].y;
			}
		}
	}
	printf("%d\n",work());
	return 0;
}

