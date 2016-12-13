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

const long long top=10000000000;

long long q[2100];
bool ban[2100];
int head=1,tail=1;
void init() {
	q[tail++]=6;
	q[tail++]=8;
	while (head<tail) {
		long long now=q[head++];
		if (now*10+6<=top) q[tail++]=now*10+6;
		if (now*10+8<=top) q[tail++]=now*10+8;
	}
	for (int i=2;i<tail;i++) {
		for (int j=1;j<i;j++) {
			if (!ban[j] && q[i]%q[j]==0) {
				ban[i]=1;
				break;
			}
		}
	}
}

long long work(long long x) {
	long long ans=0;
	for (int i=1;i<tail;i++) {
		if (!ban[i]) ans+=x/q[i];
	}
	return ans;
}

int main() {
	long long a,b;
	init();
	cin>>a>>b;
	cout<<work(b)-work(a-1)<<endl;
	return 0;
}

