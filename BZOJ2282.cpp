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


#define MAXN 300005

struct edge {
	int next,to,w;
}e[MAXN<<1];

int n,s,ecnt=0;
int dis[MAXN],fa[MAXN],head[MAXN],ans[MAXN];
int visit[MAXN];

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

int q[MAXN];

inline int bfs(int st) {
	fa[st]=st;
	dis[st]=0;
	int he=1,ta=2;
	q[1]=st;
	while (he<ta) {
		int x=q[he++];
		for (int now=head[x];now;now=e[now].next) {
			int v=e[now].to;
			if (v!=fa[x]) {
				fa[v]=x;
				dis[v]=dis[x]+e[now].w;
				q[ta++]=v;
			}
		}
	}
	int d=0,t=0;
	for (int i=1;i<=n;i++) {
		if (dis[i]>d) {
			d=dis[i];
			t=i;
		}
	}
	return t;
}

struct statu {
	int val,tag;
	statu(){}
	statu(int a,int b):val(a),tag(b){}
	bool operator < (statu a) const {
		return val<a.val;
	}
};

priority_queue<statu> fnt,back,on;
int minans=0x7fffffff;
int main() {
	read(n);read(s);
	for (int i=1,u,v,w;i<n;i++) {
		read(u);read(v);read(w);
		add(u,v,w);
	}
	int root=bfs(1);
	int x=bfs(root),tag=0;
	for (int i=x;;i=fa[i]) {
		visit[i]=++tag;
		if (i==root) break;
	}
	for (int i=n;i>1;i--) {
		if (!visit[q[i]]) {
			ans[fa[q[i]]]=max(ans[fa[q[i]]],ans[q[i]]+dis[q[i]]-dis[fa[q[i]]]);
		}
	}
	for (int i=x;;i=fa[i]) {
		back.push(statu(ans[i]-dis[i],visit[i]));
		if (i==root) break;
	}
	int i=x,j=x;
	on.push(statu(ans[x],visit[x]));
	while (j!=root) {
		while (j!=root && dis[i]-dis[fa[j]]<=s) {
			j=fa[j];
			on.push(statu(ans[j],visit[j]));
		}
		//push back
		while (!back.empty() && back.top().tag<=visit[j]) back.pop();
		//push on
		while (!on.empty() && on.top().tag<visit[i]) on.pop();
		int nowans=on.top().val;
		if (!back.empty()) nowans=max(nowans,back.top().val+dis[j]);
		if (!fnt.empty()) nowans=max(nowans,fnt.top().val-dis[i]);
		minans=min(minans,nowans);
		fnt.push(statu(ans[i]+dis[i],visit[i]));
		i=fa[i];
	}
	printf("%d\n",minans);
	return 0;
}

