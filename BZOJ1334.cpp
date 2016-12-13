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

int n;
int a[305],dp[100005],sum=0;

int main() {
	read(n);
	for (int i=1;i<=n;i++) read(a[i]),sum+=a[i];
	sort(a+1,a+n+1);
	int tot=sum/2;
	dp[0]=1;
	for (int i=n;i;i--) {
		for (int j=tot;j>=0;j--) dp[j+a[i]]|=dp[j];
	}
	int ans=0;
	for (int i=1;i<=sum;i++) if (dp[i]) ans=i;
	printf("%d\n",ans);
	return 0;
}

