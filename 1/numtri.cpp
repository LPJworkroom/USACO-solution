/*ID: lpjwork1
TASK: numtri
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
#include<fstream>
using namespace std;
const int MAXN=1000+10;
int read[MAXN],curmax[MAXN];
int N;
int main() {
ofstream fout ("numtri.out");
ifstream fin ("numtri.in");
	fin>>N;
	cout<<"ok"<<endl;
	memset(read,0,sizeof(read));
	memset(curmax,0,sizeof(curmax));
	cout<<"ok"<<endl;
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=i;j++)
		{
			fin>>read[j];
			read[j]+=max(curmax[j-1],curmax[j]);
		}
		for (int j=1;j<=i;j++)	curmax[j]=read[j];
		for (int j=1;j<=i;j++)	cout<<curmax[j]<<' ';cout<<endl;
	}
	int ans=0;
	for (int i=1;i<=N;i++)	ans=max(ans,curmax[i]);
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}
