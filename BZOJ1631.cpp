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
#define MAXN 1005
#define MAXM 100005
struct Readedge {
	int u,v,w;
}re[MAXM];

struct edge {
	int next,to,w;
}e[MAXM<<1];
/*#define TOP 1023
struct queue {
	int v[TOP+1],head,tail;
	queue():head(1048576),tail(1048576){}
	int &operator [](int x) {return v[x];}
	void push_back(int x) {
		v[(tail++)&TOP]=x;
	}
	void push_front(int x) {
		v[(--head)&TOP]=x;
	}
	void pop_front() {
		head++;
	}
	bool empty() {
		return head>=tail;
	}
	int front() {
		return v[head&TOP];
	}
}q;*/
queue<int> q;
int n,m,ecnt,X,dis[MAXN],head[MAXN],dd[MAXN],ans=0;
inline void add(int u,int v,int w) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].w=w;
	head[u]=ecnt;
}
bool inq[MAXN];
void spfa() {
	memset(dis,0x7f,sizeof(dis));
	dis[X]=0;
	q.push(X);
	while (!q.empty()) {
		int x=q.front();q.pop();
		inq[x]=0;
		for (int now=head[x];now;now=e[now].next) {
			if (dis[x]+e[now].w<dis[e[now].to]) {
				dis[e[now].to]=dis[x]+e[now].w;
				if (!inq[e[now].to]) {
					inq[e[now].to]=1;
					if (dis[e[now].to]<dis[q.front()]) q.push(e[now].to);
					else q.push(e[now].to);
				}
			}
		}
	}
}

int main() {
	read(n);read(m);read(X);
	for (int i=1;i<=m;i++) {
		read(re[i].u);read(re[i].v);read(re[i].w);
	}
	ecnt=0;
	for (int i=1;i<=m;i++) {
		add(re[i].u,re[i].v,re[i].w);
	}
	spfa();
	for (int i=1;i<=n;i++) dd[i]=dis[i];
	memset(head,0,sizeof(head));
	ecnt=0;
	for (int i=1;i<=m;i++) {
		add(re[i].v,re[i].u,re[i].w);
	}
	spfa();
	for (int i=1;i<=n;i++) ans=max(ans,dd[i]+dis[i]);
	printf("%d\n",ans);
	return 0;
}

