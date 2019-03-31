/*ID: lpjwork1
TASK: runround
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
#define ul unsigned long
using namespace std;
const int INF=(1<<31);
int nownum[20],temparray[20];
bool inuse[20],vis[10];
ul pow10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
ul M,N=0,ans=INF;
void addup(int);
void generatebase();
void dfs(int);
ul unique(ul);
bool notunique();
ofstream fout ("runround.out");
ifstream fin ("runround.in");
int main() {
	memset(nownum,0,sizeof(nownum));
	memset(inuse,false,sizeof(inuse));
	fin>>M;
	int tempm=M;
	while (tempm>0)
	{
		N++;tempm/=10;
	}
	reverse(temparray,temparray+N);
	dfs(0);
	/*you embrass me???*/
	if (ans==INF){
		N++;ans=INF;
		dfs(0);
	}				
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void dfs(int dep)
{
	if (dep==N){
		generatebase();return;
	}
	for (int i=0;i<N;i++)
	{
		if (inuse[i])	continue;
		nownum[dep]=i;
		inuse[i]=true;
		dfs(dep+1);
		inuse[i]=false;
	}
}

void addup(int dep)
{
	//cout<<dep<<endl;
	if (dep==N){
		if (notunique())	return;
		ul tempans=0;
		for (int i=0;i<N;i++)
		{
			tempans*=10;tempans+=temparray[i];
		}
		if (tempans<=M)	return;
		cout<<tempans<<endl;
		ans=min(ans,tempans);
		return;
	}
	for (int i=0;i<=(9-temparray[dep])/N;i++)
	{
		//cout<<i<<endl;
		temparray[dep]+=i*N;
		addup(dep+1);
		temparray[dep]-=i*N;
	}
}

void generatebase()
{
	/*from first digit to Nth*/
	for (int i=0;i<N;i++)
	{
		//find this digit's point,eg:2->3,N->1
		int tofind=(nownum[i]+1)%N,cnt=0;
		while (cnt<10&&nownum[(i+cnt)%N]!=tofind)	cnt++;
		if (cnt==10)	return;
		temparray[i]=cnt;
	}
	addup(0);
}

bool notunique()
{
	memset(vis,false,sizeof(vis));
	for (int i=0;i<N;i++)
		if (vis[temparray[i]])	return true;
		else					vis[temparray[i]]=true;
	return false;
}
