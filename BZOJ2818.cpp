/*	Never stop fighting for what you believe in.	*/
#include <iostream>
using namespace std;

#define MAXN 10000005

#define LL long long

bool mark[MAXN];
int n,p[1000005],pcnt=0;
LL ans=0,sum[MAXN],phi[MAXN];

void getphi() {
	sum[1]=phi[1]=1;
	for (int i=2;i<=n;i++) {
		if (!mark[i]) {
			p[++pcnt]=i;
			phi[i]=i-1;
		}
		for (int j=1;j<=pcnt;j++) {
			if (i*p[j]>n) break;
			mark[i*p[j]]=1;
			if (i%p[j]==0) {
				phi[i*p[j]]=p[j]*phi[i];
				break;
			}
			else {
				phi[i*p[j]]=(p[j]-1)*phi[i];
			}
		}
	}
}

int main() {
	cin>>n;
	getphi();
	for (int i=2;i<=n;i++) {
		sum[i]=sum[i-1]+phi[i];
	}
	for (int i=1;i<=pcnt;i++) {
		ans+=(sum[n/p[i]])*2-1;
	}
	cout<<ans<<endl;
	return 0;
}

