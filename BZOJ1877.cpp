/*  Never stop fighting for what you believe in.    */
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
 
#define MAXN 405
#define MAXM 20005
 
struct edge {
    int next,to,w,flow;
}e[MAXM*4];
  
const int source=0,sink=1;
  
int n,m,ecnt=1,head[MAXN];
 
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
bool spfa() {
    memset(dis,31,sizeof(dis));
	memset(pre,-1,sizeof(pre));
    dis[source]=0;
    q.push(source);
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
	return pre[sink]!=-1;
}
  
  
void work() {
    int ans=0,tot=0;
    while (spfa()) {
		tot++;
		ans+=dis[sink];
        for (int x=sink;x!=source;x=pre[x]) {
            e[pos[x]].flow--;
            e[pos[x]^1].flow++;
        }
    }
    printf("%d %d\n",tot,ans);
}
 
int main() {
    scanf("%d%d",&n,&m);
	for (int i=2;i<n;i++) {
		add(i*2,i*2+1,0,1);
	}
    for (int i=1,u,v,w;i<=m;i++) {
        scanf("%d%d%d",&u,&v,&w);
        add(u*2+1,v*2,w,1);
    }
	add(0,3,0,12345678);
	add(n*2,1,0,12345678);
    work();
    return 0;
}
