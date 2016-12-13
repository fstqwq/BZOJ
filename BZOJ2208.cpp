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
#include <bitset>
using namespace std;
#define MAXN 2005
bitset<MAXN> map[MAXN],G[MAXN];

struct edge {
	int next,to;
}e[MAXN*MAXN];

int ecnt=0,head[MAXN];

int n;
char temp[MAXN];
int low[MAXN],dfn[MAXN],belong[MAXN],in[MAXN],scc=0,cnt=0;
long long ans=0;
int sta[MAXN],top=0;
int siz[MAXN];
bool inq[MAXN];

void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	in[v]++;
}
void tarjan(int x) {
	dfn[x]=low[x]=++cnt;
	sta[++top]=x;
	inq[x]=1;
	for (int i=1;i<=n;i++) {
		if (map[x][i]) {
			if (!dfn[i]) tarjan(i),low[x]=min(low[x],low[i]);
			else if (inq[i]) low[x]=min(low[x],low[i]);
		}
	}
	if (dfn[x]==low[x]) {
        siz[++scc]=0;
        int now=0;
        while (now!=x) {
            now=sta[top--];
            belong[now]=scc;
            inq[now]=0;
            siz[scc]++;
        }
    }
}

int q[MAXN],he=1,ta=1;
void topo() {
	for (int i=1;i<=scc;i++) {
		if (!in[i]) q[ta++]=i;
		G[i][i]=1;
	}
	while (he<ta) {
		int x=q[he++];
		for (int now=head[x];now;now=e[now].next) {
			G[e[now].to]|=G[x];
			in[e[now].to]--;
			if (!in[e[now].to]) {
				q[ta++]=e[now].to;
			}
		}
	}
	for (int i=1;i<=scc;i++) {
		for (int j=1;j<=scc;j++) {
			if (G[i][j]) {
				ans+=(long long)siz[i]*siz[j];
			}
		}
	}
	printf("%lld\n",ans);
}

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%s",temp+1);
		for (int j=1;j<=n;j++) {
			if (temp[j]=='1') map[i][j]=1;
		}
		map[i][i]=1;
	}
	for (int i=1;i<=n;i++) {
		if (!dfn[i]) tarjan(i);
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			if (map[i][j] && belong[i]!=belong[j] && !G[belong[i]][belong[j]])
				add(belong[i],belong[j]);
		}
	}
	topo();
	return 0;
}

