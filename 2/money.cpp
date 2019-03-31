/*ID: lpjwork1
TASK: money
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
const int MAXN=10000,MAXV=25;
int N,V;
ll coins[MAXV+1],dp[MAXN+10];
ofstream fout ("money.out");
ifstream fin ("money.in");
int main() {
	memset(dp,0,sizeof(dp));
	fin>>V>>N;
	for (int i=1;i<=V;i++)	fin>>coins[i];
	dp[0]=1;
	/*
	for (int i=0;i<N;i++)
	{
		if (dp[i]){
			for (int j=1;j<=V;j++)
				if (i+coins[j]<=N)	dp[i+coins[j]]+=dp[i];
		}
	}*/
	for (int i=1;i<=V;i++)
		for (int j=0;j<=N;j++)
		{
			if (j+coins[i]<=N)	dp[j+coins[i]]+=dp[j];
		}
//	for (int i=0;i<=N;i++)
//		cout<<dp[i]<<' ';cout<<endl;
	fout<<dp[N]<<endl;
    fout.close();fin.close();
    return 0;
}
