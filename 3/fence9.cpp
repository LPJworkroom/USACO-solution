/*ID: lpjwork1
TASK: fence9
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<string.h>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>
#include<fstream>
#include<cmath>
//#include<stdlib.h>
using namespace std;
struct line{
	int px,py;
	double k;
	double ret_x(int y)
	{
		//if (k>(1<<30))	return px;
		return ((double)y-py)/k+px;
	}
};
ofstream fout ("fence9.out");
ifstream fin ("fence9.in");
int main() {
	double x1,y1,x2;fin>>x1>>y1>>x2;
	int ans=0;
	line line1{0,0,y1/x1},line2{x2,0,y1/(x1-x2)};
	for (int i=1;i<y1;i++)
	{
		double ld=line1.ret_x(i),rd=line2.ret_x(i);
		int l=ld+1,r=rd;
		if (fabs(ld-l)<0.000001)	l++;
		if (fabs(rd-r)<0.000001)	r--;
		//cout<<i<<'|'<<ld<<' '<<rd<<' '<<l<<' '<<r<<' '<<endl;
		if (r<l)	continue;
		ans+=(r-l+1);
		//cout<<ans<<endl;
	}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}
