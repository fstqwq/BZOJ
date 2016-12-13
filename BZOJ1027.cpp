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
 
#define MAXN 505
#define eps 1e-9
struct point {
    double x,y;
    point(){}
    point(double a,double b):x(a),y(b){}
    point operator - (point a) const {
        return point(x-a.x,y-a.y);
    }
    double operator * (point a) const {
        return x*a.y-a.x*y;
    }
    double operator ^ (point a) const {
        return x*a.x+y*a.y;
    }
}a[MAXN],b[MAXN];
 
double fun;
int m,n;
int map[MAXN][MAXN];
 
inline bool spj() {
    for (int i=2;i<=n;i++) {
        if (b[i].x!=b[i-1].x || b[i].y!=b[i-1].y) return 0;
    }
    for (int i=1;i<=m;i++) {
        if (b[1].x==a[i].x && b[1].y==a[i].y) return 1;
    }
    return 0;
}
 
inline int check(point st,point ed) {
    int cnt1=0,cnt2=0;
    for (int i=1;i<=n;i++) {
        double x=(ed-st)*(b[i]-st);
        if (!(x+eps>0 && x-eps<0)) {
            if (x>0) {
                cnt1++;
            }
            else {
                cnt2++;
            }
        }
    }
    int ret=0;
    if (!cnt1) ret=1;
    if (!cnt2) ret+=2;
    return ret;
}
 
inline bool allin(point x,point y) {
    for (int i=1;i<=n;i++) {
        if (((b[i]-x)^(y-b[i]))+eps<0) return 0;
    }
    return 1;
}
 
inline bool build() {
    memset(map,31,sizeof(map));
    for (int i=1;i<m;i++)
        for (int j=i+1;j<=m;j++) {
            int ret=check(a[i],a[j]);
            if (ret==3) {
                if (allin(a[i],a[j])) return 1;
                else continue;
            }
            if (ret&1) map[i][j]=1;
            if (ret&2) map[j][i]=1;
        }
    return 0;
}
 
inline void work() {
    for (int k=1;k<=m;k++)
        for (int i=1;i<=m;i++)
            for (int j=1;j<=m;j++) {
                if (map[i][j]>map[i][k]+map[k][j]) map[i][j]=map[i][k]+map[k][j];
            }
    int ans=m+1;
    for (int i=1;i<=m;i++) {
        if (map[i][i]<ans) ans=map[i][i];
    }
    if (ans>m) puts("-1");
    else printf("%d\n",ans);
}
 
int main() {
    scanf("%d%d",&m,&n);
    for (int i=1;i<=m;i++) {
        scanf("%lf%lf%lf",&a[i].x,&a[i].y,&fun);
    }
    for (int i=1;i<=n;i++) {
        scanf("%lf%lf%lf",&b[i].x,&b[i].y,&fun);
    }
    if (spj()) puts("1");
    else if (build()) puts("2");
    else work();
    return 0;
}
