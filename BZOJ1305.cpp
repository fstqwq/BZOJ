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
inline void readop(bool &a) {
	while (ch<'A' || ch>'Z') ch=getchar();
	if (ch=='Y') a=1;
	else a=0;
	ch=getchar();
}


#define MAXN 210
#define MAXM MAXN*MAXN*2
struct edge {
	int next,to,flow;
}e[MAXM];

bool map[55][55];
const int src=0,sink=1;
int n,k,head[MAXN],cur[MAXN],tag[MAXN],ecnt;

void add(int u,int v,int f) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=f;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=0;
	head[v]=ecnt;
}

void build(int mid) {
	memset(head,0,sizeof(head));
	ecnt=1;
	for (int i=1;i<=n;i++) {
		add(0,i<<2,mid);
		add(i<<2,(i<<2)|1,k);
		add((i<<2)|2,(i<<2)|3,k);
		add((i<<2)|3,1,mid);
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) {
			if (map[i][j]) {
				add(i<<2,(j<<2)|3,1);
			}
			else {
				add((i<<2)|1,(j<<2)|2,1);
			}
		}
}


queue <int> q;
bool bfs() {
	memset(tag,0,sizeof(tag));
	tag[0]=1;
	q.push(0);
	while (!q.empty()) {
		int x=q.front();q.pop();
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q.push(e[now].to);
			}
		}
	}
	return tag[1]!=0;
}

int dfs(int x,int flow) {
	if (x==sink) return flow;
	int used=0;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tag[x]<tag[e[now].to]) {
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

bool dinic(int mid) {
	int ans=0;
	while (bfs()) {
		for (int i=0;i<=((n<<2)|3);i++) cur[i]=head[i];
		ans+=dfs(0,n*mid);
	}
	return ans==n*mid;
}

int main() {
	read(n);read(k);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			readop(map[i][j]);
		}
	}
	int l=min(n,k),r=n,mid;
	while (l<r) {
		mid=(l+r+1)>>1;
		build(mid);
		if (dinic(mid)) l=mid;
		else r=mid-1;
	}
	printf("%d\n",l);
	return 0;
}

