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
#define MAXN 50005
int n,w,ans=0;
int top,sta[MAXN];
int main() {
	read(n);read(w);
	for (int i=1,fun,h;i<=n;i++) {
		read(fun);read(h);
		while (top && sta[top]>h) top--;
		if (sta[top]==h) continue;
		sta[++top]=h;
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}

