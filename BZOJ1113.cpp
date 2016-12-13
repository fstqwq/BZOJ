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
#define MAXN 250005
int n;
int sta[MAXN],top=0,ans=0;
int main() {
	read(n);
	sta[top]=0;
	for (int i=1,l,w;i<=n;i++) {
		read(l);read(w);
		while (sta[top]>w) top--;
		if (sta[top]!=w) {
			sta[++top]=w;
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}

