	#include <cstdio>  
	#include <cstring>  
	#include <iostream>  
	#include <algorithm>  
	#define M 500500  
	#define MOD 1032992941  
	using namespace std;  
	struct abcd{  
		int to,next;  
	}table[M<<1];  
	int n,fa[M];  
	long long f[M],g[M],h[M];  
	long long F[M],G[M],H[M];  
	//f-自己选择 g-被子节点支配 h-放置play  
	int head[M],tot;  
	void Add(int x,int y)  
	{  
		table[++tot].to=y;  
		table[tot].next=head[x];  
		head[x]=tot;  
	}  
	void Tree_DP(int x)  
	{  
		int i;  
		f[x]=1;g[x]=0x3f3f3f3f;h[x]=0;  
		F[x]=G[x]=H[x]=1;  
		for(i=head[x];i;i=table[i].next)  
		{  
			if(table[i].to==fa[x])  
				continue;  
			fa[table[i].to]=x;  
			Tree_DP(table[i].to);  
	  
			{  
				long long min_sta=min(min(f[table[i].to],g[table[i].to]),h[table[i].to]);  
				long long ans=0;  
				if(f[table[i].to]==min_sta)  
					ans+=F[table[i].to];  
				if(g[table[i].to]==min_sta)  
					ans+=G[table[i].to];  
				if(h[table[i].to]==min_sta)  
					ans+=H[table[i].to];  
				f[x]+=min_sta;  
				F[x]=(ans*F[x])%MOD;  
			}  
	  
			{  
				long long min_sta=min(min(g[x]+f[table[i].to],g[x]+g[table[i].to]),h[x]+f[table[i].to]);  
				long long ans=0;  
				if(g[x]+f[table[i].to]==min_sta)  
					ans+=(G[x]*F[table[i].to])%MOD;  
				if(g[x]+g[table[i].to]==min_sta)  
					ans+=(G[x]*G[table[i].to])%MOD;  
				if(h[x]+f[table[i].to]==min_sta)  
					ans+=(H[x]*F[table[i].to])%MOD;  
				g[x]=min_sta;  
				G[x]=ans%MOD;  
			}  
	  
			{  
				h[x]+=g[table[i].to];  
				H[x]=(H[x]*G[table[i].to])%MOD;  
			}
		}
		printf("%d :  %lld %lld %lld\n",x,f[x],g[x],h[x]);
	}  
	int main()  
	{  
		int i,x,y;  
		cin>>n;  
		for(i=1;i<n;i++)  
		{  
			scanf("%d%d",&x,&y);  
			Add(x,y);Add(y,x);  
		}  
		Tree_DP(1);  
		cout<<min(f[1],g[1])<<endl;  
		cout<<( (f[1]==g[1]) ? ((F[1]+G[1])%MOD) : (f[1]<g[1]?F[1]:G[1]) )<<endl;  
	}  
