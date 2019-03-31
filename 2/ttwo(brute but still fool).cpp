/*ID: lpjwork1
TASK: ttwo
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
const int step[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
char graph[12][12];
void move(int&,int&,int&);
bool state[10000][16];
ofstream fout ("ttwo.out");
ifstream fin ("ttwo.in");
int main() {
	int fi,fj,ci,cj,dirf=0,dirc=0;
	for (int i=0;i<10000;i++)	memset(state[i],false,sizeof(state[i]));
	for (int i=0;i<12;i++)	graph[0][i]=graph[11][i]=graph[i][0]=graph[i][11]='*';
	for (int i=1;i<=10;i++)
		for (int j=1;j<=10;j++)
		{
			fin>>graph[i][j];
			if (graph[i][j]=='F'){
				fi=i;fj=j;
			}
			if (graph[i][j]=='C'){
				ci=i;cj=j;
			}
		}
	state[(fi-1)+(fj-1)*10+(ci-1)*100+(cj-1)*1000][0]=true;
	int ans=0;
	while (1)
	{
		ans++;
		move(fi,fj,dirf);
		move(ci,cj,dirc);
		if (fi==ci&&fj==cj)	break;
		int pos=(fi-1)+(fj-1)*10+(ci-1)*100+(cj-1)*1000;
		int director=dirf+dirc*4;
		if (state[pos][director]==true){
			ans=0;break;
		}
		state[pos][director]=true;
	}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}

void move(int& x,int& y,int& dir)
{
	int newx=x+step[dir][0],newy=y+step[dir][1];
	if (graph[newx][newy]=='*')	dir=(dir+1)%4;
	else{
		x=newx;y=newy;
	}
}
