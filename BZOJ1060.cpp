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
typedef long long LL;
#define MAXN 500005
struct edge {
	int next,to,w;
}e[MAXN<<1];
int n,ecnt=0,head[MAXN],fa[MAXN],S;
LL tt[MAXN],ans=0;
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
int q[MAXN],he,ta;
void bfs() {
	fa[S]=S;
	he=1,ta=2;
	q[1]=S;
	while (he<ta) {
		int x=q[he++];
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].to!=fa[x]) {
				fa[e[now].to]=x;
				q[ta++]=e[now].to;
			}
		}
	}
}
void work() {
	for (int i=n;i;i--) {
		int x=q[i];
		LL maxt=0;
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].to!=fa[x]) {
				maxt=max(maxt,tt[e[now].to]);
			}
		}
		tt[x]=maxt;
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].to!=fa[x]) {
				ans+=maxt-tt[e[now].to];
			}
			else {
				tt[x]+=e[now].w;
			}
		}
	}
}
int main() {
	read(n);read(S);
	for (int i=1,u,v,w;i<n;i++) {
		read(u);read(v);read(w);
		add(u,v,w);
	}
	bfs();
	work();
	cout<<ans<<endl;
	return 0;
}

