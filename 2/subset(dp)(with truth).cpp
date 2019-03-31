/*ID: lpjwork1
TASK: subset
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
#define ll long long 
using namespace std;
const int MAXN=39;
ll N,ans=0,sum=0;
ll dp[400];
//void showtable();
ofstream fout ("subset.out");
ifstream fin ("subset.in");
int main() {
	for (int i=0;i<400;i++)	dp[i]=0;
	dp[0]=1;
	fin>>N;
	int sum=(N+1)*N/2;
	if (N==1||(!(N&1)&&N%4)||(sum&1)){
		fout<<0<<endl;
		fout.close();fin.close();
		return 0;	
	}
	cout<<"ok"<<endl;
	
	for (int j=1;j<=N;j++)
		for (int i=sum/2-j;i>=0;i--)
			dp[i+j]+=dp[i];
		
	ans=dp[sum/2];
	cout<<ans/2<<endl;
	fout<<ans/2<<endl;
    fout.close();fin.close();
    return 0;
}

void showtable()
{
	for (int i=0;i<400;i++)
	{
		for (int j=0;j<=MAXN;j++)	printf("%d ",dp[j][i]);
		printf("\n");
	}
}*/
