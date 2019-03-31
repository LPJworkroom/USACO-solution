/*ID: lpjwork1
TASK: cowtour
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
#include<iomanip>
#include<cmath>
using namespace std;
const int MAXN=150;
const double INF=(1<<30);
int N;
double dist[MAXN+10][MAXN+10],maxdist[MAXN+10],coord[MAXN+10][2],diameter[MAXN+10];
double ans=INF;
int vis[MAXN+10];
void findmaxdist();
void show();
void bfs();
ofstream fout ("cowtour.out");
ifstream fin ("cowtour.in");
int main() {
	fin>>N;
	for (int i=1;i<=N;i++)	fin>>coord[i][0]>>coord[i][1];
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=N;j++)
		{
			char a;fin>>a;//cout<<a<<' ';
			if (a=='0')	dist[i][j]=dist[j][i]=INF;
			else{
				double xx=coord[i][0]-coord[j][0],yy=coord[i][1]-coord[j][1];
				//if (xx*xx+yy*yy<0)	cout<<"wrong!"<<endl;
				dist[i][j]=dist[j][i]=sqrt(xx*xx+yy*yy);
			}
		}
	//	cout<<endl;
	}
	//show();
		for (int k=1;k<=N;k++)
			for (int i=1;i<=N;i++)
			for (int j=1;j<=N;j++)
				dist[i][j]=dist[j][i]=min(dist[i][j],dist[i][k]+dist[k][j]);
	for (int i=1;i<=N;i++)	dist[i][i]=0;
//	show();
	findmaxdist();
	bfs();
	
	//for (int i=1;i<=N;i++)	cout<<maxdist[i]<<' ';cout<<endl;
	
	for (int i=1;i<=N;i++)
		for (int j=1;j<=N;j++)
		{
			if (i==j||fabs(dist[i][j]-INF)>0.00001)	continue;
			double xx=coord[i][0]-coord[j][0],yy=coord[i][1]-coord[j][1];
			double temp=sqrt(xx*xx+yy*yy);
			/*
			if (ans>maxdist[i]+maxdist[j]+temp){
				cout<<i<<' '<<coord[i][0]<<' '<<coord[i][1]<<' '<<j<<' '<<coord[j][0]<<' '<<coord[j][1]<<' ';
				printf("%llf,%llf,%llf----%llf\n",maxdist[i],maxdist[j],temp,maxdist[i]+maxdist[j]+temp);
			}
			*/
			double tempdia=max(diameter[i],max(diameter[j],maxdist[i]+maxdist[j]+temp));
			ans=min(ans,tempdia);
		}
	//show();
	//for (int i=1;i<=N;i++)	printf("%.6llf  ",maxdist[i]);printf("\n");
	//for (int i=1;i<=N;i++)	printf("%.6llf  ",diameter[i]);printf("\n");
	fout<<fixed<<setprecision(6)<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void findmaxdist()
{
	for (int i=1;i<=N;i++)
	{
		//int maxid=0;
		double tempmax=0;
		for (int j=1;j<=N;j++)
		{
			if (fabs(dist[i][j]-INF)<0.00001)	continue;
			//if (dist[i][j]>tempmax)	maxid=j;
			tempmax=max(dist[i][j],tempmax);
		}
		maxdist[i]=tempmax;
		/*
		cout<<"maxdist:"<<i<<' '<<maxid<<' ';
		printf("%.6llf\n",tempmax);
		*/
	}
}


void show()
{
	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=N;j++)
			if (dist[i][j]==INF)	printf("-");
			else					printf("%.6llf ",dist[i][j]);
		printf("\n");
	}
}

void bfs()
{
	bool vis[N+10];
	memset(vis,false,sizeof(vis));
	for (int i=1;i<=N;i++)
	{
		if (!vis[i]){
			vector<int> g;
			queue<int> q;q.push(i);
			vis[i]=true;
			double tempdia=0;
			while (!q.empty())
			{
				int now=q.front();q.pop();
				g.push_back(now);
				tempdia=max(tempdia,maxdist[now]);
	//			printf("%d  ",now);
				for (int k=1;k<=N;k++)
				{
					if (!vis[k]&&dist[now][k]!=INF){
						vis[k]=true;
						q.push(k);
					}
				}
			}
			for (int i=0;i<g.size();i++)
				diameter[g[i]]=tempdia;
	//		printf("  over!!\n");
		}
	}
}
