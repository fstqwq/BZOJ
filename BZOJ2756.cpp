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

int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 45
#define MAXNODE 2005
#define INF 1234567890123456ll
struct edge {
	int next,to;
	LL flow;
}e[MAXNODE<<4];

int S,T;
int n,m,head[MAXNODE],ecnt,tag[MAXNODE],cur[MAXNODE];
int a[MAXN][MAXN];

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

int q[2048];
bool bfs() {
	int h=0,t=1;
	q[0]=0;
	memset(tag,0,sizeof(tag));
	tag[0]=1;
	while (h<t) {
		int x=q[h++];
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q[t++]=e[now].to;
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
	LL ans=0;
	while (bfs()) {
		for (int i=T;i!=-1;i--) cur[i]=head[i];
		ans+=dfs(0,INF);
	}
	return ans;
}

#define pos(i,j) ((i-1)*m+j)

bool ok(LL mid) {
	ecnt=1;
	LL should=0;
	S=0,T=n*m+1;
	memset(head,0,sizeof(head));
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			if ((i^j)&1) {
				should+=mid-a[i][j];
				add(0,pos(i,j),mid-a[i][j]);
				if (j<m) add(pos(i,j),pos(i,j+1),INF);
				if (j>1) add(pos(i,j),pos(i,j-1),INF);
				if (i<n) add(pos(i,j),pos(i+1,j),INF);
				if (i>1) add(pos(i,j),pos(i-1,j),INF);
			}
			else {
				add(pos(i,j),T,mid-a[i][j]);
			}
		}
	}
	return dinic()==should;
}

int main() {
	int t;
	read(t);
	while (t--) {
		read(n);read(m);
		int MAX=0;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++) {
				read(a[i][j]);
				MAX=max(a[i][j],MAX);
			}
		LL s[2]={0,0};
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++) {
				s[(i^j)&1]+=a[i][j];
			}
		if (n&m&1) {
			LL x=s[0]-s[1];
			if (x>=MAX && ok(x)) printf("%lld\n",(x*n*m-(s[0]+s[1]))/2);
			else puts("-1");
		}
		else {
			if (s[0]!=s[1]) puts("-1");
			else {
				LL l=MAX,r=INF,mid;
				while (l<r) {
					mid=(l+r)>>1;
					if (ok(mid)) r=mid;
					else l=mid+1;
				}
				printf("%lld\n",l*(n*m)/2-s[0]);
			}
		}
	}
	return 0;
}

