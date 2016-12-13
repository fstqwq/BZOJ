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
int ch=0;
inline void read(int &a) {
	while (ch<'0' || ch>'9') ch=getchar();
	a=0;
	while (ch>='0' && ch<='9') {a=a*10+ch-'0';ch=getchar();}
}
typedef long long LL;
LL A=1234,B=101,C=107,M=19260817;
const double eps=1e-6;
int Rand() {
	A=(A*B+C)%M;
	return int(A);
}

struct point {
	double x,y;
	point(){}
	point(double _x,double _y):x(_x),y(_y){}
}p[500005];
double dis(point a,point b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
point mid(point a,point b) {
	return point((a.x+b.x)/2,(a.y+b.y)/2);
}

point center(point a,point b,point c) {
    double a1=b.x-a.x,b1=b.y-a.y,c1=(a1*a1+b1*b1)/2;
    double a2=c.x-a.x,b2=c.y-a.y,c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    return (point){a.x+(c1*b2-c2*b1)/d,a.y+(a1*c2-a2*c1)/d};
}
int n;
int main() {
	read(n);
	for (int i=1;i<=n;i++) {
		scanf("%lf%lf",&p[i].x,&p[i].y);
	}
	point O=p[1];
	double r=0;
	for (int i=2;i<=n;i++) {
		if (dis(O,p[i])>eps+r) {
			O=p[i];r=0;
			for (int j=1;j<i;j++)
				if (dis(O,p[j])>eps+r) {
					O=mid(p[i],p[j]);
					r=dis(O,p[j]);
					for (int k=1;k<j;k++) {
						if (dis(O,p[k])>eps+r) {
							O=center(p[i],p[j],p[k]);
							r=dis(O,p[j]);
						}
					}
				}
		}
	}
	printf("%.2lf %.2lf %.2lf\n",O.x,O.y,r);
	return 0;
}

