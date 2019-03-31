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
bool bsq[MAXM*MAXM*2],acan[MAXM*MAXM*2];
bool none=true;
ofstream fout ("ariprog.out");
ifstream fin ("ariprog.in");

int main() {
	memset(bsq,false,sizeof(bsq));
	fin>>N>>M;
	for (int i=0;i<=M;i++)	for (int j=0;j<=M;j++)	bsq[i*i+j*j]=true;
	int a,b;
	for (b=1;b<=2*M*M/(N-1);b++)
	{
		//cout<<b<<endl;	
		memset(acan,true,sizeof(acan));
		for (a=0;a<=2*M*M-(N-1)*b;a++)
		{
			if (!acan[a])	continue;
			int len;
			for (len=0;len<N;len++)
				if (!bsq[a+b*len])	break;				//failed
			if (len==N){												//ok
				fout<<a<<' '<<b<<endl;
				none=false;
		//		cout<<"ok"<<endl;
			}
			else	for (int i=0;i<len;i++)	acan[i*b+a]=false;
		}
	}
	if (none)	fout<<"NONE"<<endl;
    fout.close();fin.close();
    return 0;
}
