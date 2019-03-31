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
ll dp[MAXN+1][400];
ll combination(ll,ll);
//void lookfor(int,int);
void showtable();
ofstream fout ("subset.out");
ifstream fin ("subset.in");
int main() {
	//int a,b;cin>>a>>b;cout<<combination(a,b)<<endl;
	for (int i=0;i<400;i++)
	{
		for (int j=0;j<=MAXN;j++)	dp[j][i]=0;
	}
	
	//for (int i=0;i<=MAXN;i++)	dp[i][0]=1;
	dp[0][0]=1;
	fin>>N;
	int sum=(N+1)*N/2;
	if (N==1||(!(N&1)&&N%4)||(sum&1)){
		fout<<0<<endl;
		fout.close();fin.close();
		return 0;	
	}
	/*if (!(N&1)){
		fout<<combination(N/4,N/2)/2<<endl;
		fout.close();fin.close();
		return 0;	
	}*/
	cout<<"ok"<<endl;
	for (int i=0;i<sum/2;i++)
		for (int j=0;j<=N;j++)
		{
			if (dp[j][i]!=0){
				for (int k=j+1;k<=N&&k+i<=sum/2;k++)
				{
			//		cout<<i+k<<' '<<k<<' '<<dp[i][j]<<endl;
			 		dp[k][k+i]+=dp[j][i];
				//	dp[j][j+i]+=dp[j][i];
				}
			}
		}
	for (int i=1;i<=N;i++)	ans+=dp[i][sum/2];
	cout<<ans/2<<endl;
	fout<<ans/2<<endl;
    fout.close();fin.close();
    return 0;
}

ll combination(ll a,ll b)
{
	ll ans=1;
	for (ll i=b;i>b-a;i--)	ans*=i;
	for (ll i=a;i>1;i--)	ans/=i;
	return ans; 
}

void showtable()
{
	for (int i=0;i<400;i++)
	{
		for (int j=0;j<=MAXN;j++)	printf("%d ",dp[j][i]);
		printf("\n");
	}
}
