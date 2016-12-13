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
#define MAXN 5005

struct edge {
	int next,to,flow;
}ee[MAXN<<5],e[MAXN<<6];

int eecnt=0,ehead[MAXN],ecnt=1,head[MAXN],cur[MAXN],tag[MAXN];
bool visit[MAXN];

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

void add_1(int u,int v) {
	ee[++eecnt].to=v;
	ee[eecnt].next=ehead[u];
	ee[eecnt].flow=0;
	ehead[u]=eecnt;
}

int n,ans=0;

bool k_T(int x) {
	if (x==n) return 1;
	for (int now=ehead[x];now;now=ee[now].next) {
		if (!visit[ee[now].to]) {
			visit[ee[now].to]=1;
			if (k_T(ee[now].to)) {
				ee[now].flow++;
				return 1;
			}
		}
	}
	return 0;
}

int kkk;

bool S_k(int x) {
	if (x==kkk) return 1;
	for (int now=ehead[x];now;now=ee[now].next) {
		if (!visit[ee[now].to]) {
			visit[ee[now].to]=1;
			if (S_k(ee[now].to)) {
				ee[now].flow++;
				return 1;
			}
		}
	}
	return 0;
}
queue <int> q;
bool bfs() {
    q.push(n);
    memset(tag,0,sizeof(tag));
    tag[n]=1;
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
    int used=0;
    for (int &now=cur[x];now;now=e[now].next) {
        if (e[now].flow && tag[e[now].to]>tag[x]) {
            int ret=dfs(e[now].to,min(e[now].flow,flow-used));
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
        for (int i=1;i<=n;i++) cur[i]=head[i];
        ret+=dfs(n,0x7ffffff);
    }
    return ret;
}
int main() {
	read(n);
	for (int i=1,x;i<n;i++) {
		read(x);
		for (int j=1,p;j<=x;j++) {
			read(p);
			add_1(i,p);
		}
	}
	for (int i=1;i<n;i++) {
		for (int now=ehead[i];now;now=ee[now].next) {
			if (!ee[now].flow) {
				ans++;
				memset(visit,0,sizeof(visit));
				visit[1]=1;
				kkk=i;
				S_k(1);
				memset(visit,0,sizeof(visit));
				visit[ee[now].to]=1;
				k_T(ee[now].to);
				ee[now].flow++;
			}
		}
	}
	for (int i=1;i<n;i++) {
		for (int now=ehead[i];now;now=ee[now].next) {
			if (ee[now].flow>1) {
				add(ee[now].to,i,ee[now].flow-1);
			}
		}
	}
	printf("%d\n",ans-dinic());
	return 0;
}

