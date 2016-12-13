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
#include <map>
using namespace std;

map <int,bool> m;
#define MAXN 50005
int n,T;
int a[MAXN],cnt=0;
int main() {
	scanf("%d",&T);
	while (T--) {
		scanf("%d",&n);
		m.clear();
		cnt=0;
		for (int i=1,v;i<=n;i++) {
			scanf("%d",&v);
			if (!m[v]) {
				m[v]=1;
				a[++cnt]=v;
			}
		}
		for (int i=1;i<cnt;i++) {
			printf("%d ",a[i]);
		}
		if (cnt>0) printf("%d\n",a[cnt]);
	}

	return 0;
}

