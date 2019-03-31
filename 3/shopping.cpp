/*ID: lpjwork1
TASK: shopping
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
#define for_range(i,x,y)		for (int i=x;i<y;i++)
const int pow10[]={1,10,100,1000,10000,100000};
const int MAXSTATE=55555,MAXOFF=99,MAXN=5,INF=(1<<30);
map<int,int> codetoi;
int off,N=0,tot=0;
					/*default price and offers combined*/
int dp[MAXSTATE+10],offer[MAXOFF+MAXN+1][MAXN+1],price[MAXOFF+MAXN+1];
int state[MAXN],target[MAXN];
void init();
int genestate(int[]);
void degenestate(int[],int);
bool overflow(int[],int[]);
void show();
ofstream fout ("shopping.out");
ifstream fin ("shopping.in");
int main() {
	init();
	fin>>off;
	for (int i=0;i<off;i++)
	{
		int n,pri;fin>>n;
		for (int j=0;j<n;j++)
		{
			int code,num;
			fin>>code>>num;
			if (codetoi.find(code)==codetoi.end())	codetoi[code]=tot++;
			code=codetoi[code];
			offer[i][code]=num;
		}
		fin>>price[i];
	}
	fin>>N;
	int final=0;
	for (int i=0;i<N;i++)
	{
		int code,todo;fin>>code>>todo>>price[off];
		if (codetoi.find(code)==codetoi.end())	codetoi[code]=tot++;
		code=codetoi[code];
		target[code]=todo;
		offer[off][code]=1;
		final+=pow10[code]*todo;
		off++;
	}
	//cout<<final<<endl;
	//show();
	dp[0]=0;
	for (int ind=0;ind<final;ind++)
	{
		if (dp[ind]==INF)	continue;
		degenestate(state,ind);
		for (int i=0;i<off;i++)
		{
			if (overflow(state,offer[i]))	continue;
			int addup=genestate(offer[i]);
			dp[addup+ind]=min(dp[addup+ind],dp[ind]+price[i]);
		}
	}
	//for_range(i,0,final+1)	cout<<i<<' '<<dp[i]<<endl;
	fout<<dp[final]<<endl;
    fout.close();fin.close();
    return 0;
}

bool overflow(int a[],int b[])
{
	for (int i=0;i<MAXN;i++)
		if (a[i]+b[i]>target[i])	return true;
	return false;
}

int genestate(int from[])
{
	int ret=0;
	for (int i=0;i<MAXN;i++)	ret+=pow10[i]*from[i];
	return ret;
}

void degenestate(int to[ ],int ind)
{
	for (int i=0;ind;ind/=10,i++)	to[i]=ind%10;
}

void init()
{
	for (int i=0;i<MAXSTATE+10;i++)	dp[i]=INF;
	for_range(i,0,MAXOFF+MAXN+1)
		for_range(j,0,MAXN+1)	offer[i][j]=0;
	for_range(i,0,MAXOFF+MAXN+1)	price[i]=0;
}

void show()
{
	for_range(i,0,off)
	{
		for_range(j,0,MAXN+1)	cout<<offer[i][j]<<' ';cout<<"||";
		cout<<price[i]<<endl;
	}
}
