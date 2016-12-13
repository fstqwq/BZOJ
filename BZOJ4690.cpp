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

#define MAXN 100005

int n,m;
int f[MAXN],rank[MAXN];

int getf(int x) {
	if (f[x]==x) {
		rank[x]=0;
		return f[x];
	}
	int pref=f[x];
	f[x]=getf(f[x]);
	rank[x]+=rank[pref];
	return f[x];
}
void merge(int a,int b,int val) {
	int fa=getf(a),fb=getf(b);
	if (fa!=fb) {
		f[fa]=fb;
		rank[fa]=rank[b]-rank[a]+val;
	}
}
char op[5];
int main() {
	while (scanf("%d%d",&n,&m)!=EOF && n && m) {
		for (int i=1;i<=n;i++) f[i]=i,rank[i]=0;
		for (int i=1,a,b,w;i<=m;i++) {
			scanf("%s",op);
			if (op[0]=='!') {
				scanf("%d%d%d",&a,&b,&w);
				merge(a,b,w);
			}
			else {
				scanf("%d%d",&a,&b);
				if (getf(a)!=getf(b)) puts("UNKNOWN");
				else printf("%d\n",rank[a]-rank[b]);
			}
		}
	}
	return 0;
}

