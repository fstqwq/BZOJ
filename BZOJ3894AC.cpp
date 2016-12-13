#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define inf 1000000000
#define pa pair<int,int>
#define ll long long 
#define mod 1000000007
using namespace std;
#define p(i,j) (i-1)*m+j
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int ans,tot;
int n,m,T,cnt=1;
int q[30005],last[30005],h[30005];
int xx[5]={0,0,1,-1,0},yy[5]={1,-1,0,0,0};
struct edge{
	int to,next,v;
}e[1000005];
void insert(int u,int v,int w)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;e[cnt].v=w;
	e[++cnt].to=u;e[cnt].next=last[v];last[v]=cnt;e[cnt].v=0;
}
bool bfs()
{
	int head=0,tail=1;
	memset(h,-1,sizeof(h));
	q[0]=0;h[0]=0;
	while(head!=tail)
	{
		int now=q[head];head++;
		for(int i=last[now];i;i=e[i].next)
			if(e[i].v&&h[e[i].to]==-1)
			{
				h[e[i].to]=h[now]+1;
				q[tail++]=e[i].to;
			}
	}
	return h[T]!=-1;
}
int dfs(int x,int f)
{
	if(x==T)return f;
	int w,used=0;
	for(int i=last[x];i;i=e[i].next)
		if(e[i].v&&h[e[i].to]==h[x]+1)
		{
			w=dfs(e[i].to,min(e[i].v,f-used));
			e[i].v-=w;e[i^1].v+=w;
			used+=w;if(used==f)return f;
		}
	if(!used)h[x]=-1;
	return used;
}
int main()
{
	n=read();m=read();T=3*n*m+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int x=read();
			insert(0,p(i,j),x);
			tot+=x;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)	
		{
			int x=read();
			insert(p(i,j),T,x);
			tot+=x;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int val=read();tot+=val;
		    for(int k=0;k<5;k++)
			{
				int x=xx[k]+i,y=yy[k]+j;
				if(x>n||y>m||x<1||y<1)continue;
				insert(p(i,j)+n*m,p(x,y),inf);
			}
			insert(0,p(i,j)+n*m,val);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int val=read();tot+=val;
		    for(int k=0;k<5;k++)
			{
				int x=xx[k]+i,y=yy[k]+j;
				if(x>n||y>m||x<1||y<1)continue;
				insert(p(x,y),p(i,j)+2*n*m,inf);
			}
			insert(p(i,j)+2*n*m,T,val);
		}
	while(bfs())ans+=dfs(0,inf);
	printf("%d\n",tot);
	printf("%d\n",tot-ans);
	return 0;
}
