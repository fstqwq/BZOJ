/*	Never stop fighting for what you believe in.	*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;
int ch=0;
inline void read(int &a) {
	bool f=0;
	while (ch<'0' || ch>'9') {if (ch=='-') f=1;ch=getchar();}
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
	if (f) a=-a;
}
#define MAXN 25005
#define INF 0x3f3f3f3f
struct edge {
	int next,to,w;
}e[MAXN<<3];

const int Q=32767;
struct queue {
	int head,tail,v[32768];
	queue():head(16777216),tail(16777216){}
	void push_front(int x) {
		v[(--head)&Q]=x;
	}
	void push_back(int x) {
		v[(tail++)&Q]=x;
	}
	void push(int x) {
		v[(tail++)&Q]=x;
	}
	void pop() {
		head++;
	}
	int front() {
		return v[head&Q];
	}
	bool empty() {
		return head>=tail;
	}
}q;

int head[MAXN],dis[MAXN];
int n,m,M,S,ecnt=0;
bool inq[MAXN];
void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].w=w;
	head[u]=ecnt;
}

void spfa() {
	memset(dis,63,sizeof(dis));
	dis[S]=0;
	q.push(S);
	while (!q.empty()) {
		int x=q.front();q.pop();inq[x]=0;
		for (int now=head[x];now;now=e[now].next) {
			if (dis[e[now].to]>dis[x]+e[now].w) {
				dis[e[now].to]=dis[x]+e[now].w;
				if (!inq[e[now].to]) {
					inq[e[now].to]=1;
					if (dis[e[now].to]<=dis[q.front()]) {
						q.push_front(e[now].to);
					}
					else {
						q.push_back(e[now].to);
					}
				}
			}
		}
	}
}

int main() {	
	read(n);read(m);read(M);read(S);
	for (int i=1,u,v,w;i<=m;i++) {
		read(u);read(v);read(w);
		add(u,v,w);add(v,u,w);
	}
	for (int i=1,u,v,w;i<=M;i++) {
		read(u);read(v);read(w);
		add(u,v,w);
	}
	spfa();
	for (int i=1;i<=n;i++) {
		if (dis[i]==INF) puts("NO PATH");
		else printf("%d\n",dis[i]);
	}
	return 0;
}

