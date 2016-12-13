/*	Never stop fighting for what you believe in.	*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>

int n;
int v,cnt,i,x;

int main() {
	scanf("%d",&n);
	cnt=0;
	for (i=1;i<=n;i++) {
		scanf("%d",&x);
		if (cnt==0) v=x,cnt=1;
		else {
			if (x==v) cnt++;
			else cnt--;
		}
	}
	printf("%d\n",v);
	return 0;
}

