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

#define MAXN 1005
#define MAXM 5005

struct edge {
    int next,to,w,flow;
}e[MAXM*4];
 
const int source=0,sink=1;
 
int n,m,k,ecnt=1,head[MAXN];

void add(int u,int v,int w,int flow) {
    e[++ecnt].to=v;
    e[ecnt].next=head[u];
    e[ecnt].w=w;
    e[ecnt].flow=flow;
    head[u]=ecnt;
    e[++ecnt].to=u;
    e[ecnt].next=head[v];
    e[ecnt].w=-w;
    e[ecnt].flow=0;
    head[v]=ecnt;
}
 
 
int pos[MAXN],pre[MAXN],dis[MAXN];
bool inq[MAXN];
 
queue <int> q;
void spfa() {
    memset(dis,31,sizeof(dis));
    dis[1]=0;
    q.push(1);
    while (!q.empty()) {
        int x=q.front();q.pop();inq[x]=0;
        for (int now=head[x];now;now=e[now].next) {
            if (e[now].flow && dis[e[now].to]>dis[x]+e[now].w) {
                dis[e[now].to]=dis[x]+e[now].w;
                pre[e[now].to]=x;
                pos[e[now].to]=now;
                if (!inq[e[now].to]) {
                    inq[e[now].to]=1;
                    q.push(e[now].to);
                }
            }
        }
    }
}
 
 
void work() {
    int ans=0,nocost=0,tot=0;
    while (tot<k) {
        spfa();
		if (dis[n]) {
        	ans+=dis[n];
			tot++;
		} else {
			nocost++;
		}
        for (int x=n;x!=1;x=pre[x]) {
            e[pos[x]].flow--;
            e[pos[x]^1].flow++;
        }
    }
    printf("%d %d\n",nocost,ans);
}

int main() {
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1,u,v,f,w;i<=m;i++) {
		scanf("%d%d%d%d",&u,&v,&f,&w);
		add(u,v,0,f);
		add(u,v,w,k);
	}
	work();
	return 0;
}

