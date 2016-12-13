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


int n=100000,l=20;

int main() {
	printf("%d %d\n",n,l);
	for (int i=1;i<=n;i++) {
		putchar('a'+rand()%26);
	}
	putchar('\n');
	return 0;
}

