/*ID: lpjwork1
TASK: nocows
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
#define ll long long 
using namespace std;
const int MAXN=200,MAXK=100;
ll dp[MAXN][MAXK],sumof[MAXN][MAXK];
int N,H;
void initialize();
void show();
ofstream fout ("nocows.out");
ifstream fin ("nocows.in");
int main() {
	initialize();
	fin>>N>>H;
	dp[1][1]=1;
	sumof[1][1]=1;
	for (int i=1;i<=N;i+=2)
	{
		for (int j=1;j<=H;j++)
		{
			int k;
			for (k=1;k<(i-1);k+=2)
			{
			//	printf("i:%d j:%d k:%d dp[k][j-1]:%d sumof[i-k-1][j-1]:%d \n",
			//	i,j,k,dp[k][j-1],sumof[i-k-1][j-1]);
				dp[i][j]+=dp[k][j-1]*sumof[i-k-1][j-2]*2;
				dp[i][j]+=dp[k][j-1]*dp[i-k-1][j-1];
			}
			//if ((i-1)/2%2==1)	dp[i][j]-=dp[(i-1)/2][j-1];
			dp[i][j]%=9901;
			sumof[i][j]=sumof[i][j-1]+dp[i][j];
			sumof[i][j]%=9901;
			//printf("%d\n",dp[i][j]);
		}
	}
	//show();
	fout<<dp[N][H]%9901<<endl;
    fout.close();fin.close();
    return 0;
}

void initialize()
{
	for (int i=0;i<MAXN;i++)
		for (int j=0;j<MAXK;j++)	sumof[i][j]=dp[i][j]=0;
	//for (int i=0;i<MAXN;i++)	sumof[i]=0;
}

void show()
{
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=H;j++)
			printf("%d ",dp[i][j]);
		printf("\n");
	}
	printf("////////////////////\n");
	
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=H;j++)
			printf("%d ",sumof[i][j]);
		printf("\n");
	}	
	
}
