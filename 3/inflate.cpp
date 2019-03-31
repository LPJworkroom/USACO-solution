/*ID: lpjwork1
TASK: inflate
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
const int MAXM=100000,MAXN=10000;
struct Prob{
	int time,val;
};
bool operator<(Prob& a,Prob& b){
if (a.time!=b.time)	return a.time<b.time;
else				return a.val>b.val;
}
int M,N,datasize=0,probsize=0;
Prob data[MAXN+1],prob[MAXN+1];	/*prob is uniqued data*/
int dp[MAXM+1];
void input();
ofstream fout ("inflate.out");
ifstream fin ("inflate.in");
int main() {
	fin>>M>>N;
	for (int i=0;i<=M;i++)	dp[i]=0;
	input();
	for (int i=0;i<M;i++)
		for (int j=0;j<probsize;j++)
			dp[i+prob[j].time]=max(dp[i]+prob[j].val,dp[i+prob[j].time]);
	fout<<dp[M]<<endl;
    fout.close();fin.close();
    return 0;
}

void input()
{
	for (int i=0;i<N;i++)
		fin>>data[i].val>>data[i].time;
	sort(data,data+N);
	prob[0]=data[0];
	probsize++;
	for (int i=1;i<N;i++)
	{
		if (data[i].val<=prob[probsize-1].val)	continue;
		prob[probsize++]=data[i];
	}
}
