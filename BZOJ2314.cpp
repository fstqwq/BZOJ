/*  Never stop fighting for what you believe in.	*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;
#define MAXN 500005
#define MOD 1032992941
struct edge {
	int next,to;
}e[MAXN<<1];
typedef long long LL;
int n,head[MAXN],ecnt=0;
LL cnt[MAXN][3],dp[MAXN][3];
// 0 - son 1 - self 2 - fa
void add(int u,int v) {
	e[++ecnt].to=v;
	e[ecnt].next=head[u];
	head[u]=ecnt;
	e[++ecnt].to=u;
	e[ecnt].next=head[v];
	head[v]=ecnt;
}
#define v e[now].to
void dfs(int x,int fa) {
	dp[x][0]=0;cnt[x][0]=1;
	dp[x][1]=1;cnt[x][1]=1;
	dp[x][2]=0x3f3f3f3f;cnt[x][2]=1;
	for (int now=head[x];now;now=e[now].next) {
		if (v!=fa) {
			dfs(v,x);
			LL minans=min(min(dp[v][0],dp[v][1]),dp[v][2]),sum=0;
			for (int i=0;i<3;i++) if (dp[v][i]==minans) sum+=cnt[v][i];
			dp[x][1]+=minans;
			cnt[x][1]=(cnt[x][1]*sum)%MOD;
			minans=min(min(dp[x][2]+dp[v][1],dp[x][2]+dp[v][2]),dp[x][0]+dp[v][1]);
			sum=0;
			if (dp[x][2]+dp[v][1]==minans) sum+=(cnt[x][2]*cnt[v][1])%MOD;
			if (dp[x][2]+dp[v][2]==minans) sum+=(cnt[x][2]*cnt[v][2])%MOD;
			if (dp[x][0]+dp[v][1]==minans) sum+=(cnt[x][0]*cnt[v][1])%MOD;
			dp[x][2]=minans;
			cnt[x][2]=sum%MOD;
			dp[x][0]+=dp[v][2];
			cnt[x][0]=(cnt[x][0]*cnt[v][2])%MOD;
		}
	}
}
#undef v
 
int main() {
	scanf("%d",&n);
	for (int i=1,u,v;i<n;i++) {
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	dfs(1,1);
	printf("%lld\n",min(dp[1][2],dp[1][1]));
	if (dp[1][2]<dp[1][1]) printf("%lld\n",cnt[1][2]%MOD);
	else if (dp[1][2]>dp[1][1]) printf("%lld\n",cnt[1][1]%MOD);
	else printf("%lld\n",(cnt[1][2]+cnt[1][1])%MOD);
	return 0;
}
