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

#define MOD 100000007

long long C[1005][1005];

void init() {
	for (int i=0;i<=1000;i++) {
		C[i][0]=1;
		for (int j=1;j<=i;j++) {
			C[i][j]=C[i-1][j]+C[i-1][j-1];
			if (C[i][j]>=MOD) C[i][j]-=MOD;
		}
	}
}

bool visit[255];
long long g[35][35][255];

int n,m,c;

void initg(int k) {
	visit[k]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			long long s=0;
			for (int a=1;a<=i;a++)
				for (int b=1;b<=j;b++) {
					if (a!=i || b!=j) {
						s=(s+((g[a][b][k]*C[i][a])%MOD)*C[j][b])%MOD;
					}
				}
			g[i][j][k]=(C[i*j][k]-s)%MOD;
			if (g[i][j][k]<0) g[i][j][k]+=MOD;
		}
}

long long dp[15][35][35];

int main() {
	init();
	scanf("%d%d%d",&n,&m,&c);
	dp[0][0][0]=1;
	int tot=0;
	for (int t=1,cc;t<=c;t++) {
		scanf("%d",&cc);
		tot+=cc;
		if (cc==0) {
			t--,n--;
			continue;
		}
		if (cc>n*m) {
			puts("0");
			return 0;
		}
		if (!visit[cc]) initg(cc);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++) {
				if (g[i][j][cc]) {
					for (int a=0;a+i<=n;a++)
						for (int b=0;b+j<=m;b++) {
							if (dp[t-1][a][b]) {
								dp[t][a+i][b+j]=(dp[t][a+i][b+j]+((dp[t-1][a][b]*g[i][j][cc])%MOD)*((C[a+i][i]*C[b+j][j])%MOD))%MOD;
							}
						}
				}
			}
	}
	if (n*m<tot) {
		puts("0");
		return 0;
	}
	if (tot==0) {
		puts("1");
		return 0;
	}
	long long ans=0;
	for (int i=0;i<=n;i++) {
		for (int j=0;j<=m;j++) {
			ans=(ans+dp[c][i][j]*((C[n][i]*C[m][j])%MOD))%MOD;
		}
	}
	cout<<ans<<endl;
	return 0;
}


