#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#define inf 0x7fffffff
#define ll long long
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,t[200005],ans[100005];
struct data{int a,b,c,s,ans;}a[100005],p[100005];
inline bool cmp(data a,data b)
{
	if(a.a==b.a&&a.b==b.b)return a.c<b.c;
	if(a.a==b.a)return a.b<b.b;
	return a.a<b.a;
}
inline bool operator<(data a,data b)
{
	if(a.b==b.b)return a.c<b.c;
	return a.b<b.b;
}
inline int lowbit(int x){return x&(-x);}
inline void update(int x,int num)
{
	for(int i=x;i<=m;i+=lowbit(i))
	    t[i]+=num;
}
inline int ask(int x)
{
	int tmp=0;
	for(int i=x;i;i-=lowbit(i))
	    tmp+=t[i];
	return tmp;
}
void solve(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)>>1;
	solve(l,mid);solve(mid+1,r);
	sort(p+l,p+mid+1);
	sort(p+mid+1,p+r+1);
	int i=l,j=mid+1;
	while(j<=r)
	{
		while(i<=mid&&p[i].b<=p[j].b)
		{
			update(p[i].c,p[i].s);
		    i++;
		}
		p[j].ans+=ask(p[j].c);
		j++;
	}
	for(int j=l;j<i;j++)update(p[j].c,-p[j].s);
}
int main()
{
	int N=read();m=read();
	for(int i=1;i<=N;i++)
	    a[i].a=read(),a[i].b=read(),a[i].c=read();
	sort(a+1,a+N+1,cmp);
	int cnt=0;
	for(int i=1;i<=N;i++)
	{
		cnt++;
		if(a[i].a!=a[i+1].a||a[i].b!=a[i+1].b||a[i].c!=a[i+1].c)
		{
			p[++n]=a[i];
			p[n].s=cnt;
			cnt=0;
		} 
	}
	solve(1,n);
    for(int i=1;i<=n;i++)
        ans[p[i].ans+p[i].s-1]+=p[i].s;
    for(int i=0;i<N;i++)
        printf("%d\n",ans[i]);
	return 0;
}
