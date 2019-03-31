/*ID: lpjwork1
TASK: rockers
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
#define loop(i,x,y)	for(int i=x;i<y;i++)
/*dp[i][j]:ith song,jth disc*/
int data[20+1],dp[20+1][20+1],totake[20+1][20+1];
/*songs from i to 20*/
vector<vector<vector<int> > >songs(20,vector<vector<int> >(20));
int N,M,T;
ofstream fout ("rockers.out");
ifstream fin ("rockers.in");
int main() {
	fin>>N>>T>>M;
	loop(i,0,M+1)
		loop(j,0,N+1)	dp[i][j]=0;
	loop(i,0,N)	fin>>data[i];
	loop(i,0,N)
		loop(j,i,N)
		{
			songs[i][j]=vector<int>(data+i,data+j+1);
			sort(songs[i][j].begin(),songs[i][j].end());
			vector<int>& now=songs[i][j];
			int cnt=0,sum=0;
			while (cnt<now.size()&&sum<=T)	sum+=now[cnt++];
			if (!(cnt==now.size()&&sum<=T))	cnt--;
			totake[i][j]=cnt;
		}
	loop(i,0,M)
		loop(j,0,N)
			loop(k,j,N)
			{
			//	cout<<i<<' '<<j<<' '<<k<<' '<<cnt<<' '<<sum<<endl;
				dp[i+1][k+1]=max(dp[i+1][k+1],dp[i][j]+totake[j][k]);
			}
	/*
	loop(i,0,M+1)
	{
		loop(j,0,N+1)	cout<<dp[i][j]<<' ';
		cout<<endl;
	}
	*/	
	int ans=0;
	loop(i,0,N+1)	ans=max(ans,dp[M][i]);
	//fout<<ans<<endl;
	fout<<dp[M][N]<<endl;
    fout.close();fin.close();
    return 0;
}
