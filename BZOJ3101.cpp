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


int n;
int main() {
	scanf("%d",&n);
	if (n%6!=2 && n%6!=3) {
		for (int i=2;i<=n;i+=2) printf("%d\n",i);
		for (int i=1;i<=n;i+=2) printf("%d\n",i);
	}
	else {
		int k=n/2;
		if(k&1){
			for(int i=k;i<=n-1;i+=2)printf("%d\n",i);
			for(int i=1;i<=k-2;i+=2)printf("%d\n",i);
			for(int i=k+3;i<=n;i+=2)printf("%d\n",i);
			for(int i=2;i<=k+1;i+=2)printf("%d\n",i);
		} else {
			for(int i=k;i<=n;i+=2)printf("%d\n",i);
			for(int i=2;i<=k-2;i+=2)printf("%d\n",i);
			for(int i=k+3;i<=n-1;i+=2)printf("%d\n",i);
			for(int i=1;i<=k+1;i+=2)printf("%d\n",i);
		}
		if(n&1)printf("%d\n",n);
	}
	return 0;
}

