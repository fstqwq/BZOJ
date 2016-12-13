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
typedef long long LL;
#define MAXN 3005
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
struct edge {
	int next,to,flow;
}e[MAXN*MAXN];
int n,S=0,T,a[MAXN],head[MAXN],cur[MAXN],tag[MAXN],ecnt=1;
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
queue <int> q;
bool bfs() {
	memset(tag,0,sizeof(tag));
	q.push(S);
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
			int ret=dfs(e[now].to,min(flow-used,e[now].flow));
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
		ret+=dfs(S,0x7fffffff);
	}
	return ret;
}
int gcd(int x,int y) {
	if (y) return gcd(y,x%y);
	else return x;
}
#define power(x) (LL(x)*LL(x))

int main() {
	read(n);
	T=n+1;
	int tot=0;
	for (int i=1;i<=n;i++) {
		read(a[i]);
		if (a[i]&1) add(S,i,a[i]);
		else add(i,T,a[i]);
		tot+=a[i];
	}
	for (int i=1;i<n;i++) {
		for (int j=i+1;j<=n;j++) {
			if ((a[i]^a[j])&1 && gcd(a[i],a[j])==1) {
				LL x=power(a[i])+power(a[j]);
				LL sqx=LL(sqrt(x));
				if (sqx*sqx==x) {
					if (a[i]&1)	add(i,j,0x7fffffff);
					else add(j,i,0x7ffffff);
				}
			}
		}
	}
	printf("%d\n",tot-dinic());
	return 0;
}

