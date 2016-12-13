/*	Never stop fighting for what you believe in.	*/
#include <cstdio>
using namespace std;

int main() {
	int a,b,c,d,e,f,g,h;
	unsigned long long ans;
	int t;
	scanf("%d",&t);
	while (t--) {
		scanf("%d%d%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f,&g,&h);
		scanf("%llu",&ans);
		if (a==60 && b==60 && c==60 && d==60 && e==60 && f==60 && g==60 && h==60 && ans==9223372036854775808llu) {
			puts("18446744073709551616");
		}
		else {
			printf("%llu\n",ans+(1llu<<a)+(1llu<<b)+(1llu<<c)+(1llu<<d)+(1llu<<e)+(1llu<<f)+(1llu<<g)+(1llu<<h));
		}
	}

	return 0;
}

