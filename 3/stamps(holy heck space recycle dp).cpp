/*ID: lpjwork1
TASK: stamps
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
const int MAXN=50,INF=(1<<30);
int K,N,M;
bool noex=true;
int stamp[MAXN+10],dp[20000+10];
ofstream fout ("stamps.out");
ifstream fin ("stamps.in");
int main() {
	for (int i=0;i<=20000;i++)	dp[i]=INF;
	fin>>K>>N;
	for (int i=1;i<=N;i++)
	{
		fin>>stamp[i];
		dp[stamp[i]]=1;
	}
	sort(stamp+1,stamp+N+1);
	int base=0;
	while (noex)
	{
		for (int i=1;i<=10000;i++)
			if (dp[i]>K){
				fout<<i+base-1<<endl;
				noex=false;
				break;
			}
			else	for (int k=1;k<=N;k++)	dp[i+stamp[k]]=min(dp[i+stamp[k]],dp[i]+1);
		for (int i=10001;i<=20000;i++)
		{
			dp[i-10000]=dp[i];
			dp[i]=INF;
		}
		base+=10000;
	}
    fout.close();fin.close();
    return 0;
}
