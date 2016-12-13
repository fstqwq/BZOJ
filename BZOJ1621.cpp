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

int n,k,ans=0;

void dfs(int x) {
	if (x>k && !((x+k)&1) && !((x-k)&1)) {
		dfs((x+k)>>1);
		dfs((x-k)>>1);
		return;
	}
	ans++;
}

int main() {
	read(n);read(k);
	dfs(n);
	printf("%d\n",ans);
	return 0;
}

