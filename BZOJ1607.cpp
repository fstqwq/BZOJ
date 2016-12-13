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

#define MAX_VAL 1000005
#define MAXN 100005

int n;
int a[MAXN],cnt[MAX_VAL],ans[MAX_VAL];

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",a+i);
		cnt[a[i]]++;
	}
	for (int i=1;i<=1000000;i++) {
		if (cnt[i]) {
			for (int j=i;j<=1000000;j+=i) {
				ans[j]+=cnt[i];
			}
		}
	}
	for (int i=1;i<=n;i++) {
		printf("%d\n",ans[a[i]]-1);
	}
	return 0;
}

