/*ID: lpjwork1
TASK: fc
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
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<iomanip>
using namespace std;
const int MAXN=10000;
const double PI=3.1415926;
struct Vertice{
	int ind;
	double x,y;
} vertics[MAXN+10],midp;
int N;
/*angle with x axis*/
double angle[MAXN+10];
bool cmp(Vertice& a,Vertice& b)
{
	return angle[a.ind]<angle[b.ind];
}
vector<Vertice> chosen;

double dist(double,double,double,double);
double get_diff(Vertice&,Vertice&,Vertice&);
ofstream fout ("fc.out");
ifstream fin ("fc.in");
int main() {
	fin>>N;
	for (int i=0;i<N;i++)
	{
		double x,y;fin>>x>>y;
		vertics[i]=Vertice{i,x,y};
		midp.x+=x;midp.y+=y;
	}
	midp.x/=N;midp.y/=N;
	for (int i=0;i<N;i++)
	{
		angle[i]=atan2(vertics[i].y-midp.y,vertics[i].x-midp.x)*180/PI;
		if (angle[i]<0)	angle[i]+=360;
	}
	sort(vertics,vertics+N,cmp);
	chosen.push_back(vertics[0]);chosen.push_back(vertics[1]);
	for (int i=2;i<N;i++)
	{
		while (1)
		{
			int n=chosen.size();
			double diff=get_diff(chosen[n-2],chosen[n-1],vertics[i]);
			if (diff>180)	chosen.pop_back();
			else			break;
		}
		chosen.push_back(vertics[i]);
	}
	while (1)
	{
		int n=chosen.size();
		Vertice& last=chosen[n-1],& nlast=chosen[n-2],& first=chosen[0];
		double diff=get_diff(nlast,last,first);
		if (diff>180){
			chosen.pop_back();continue;
		}
		//else
		Vertice& a=chosen[n-1],&b=chosen[0],&c=chosen[1];
		diff=get_diff(a,b,c);
		if (diff>180){
			chosen.erase(chosen.begin());continue;
		}
		//else
		break;
	}
	double ans=dist(chosen.back().x,chosen.back().y,chosen[0].x,chosen[0].y);
	for (int i=0;i<chosen.size()-1;i++)	ans+=dist(chosen[i].x,chosen[i].y,chosen[i+1].x,chosen[i+1].y);
	fout<<fixed<<setprecision(2)<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

double dist(double x1,double y1,double x2,double y2)
{
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

double get_diff(Vertice& fir,Vertice& sec,Vertice& thir)
{
	double 	angle21=atan2(fir.y-sec.y,fir.x-sec.x)*180/PI,
			angle23=atan2(thir.y-sec.y,thir.x-sec.x)*180/PI,
			diff;
	if (angle21<0)	angle21+=360;
	if (angle23<0)	angle23+=360;
	diff=angle21-angle23;
	if (diff<0)	diff+=360;
	return diff;
}
