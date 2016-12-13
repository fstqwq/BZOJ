#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
#define LL long long
struct H{
    LL w; int l;
    bool operator < (const H &a) const {
        if (w!=a.w) return a.w<w;
        return a.l<l;
    }
};
priority_queue<H> h;
int n,k,nn; LL ans=0;
int in(){
    int x=0; char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return x;
}
LL Lin(){
    LL x=0; char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9') x=x*10+(LL)(ch-'0'),ch=getchar();
    return x;
}
int main(){
    n=in(),k=in(); nn=n;
    for (int i=1; i<=n; i++){
        LL x=Lin();
        h.push((H){x,1});
    }
    if ((n-1)%(k-1)) nn+=(k-1)-((n-1)%(k-1));
    for (int i=n+1; i<=nn; i++)
        h.push((H){0,1});
    while (nn>1){
        LL s1=0; int s2=0;
        for (int i=1; i<=k; i++){
            H x=h.top(); h.pop();
            s1+=x.w; s2=max(s2,x.l);
        }
        ans+=s1; nn-=(k-1);
        h.push((H){s1,s2+1});
    }
    printf("%lld\n%d\n",ans,h.top().l-1);
    return 0;
}
