#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define LL long long
using namespace std;
LL r,ans;
LL gcd(LL a,LL b)
{
    return !b?a:gcd(b,a%b);
}
bool pd(LL a,double b)
{
    if (floor(b)==b)
    {
        LL tmpb=(LL)(floor(b));
        if (gcd(tmpb*tmpb,a*a)==1&&tmpb*tmpb!=a*a)  return 1;
    }
    return 0;
}
int main()
{
	freopen("read.in","r",stdin);
	freopen("ans.out","w",stdout);
    scanf("%lld",&r);
    for (LL d=1;d<=(LL)(sqrt(2*r));d++)
    {
        if (2*r%d==0)
        {
            for (LL a=1;a<=(LL)(sqrt((2*r)/(2*d)));a++)
            {
                double b=sqrt(2*r/d-a*a);
                if (pd(a,b))    ans++;
            }
            if (d!=2*r/d)
            {
                for (LL a=1;a<=(LL)(sqrt(d/2));a++)
                {
                    double b=sqrt(d-a*a);
                    if (pd(a,b))    ans++;
                }
            }
        }
    }
    printf("%lld",ans*4+4);
}
