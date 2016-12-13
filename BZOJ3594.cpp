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
#define MAXH 6005
#define MAXK 505
#define lowbit(x) (x&(-x))

int n,k,ans=0;
int a[MAXN];
int t[MAXH][MAXK];

inline int query(int x,int y) {
	int ret=0;
	for (int i=x;i;i-=lowbit(i))
		for (int j=y;j;j-=lowbit(j)) 
			ret=max(t[i][j],ret);
	return ret;
}

inline void update(int x,int y,int v) {
	for (int i=x;i<=MAXH;i+=lowbit(i))
		for (int j=y;j<=MAXK;j+=lowbit(j))
			t[i][j]=max(t[i][j],v);
}

int main() {
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++) {
		scanf("%d",a+i);
	}
	for (int i=1;i<=n;i++)
		for (int j=k;j!=-1;j--) {
			int now=query(a[i]+j,j+1)+1;
			ans=max(ans,now);
			update(a[i]+j,j+1,now);
		}
	printf("%d\n",ans);
	return 0;
}

