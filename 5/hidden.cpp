/*ID: lpjwork1
TASK: hidden
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
#include<list>
#include<fstream>
using namespace std;
const int MAXN=100000+10;
struct qnode{
	int begin,now;
};
bool fail[MAXN];
int N,tot=0;
qnode seed[MAXN];

string data;

void showseed();
ofstream fout ("hidden.out");
ifstream fin ("hidden.in");
int main() {
	fin>>N;
	while (1)
	{
		string tmp;fin>>tmp;
		if (tmp.empty())	break;
		data+=tmp;
	}
//	cout<<data<<endl;
	for (int i=0;i<N;i++)	fail[i]=true;
	char minc=data[0];
	for (int i=0;i<N;i++)	minc=min(minc,data[i]);
	for (int i=0;i<N;i++)
	{
		if (data[i]==minc){
			fail[i]=false;
			seed[tot++]=qnode{i,(i+1)%N};
//			seed.push_back(qnode{i,(i+1)%N});
		}
	}
	while (tot!=1)
	{
//		showseed();
		
		minc=data[seed[0].now];
		for (int i=0;i<tot;i++)
			minc=min(data[seed[i].now],minc);
		cout<<"minc:"<<minc<<endl;
		int newtot=0;
		for (int i=0;i<tot;i++)
		{
			/*not minc*/
			if (data[seed[i].now]!=minc)	continue;
			/*equal,test cover next or not*/
			if (!fail[seed[i].now])	fail[seed[i].now]=true;
			seed[i].now++;
			seed[i].now%=N;
			seed[newtot++]=seed[i];
		}
		tot=newtot;
		newtot=0;
		for (int i=0;i<tot;i++)
		{
			if (fail[seed[i].begin])	continue;
			seed[newtot++]=seed[i];
		}
		if (newtot==0)	tot=1;
		else	tot=newtot;
	}
	fout<<seed[0].begin<<endl;
    fout.close();fin.close();
    return 0;
}
