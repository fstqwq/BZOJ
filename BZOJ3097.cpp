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

int n=100000,l=2048;
int top=1;
char a[200005];

void init() {
	a[1]='b';
	while (top<100000) {
		int x=top;
		for (int i=1;i<=x;i++) {
			a[++top]=a[i]^1;
		}
	}
	a[90000]='b';
	for (int i=90001;i<=100000;i++) {
		a[i]='a';
		if (i%l==0) a[i]='b';
	}
	a[100001]='\0';
}

int main() {
	init();
	printf("%d %d\n%s\n",n,l,a+1);
	return 0;
}

