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
inline void readbit(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=(a<<1)+ch-'0';ch=getchar();}
}

int n,m;
int a[105],cnt[105];
int main() {
	read(n);read(m);
	for (int i=1;i<=m;i++) {
		readbit(a[i]);read(cnt[i]);
	}
	int ans=-1;
	for (int i=(1<<n)-1;i>-1;i--) {
		bool flag=1;
		for (int j=1;j<=m;j++) {
			if (__builtin_popcount(a[j]&i)!=cnt[j]) {flag=0;break;}
		}
		if (flag) {
			if (ans!=-1) {puts("NOT UNIQUE");return 0;}
			else ans=i;
		}
	}
	if (ans==-1) puts("IMPOSSIBLE");
	else {
		for (int i=n-1;i>-1;i--) {
			printf("%d",1&(ans>>i));
		}
	}

	return 0;
}

