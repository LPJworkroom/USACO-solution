/*ID: lpjwork1
TASK: game1
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
const int MAXN=200;
int data[MAXN+1],dp[MAXN+1][MAXN+1],sumof[MAXN+1][MAXN+1];
int N;
ofstream fout ("game1.out");
ifstream fin ("game1.in");
int main() {
	fin>>N;
	for_range(i,1,N+1)	fin>>data[i];
	for_range(i,1,N+1)
		for_range(j,i,N+1)
		{
			sumof[i][j]=sumof[i][j-1]+data[j];
		}
	for_range(k,0,N+1)
		for_range(i,1,N+1-k+1)
		{
			int l=i,r=i+k;
			dp[l][r]=max(	data[l]+sumof[l+1][r]-dp[l+1][r],
							data[r]+sumof[l][r-1]-dp[l][r-1]);
		}
	fout<<dp[1][N]<<' '<<sumof[1][N]-dp[1][N]<<endl;
    fout.close();fin.close();
    return 0;
}
