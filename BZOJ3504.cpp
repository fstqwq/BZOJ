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

#define MAXN 55
#define MAXB MAXN*MAXN

struct edge {
	int next,to,flow;
}e[MAXB<<1];

const int source=0,sink=1;

int n,a1,a2,an,b1,b2,bn,ecnt,head[MAXN],cur[MAXN],tag[MAXN];
char temp[MAXN][MAXN];

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

void add_2(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=1;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=1;
	head[v]=ecnt;
}

void add_N(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	e[ecnt].flow=123;
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	e[ecnt].flow=123;
	head[v]=ecnt;
}

void init() {
	ecnt=1;
	memset(head,0,sizeof(head));
}

void build() {
	add(0,a1+2,an);
	add(a2+2,1,an);
	add(0,b1+2,bn);
	add(b2+2,1,bn);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<i;j++) {
			if (temp[i][j]=='O') {
				add_2(i+1,j+1);
			}
			else if (temp[i][j]=='N') {
				add_N(i+1,j+1);
			}
		}
	}
}


queue <int> q;
bool bfs() {
    q.push(0);
    memset(tag,0,sizeof(tag));
    tag[0]=1;
    while (!q.empty()) {
        int x=q.front();q.pop();
        for (int now=head[x];now;now=e[now].next) {
            if (e[now].flow && !tag[e[now].to]) {
                tag[e[now].to]=tag[x]+1;
                q.push(e[now].to);
            }
        }
    }
    return tag[1]>0;
}
 
int dfs(int x,int flow) {
    if (x==1) return flow;
    int usd=0;
    for (int &now=cur[x];now;now=e[now].next) {
        if (e[now].flow && tag[x]<tag[e[now].to]) {
            int ret=dfs(e[now].to,min(e[now].flow,flow));
			if (ret) {
                usd+=ret;
                e[now].flow-=ret;
                e[now^1].flow+=ret;
                if (usd==flow) return flow;
            }
        }
    }
    return usd;
}
 
bool dinic() {
    int ans=0,k=an+bn;
    while (k!=ans && bfs()) {
        for (int i=0;i<=n+1;i++) cur[i]=head[i];
        ans+=dfs(0,k-ans);
    }
    return ans==k;
}


int main() {
	while (scanf("%d%d%d%d%d%d%d",&n,&a1,&a2,&an,&b1,&b2,&bn)==7 && n) {
		for (int i=1;i<=n;i++) {
			scanf("%s",temp[i]+1);
		}
		init();
		build();
		if (dinic()) {
			swap(b1,b2);
			init();
			build();
			if (dinic()) puts("Yes");
			else puts("No");
		}
		else puts("No");
		n=0;
	}
	return 0;
}

