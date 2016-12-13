/*  Never stop fighting for what you believe in.    */
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
typedef long long LL;
int ch=0;
inline void read(int &a) {
    while (ch<'0' || ch>'9') ch=getchar();
    a=0;
    while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
inline void read(LL &a) {
    while (ch<'0' || ch>'9') ch=getchar();
    a=0;
    while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
struct node {
    LL s;
    int h;
    node(){}
    node(LL a,int b):s(a),h(b){}
    bool operator < (node a) const {
        if (s!=a.s) return s>a.s;
        else return h>a.h;
    }
};
priority_queue<node> q;
int n,K,ansh=0;
LL ans=0;
int main() {
    read(n);read(K);
    for (int i=1;i<=n;i++) {
		LL w;
        read(w);
        q.push(node(w,1));
    }
    if ((n-1)%(K-1)) for (int i=(K-1)-((n-1)%(K-1));i;i--) q.push(node(0,1));
    while (!q.empty()) {
        LL sum=0;
        int h=0;
        for (int i=1;i<=K && !q.empty();i++) {
            node a=q.top();q.pop();
            sum+=a.s;h=max(h,a.h);
        }
        h++;
        ans+=sum;
        if (q.empty()) {
            ansh=h-1;
            break;
        }
        q.push(node(sum,h));
    }
    printf("%lld\n%d\n",ans,ansh);
    return 0;
}
