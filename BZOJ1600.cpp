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
typedef long long LL;
#define MAXN 2505

int n,n_2;
LL dp[MAXN][4];

int main() {
	scanf("%d",&n);
	n_2=(n-1)>>1;
	dp[0][0]=1;
	for (int i=1;i<n;i++) {
		for (int j=max(0,i-n_2);j<i;j++) {
			dp[i][1]+=dp[j][0];
			dp[i][2]+=dp[j][1];
			dp[i][3]+=dp[j][2];
		}
	}
	LL ans=0;
	for (int i=max(0,n-n_2);i<n;i++) {
		ans+=dp[i][3];
	}
	printf("%lld\n",ans);
	return 0;
}

