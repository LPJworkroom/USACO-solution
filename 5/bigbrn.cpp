/*ID: lpjwork1
TASK: bigbrn
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
const int MAXN=1000;
/*rolling array*/
int dp[MAXN+10][2];
int N,T;
vector<set<int> > trees;
ofstream fout ("bigbrn.out");
ifstream fin ("bigbrn.in");
int main() {
	fin>>N>>T;
	trees.resize(N+1);
	for (int i=0;i<T;i++)
	{
		int x,y;fin>>x>>y;
		trees[x].insert(y);
	}
	for (int i=1;i<=N;i++)	dp[i][0]=dp[i][1]=0;
	int ans=0;
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=N;j++)
		{
			if (trees[i].find(j)!=trees[i].end())	dp[j][1]=0;
			else	dp[j][1]=min(min(dp[j-1][1],dp[j][0]),dp[j-1][0])+1;
			ans=max(ans,dp[j][1]);
		}
		for (int j=1;j<=N;j++)	dp[j][0]=dp[j][1];
	}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}
