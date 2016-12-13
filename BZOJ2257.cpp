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
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
#define MAXN 1005
int n,k,ans;
int v[MAXN];

void check(int x) {
	if (x<=ans) return;
	int cnt=0;
	for (int i=1;i<=n;i++) {
		if (!(v[i]%x)) cnt++;
	}
	if (cnt>=k) ans=x;
}

int main() {
	read(n);read(k);
	for (int i=1;i<=n;i++) read(v[i]);
	ans=1;
	for (int i=1;i<=n;i++) {
		for (int j=2,sqn=(int)sqrt(v[i]);j<=sqn;j++) {
			if (!(v[i]%j)) {
				check(j);
				check(v[i]/j);
			}
		}
		check(v[i]);
	}
	printf("%d\n",ans);
	return 0;
}

