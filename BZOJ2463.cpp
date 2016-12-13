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


int main() {
	int n=0;
	while (scanf("%d",&n)!=EOF && n) {
		if (n&1) puts("Bob");
		else puts("Alice");
	}
	return 0;
}

