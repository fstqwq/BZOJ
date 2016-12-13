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


bool map[4][4][4],dp[205][205][4];

int num[4],n;
char s[205],dd[5]="WING";

int rev(char x) {
	if (x=='W') return 0;
	if (x=='I') return 1;
	if (x=='N') return 2;
	return 3;
}

int main() {
	for (int i=0;i<4;i++) scanf("%d",num+i);
	for (int i=0;i<4;i++) {
		for (int j=1;j<=num[i];j++) {
			scanf("%s",s);
			map[i][rev(s[0])][rev(s[1])]=1;
		}
	}
	s[0]=s[1]=0;
	scanf("%s",s+1);
	n=(int)strlen(s+1);
	for (int i=1;i<=n;i++)
		dp[i][i][rev(s[i])]=1;
	for (int len=1;len<n;len++) {
		for (int i=1,j=1+len;j<=n;i++,j++) {
			for (int k=i;k<j;k++) {
				for (int q=0;q<4;q++) {
					if (dp[i][k][q]) for (int w=0;w<4;w++) {
						if (dp[k+1][j][w]) for (int e=0;e<4;e++) {
							if (map[e][q][w]) dp[i][j][e]=1;
						}
					}
				}
			}
		}
	}
	bool flag=1;
	for (int i=0;i<4;i++) {
		if (dp[1][n][i]) {
			putchar(dd[i]);
			flag=0;
		}
	}
	if (flag) puts("The name is wrong!");
	else putchar('\n');
	return 0;
}

