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

#define MAXN 100005

LL n,m,lim,ans=0,f[MAXN];

int main() {
	cin>>n>>m;
	lim=min(n,m);
	for (LL i=lim;i>0;i--) {
		f[i]=LL(n/i)*LL(m/i);
		for (LL j=i*2;j<=lim;j+=i) f[i]-=f[j];
		ans+=f[i]*(2*i-1);
	}
	cout<<ans<<endl;
	return 0;
}

