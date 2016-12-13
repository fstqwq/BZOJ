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

struct task {
	long long num,arr,exe,val;
	task(){}
	task(long long a,long long b,long long c,long long d):num(a),arr(b),exe(c),val(d){}
	bool operator < (task a) const {
		if (val!=a.val) return val<a.val;
		return arr>a.arr;
	}
};

priority_queue<task> q;

int main() {
	long long a,b,c,d;
	long long t=-1;
	q.push(task(-1,-1,1000000000000000ll,-1));
	while (scanf("%lld%lld%lld%lld",&a,&b,&c,&d)!=EOF) {
		task now=q.top();q.pop();
		while (b-t>=now.exe) {
			t+=now.exe;
			printf("%lld %lld\n",now.num,t);
			now=q.top();q.pop();
		}
		if (b>t) {
			if (now.num!=-1) now.exe-=(b-t);
			t=b;
		}
		q.push(now);
		q.push(task(a,b,c,d));
	}
	while (q.top().num!=-1) {
		task now=q.top();q.pop();
		t+=now.exe;
		printf("%lld %lld\n",now.num,t);
	}
	return 0;
}

