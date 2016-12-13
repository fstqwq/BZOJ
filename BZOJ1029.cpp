/*This is a source code from FirstLast*/
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
#define MAXN 150005

struct data{
	int t,r;
	bool operator < (data a) const {
		return r<a.r;
	}
}b[MAXN];

int n;

int main() {
	priority_queue<int> q;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&b[i].t,&b[i].r);
	}
	sort(b+1,b+n+1);
	int total=0,ans=0;
	for (int i=1;i<=n;i++) {
		if (b[i].r-total>=b[i].t) {
			total+=b[i].t;
			q.push(b[i].t);
			ans++;
		}
		else {
			if (b[i].t<q.top()) {
				total-=q.top()-b[i].t;
				q.pop();
				q.push(b[i].t);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}

