/*ID: lpjwork1
TASK: range
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
using namespace std;
#define for_range(i,x,y)	for(int i=x;i<y;i++)
const int MAXN=250;
int consecx[MAXN+1][MAXN+1],consecy[MAXN+1][MAXN+1],ans[MAXN+1];
int N,field[MAXN+1][MAXN+1];
ofstream fout ("range.out");
ifstream fin ("range.in");
int main() {
	fin>>N;fin.get();
	for_range(i,1,N+1)
	{
		char c;
		for_range(j,1,N+1){
			fin.get(c);
			field[i][j]=c-'0';
		}
		fin.get();
	}
	
	for_range(i,1,N+1)
	{
		for_range(j,1,N+1)	cout<<field[i][j]<<' ';
		cout<<endl;
	}
	
	for_range(i,1,N+1)
		for_range(j,1,N+1)
			if (field[i][j]==0)	consecx[i][j]=consecy[i][j]=0;
			else{
				consecx[i][j]=consecx[i-1][j]+1;
				consecy[i][j]=consecy[i][j-1]+1;
			}
	cout<<endl;
	for_range(i,1,N+1)
	{
		for_range(j,1,N+1)	cout<<consecx[i][j]<<' ';
		cout<<endl;
	}		
	
	cout<<endl;
	for_range(i,1,N+1)
	{
		for_range(j,1,N+1)	cout<<consecy[i][j]<<' ';
		cout<<endl;
	}		
			
	for_range(i,1,N+1)
		for_range(j,1,N+1)
		{
			int limit=min(consecx[i][j],consecy[i][j]);
			for (int k=1;k<limit;k++)
			{
				if (consecx[i][j-k]>=k+1&&consecy[i-k][j]>=k+1)	ans[k+1]++;
				else	break;
			}
		}
	for_range(i,2,N+1)
		if (ans[i]!=0){
			fout<<i<<' '<<ans[i]<<endl;
		}
    fout.close();fin.close();
    return 0;
}
