#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define inf 1000000000
using namespace std;
inline ll read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n;
int s[5005],f[5005];
int main()
{
	freopen("read.in","r",stdin);
	freopen("ans.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		int x=read();
		s[i]=s[i-1]+x;
		f[i]=x;
	}
	for(int l=1;l<n;l++)
		for(int i=1;i<=n-l;i++)
			f[i]=s[i+l]-s[i-1]-min(f[i],f[i+1]);
	printf("%d",f[1]);
	return 0;
}
