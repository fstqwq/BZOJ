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
inline void read(bool &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
typedef long long LL;
#define MAXN 105
#define INF 123456789123456ll
struct edge {
	int next,to;
	LL flow;
}e[MAXN*MAXN*8];

int n,m,S=0,T=1,ecnt=1;
int a[MAXN],b[MAXN],head[MAXN*2],tag[MAXN*2],cur[MAXN*2];
bool map[MAXN][MAXN];
LL sum=0;

void add(int u,int v,LL flow) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=flow;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=0;
	head[v]=ecnt;
}

#define robot(x) (x+1)
#define weapon(x) (x+n+1)

queue <int> q;

bool bfs() {
	memset(tag,0,sizeof(tag));
	tag[S]=1;
	q.push(S);
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

LL dfs(int x,LL flow) {
	if (x==T) return flow;
	LL used=0;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tag[e[now].to]>tag[x]) {
			LL ret=dfs(e[now].to,min(flow-used,e[now].flow));
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

LL dinic() {
	LL ret=0;
	while (bfs()) {
		for (int i=weapon(m);i>-1;i--) cur[i]=head[i];
		ret+=dfs(S,INF);
	}
	return ret;
}

bool check(LL mid) {
	memset(head,0,sizeof(head));
	ecnt=1;
	for (int i=1;i<=n;i++) {
		add(S,robot(i),a[i]);
	}
	for (int i=1;i<=m;i++) {
		add(weapon(i),T,b[i]*mid);
	}
	for (int i=1;i<=m;i++) {
		for (int j=1;j<=n;j++) {
			if (map[i][j]) add(robot(j),weapon(i),INF);
		}
	}
	return dinic()==sum;
}

int main() {
	read(n);read(m);
	for (int i=1;i<=n;i++) read(a[i]),a[i]*=2000,sum+=a[i];
	for (int i=1;i<=m;i++) read(b[i]);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++) {
			read(map[i][j]);
		}
	LL l=0,r=200000000001ll,mid;
	while (l<r) {
		mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	double ans=double(mid)/2000.0+0.00025;
	printf("%.5lf\n",ans);
	return 0;
}

