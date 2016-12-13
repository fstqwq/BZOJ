#include<cstdio>
#include<algorithm>
using namespace std;
 
#define maxn 1000001
#define INF 0x7f7f7f7f
inline void read(int &a){ 
    char ch;
    while(!(((ch=getchar())>='0')&&(ch<='9')));a=ch-'0';
    while(((ch=getchar())>='0')&&(ch<='9'))a*=10,a+=ch-'0'; 
}
int N,l,r,last[maxn],q[maxn],a[maxn],s,ans;
inline void Kap(int l,int r,int p){if(p>r)return;if(a[p]>ans&&r-l+1>=a[p])ans=a[p];}
int main(){
    read(N);
    q[r+1]=INF;
    for(int i=1;i<=N;++i){
        read(a[i]);
        if(last[a[i]]>=s) s=last[a[i]]+1;
        while(q[l]<=last[a[i]]) Kap(q[l]+1,i-1,q[l+1]),++l;
		last[a[i]]=i;
        while(r>=l&&a[i]>=a[q[r]]) Kap(max(q[r-1]+1,s),i-1,q[r]),--r;
        q[++r]=i,q[r+1]=INF;
        if(a[q[l]]>ans&&i-s+1>=a[q[l]])ans=a[q[l]];
    }
    while(l<=r)Kap(q[l]+1,N,q[l+1]),++l;
    printf("%d\n",ans);
	}
