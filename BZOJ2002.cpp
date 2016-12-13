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
#define MAXN 201005
#define sqrtN 1005
int n,m,sqn;
int a[MAXN],step[MAXN],to[MAXN],block[MAXN];

inline void init() {
	sqn=int(sqrt(n));
	int now=0;
	for (int i=1;i<=sqn;i++) {
		for (int j=1;j<=sqn;j++) {
			block[now++]=i;
		}
	}
	while (now<n) {
		block[now++]=sqn+1;
	}
	block[n]=-1;
	step[n]=0;
	to[n]=n;
	for (int i=n-1;i>-1;i--) {
		to[i]=min(n,i+a[i]);
		if (block[i]!=block[to[i]]) {
			step[i]=1;
		}
		else {
			step[i]=step[to[i]]+1;
			to[i]=to[to[i]];
		}
	}
}

int main() {
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",a+i);
	}
	init();
	scanf("%d",&m);
	for (int t=1;t<=m;t++) {
		int x,y,z;
		scanf("%d%d",&x,&y);
		if (x==1) {
			int now=y,ans=0;
			while (now<n) {
				ans+=step[now];
				now=to[now];
			}
			printf("%d\n",ans);
		}
		else {
			scanf("%d",&z);
			a[y]=z;
			int nowblock=block[y];
			for (int i=y;i>-1 && block[i]==nowblock;i--) {
				to[i]=min(n,i+a[i]);
				if (block[i]!=block[to[i]]) {
					step[i]=1;
				}
				else {
					step[i]=step[to[i]]+1;
					to[i]=to[to[i]];
				}
			}
		}
	}
	return 0;
}

