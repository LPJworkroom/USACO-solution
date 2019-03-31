/*ID: lpjwork1
TASK: ariprog
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<string.h>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#include<fstream>
using namespace std;
const int MAXM=250+10;
int N,M;
//set<int> bsq;
bool bsq[MAXM*MAXM*2];
//bool acan[MAXM*MAXM*2];
bool none=true;
vector<int> as;
ofstream fout ("ariprog.out");
ifstream fin ("ariprog.in");

int main() {
	memset(bsq,false,sizeof(bsq));
	fin>>N>>M;
	for (int i=0;i<=M;i++)	for (int j=0;j<=M;j++)
	{
		bsq[i*i+j*j]=true;
		as.push_back(i*i+j*j);
	}
	sort(as.begin(),as.end());
	//for (int i=0;i<as.size();i++)	cout<<as[i]<<' ';cout<<endl;
	int aend=unique(as.begin(),as.end())-as.begin();
	//cout<<aend<<endl;
	//for (int i=0;i<aend;i++)	cout<<as[i]<<' ';cout<<endl;
	int a,b;
	for (b=1;b<=2*M*M/(N-1);b++)
	{
		//cout<<b<<endl;	
		//memset(acan,true,sizeof(acan));
		for (int ind=0;ind<aend;ind++)
		{
			a=as[ind];
		//	if (!acan[a])	continue;
			int len;
			for (len=0;len<N;len++)
				if (!bsq[a+b*len])	break;				//failed
			if (len==N){												//ok
				fout<<a<<' '<<b<<endl;
				none=false;
			}
		//	else	for (int i=0;i<len;i++)	acan[a+i*b]=false;
		}
	}
	if (none)	fout<<"NONE"<<endl;
    fout.close();fin.close();
    return 0;
}
