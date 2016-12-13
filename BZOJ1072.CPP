/*This is a source code from FirstLast*/
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

int n,d,top,pp[15],cnt[15],dp[1024][1005];
int num[15][300],ncnt[15];
char s[20];

inline void init() {
	n=strlen(s);
	top=(1<<n)-1;
	memset(cnt,0,sizeof(cnt));
	memset(ncnt,0,sizeof(ncnt));
	memset(dp,0,sizeof(dp));
	for (int i=0;i<=top;i++) {
		int temp=i,ans=0;
		while (temp) {
			temp-=temp&-temp;
			ans++;
		}
		num[ans][++ncnt[ans]]=i;
	}
	pp[0]=1%d;
	for (int i=1;i<=n;i++) {
		pp[i]=(pp[i-1]*10)%d;
	}
}

inline void work() {
	dp[0][0]=1;
	for (int i=0;i<n;i++) {
		int now=s[i]-'0';
		cnt[now]++;
		for (int j=1;j<=ncnt[i];j++) {
			int x=num[i][j];
			for (int k=0;k<n;k++) {
				if (!((x>>k)&1)) {
					int to=x|(1<<k);
					for (int q=0;q<d;q++) {
						if (dp[x][q]) {
							dp[to][(q+pp[k]*now)%d]+=dp[x][q];
						}
					}
				}
			}
		}
	}
	int ans=dp[top][0];
	for (int i=0;i<10;i++) {
		for (int j=2;j<=cnt[i];j++) {
			ans/=j;
		}
	}
	printf("%d\n",ans);
}

int main() {
	int t;
	scanf("%d",&t);
	while (t--) {
		scanf("%s%d",s,&d);
		init();
		work();
	}
	return 0;
}


