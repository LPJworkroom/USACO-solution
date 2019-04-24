/*ID: lpjwork1
TASK: rectbarn
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<vector>
#include<string.h>
#include<algorithm>
#include<list>
#include<fstream>
using namespace std;
const int MAXP=30000+10;
/*srad==thread*/
struct srad{
	int u,d;
};
struct point{
	int x,y;
}badp[MAXP];

bool operator<(srad a,srad b)	
{
	if (a.u!=b.u)	return a.u<b.u;
	return a.d<b.d;
}
bool operator<(point a,point b)	{
	if (a.x!=b.x)	return a.x<b.x;
	return a.y<b.y;
}
list<srad> threads;
map<srad,int> life;
vector<int> xvec;
int R,C,P;
int tot=0;

void tryinsert(srad tmpnew,int lenth);
void check_cut(list<srad>::iterator&,int&,point&);
bool srad_contain(srad&,int);

ofstream fout ("rectbarn.out");
int main() {
	FILE* fin=fopen("rectbarn.in","r");
	fscanf(fin,"%d%d%d",&R,&C,&P);
	for (int i=0;i<P;i++)
	{
		fscanf(fin,"%d%d",&badp[i].y,&badp[i].x);
		xvec.push_back(badp[i].x);
	}
	
	sort(badp,badp+P);
	sort(xvec.begin(),xvec.end());
	xvec.resize(unique(xvec.begin(),xvec.end())-xvec.begin());
	
	threads.push_back(srad{1,R});
	life[srad{1,R}]=0;
	
	int pbad=0,ans=0;
	for (int i=0;i<xvec.size();i++)
	{
		tot=xvec[i]-1;
		/*for all bad point at this x coord*/
		for (;pbad<P&&badp[pbad].x==xvec[i];pbad++)
		{
			point bad=badp[pbad];
			for (auto it=threads.begin();it!=threads.end();)
			{
				if (srad_contain(*it,bad.y))	check_cut(it,ans,bad);
				else	it=next(it);
			}
		}
		life[srad{1,R}]=-xvec[i];
		threads.push_front(srad{1,R});
	}
	tot=C;
	for (auto it=threads.begin();it!=threads.end();it++)
	{
		srad now=*it;int lenth=life[now];
		ans=max(ans,(now.d-now.u+1)*(lenth+tot));
	}
	fout<<ans<<endl;
    fout.close();fclose(fin);
    return 0;
}

bool srad_contain(srad& a,int b)
{
	return a.u<=b&&a.d>=b;
}

void check_cut(list<srad>::iterator& it,int& ans,point& bad)
{
	srad& now=*it;int lenth=life[now];
	ans=max(ans,(now.d-now.u+1)*(lenth+tot));
	if (bad.y!=now.u)	tryinsert(srad{now.u,bad.y-1},lenth);
	if (bad.y!=now.d)	tryinsert(srad{bad.y+1,now.d},lenth);
	life.erase(now);
	it=threads.erase(it);
}

void tryinsert(srad tmpnew,int lenth)
{
	/*new thread*/
	if (life.find(tmpnew)==life.end()){
		threads.push_back(tmpnew);
		life[tmpnew]=lenth;
	}
	else	
		if (life[tmpnew]<lenth)	life[tmpnew]=lenth;
}
