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
#define MOD 1000000001
#define MAXN 100005
#define top 2048
typedef long long LL;
LL ans=1,dp[18][235];
int n,can[235],num[18][13],ccnt=0;
bool visit[MAXN];

void init() {
	for (int i=0;i<=top;i++) {
		if (!(i&(i>>1))) can[++ccnt]=i;
	}
}

void Modadd(LL &a,LL b) {
	a+=b;
	if (a>=MOD) a-=MOD;
}

void work(int x) {
	memset(dp,0,sizeof(dp));
	num[1][1]=x;
	dp[0][1]=1;
	int last=1;
	for (int i=1;;i++) {
		int cnt=1;
		visit[num[i][1]]=1;
		for (int j=2;;j++) {
			num[i][j]=num[i][j-1]*3;
			if (num[i][j]>n) break;
			cnt=j;
			visit[num[i][j]]=1;
		}
		int nowtop=1<<cnt,now=1;
		for (int j=1;;j++) {
			if (can[j]>=nowtop) break;
			now=j;
			for (int k=1;k<=last;k++) {
				if (!(can[j]&can[k])) Modadd(dp[i][j],dp[i-1][k]);
			}
		}
		last=now;
		num[i+1][1]=num[i][1]*2;
		if (num[i+1][1]>n) {
			LL ret=0;
			for (int j=1;j<=now;j++) {
				Modadd(ret,dp[i][j]);
			}
			ans=(ans*ret)%MOD;
			return;
		}
	}
}

int main() {
	init();
	read(n);
	for (int i=1;i<=n;i++) {
		if (!visit[i]) work(i);
	}
	printf("%lld\n",ans);
	return 0;
}

