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

int n;
const char p[]="luvletter";
const int m=9;
char s[100005];
int main() {
	int T;
	scanf("%d\n",&T);
	for (int i=1;i<=T;i++) {
		gets(s);
		int ans=0,len=(int)strlen(s);
		for (int j=0,pos=0;j<len;j++) {
			if (p[pos]==s[j]) {
				pos++;
				if (pos==9) ans++,pos=0;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

