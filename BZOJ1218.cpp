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


#define MAXN 10005
#define LIM 5002

int n,r,sum[LIM][LIM];

int main() {
	scanf("%d%d",&n,&r);
	for (int i=1,x,y,v;i<=n;i++) {
		scanf("%d%d%d",&x,&y,&v);
		sum[x+1][y+1]=v;
	}
	for (int i=1;i<LIM;i++) {
		for (int j=1;j<LIM;j++) {
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		}
	}
	int ans=0;
	for (int i=r;i<LIM;i++)
		for (int j=r;j<LIM;j++) {
			ans=max(ans,sum[i][j]-sum[i-r][j]-sum[i][j-r]+sum[i-r][j-r]);
		}
	printf("%d\n",ans);
	return 0;
}

