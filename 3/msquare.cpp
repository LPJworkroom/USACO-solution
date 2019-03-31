/*ID: lpjwork1
TASK: msquare
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
map<int,int> seen;
const int maxmove=25;
char path[maxmove];
int opecnt=0;
int pad[2][4]={{1,2,3,4},{8,7,6,5}},target[2][4];
bool found=false;
void doA();
void doB();
void doC();
void dfs(int);
bool check();
void copy(int [][4],int[][4]);
void show(int [][4]);
int gethash();
ofstream fout ("msquare.out");
ifstream fin ("msquare.in");
int main() {
	//doA();
	//doB();
	//doC();
	//show();
	for (int i=0;i<4;i++)	fin>>target[0][i];
	for (int i=3;i>=0;i--)	fin>>target[1][i];
	//show();
	for (int dep=0;dep<=maxmove&&!found;dep++){
		show(target);
		//cout<<seen.size()<<' ';
		seen.clear();
		//cout<<seen.size()<<endl;
		dfs(dep);
		cout<<seen[43128765]<<' ';
		cout<<seen.size()<<' ';
		cout<<dep<<endl;
	}
    fout.close();fin.close();
    return 0;
}

void dfs(int dep)
{
	int temphash=gethash();
	if (temphash==43128765)	cout<<dep<<' '<<"????"<<endl; 
	if (dep==0&&check()){
		cout<<"found!"<<endl;
		fout<<opecnt<<endl;
		for (int i=0;i<opecnt;i++)	fout<<path[i];	fout<<endl;
		found=true;return;
	}
	if (found||dep==0)	return;
	if (seen.find(temphash)!=seen.end()&&seen[temphash]>=dep)	return;
	else	seen[temphash]=dep;
	int backup[2][4];
	copy(backup,pad);
	path[opecnt++]='A';
	doA();dfs(dep-1);opecnt--;copy(pad,backup);
	path[opecnt++]='B';
	doB();dfs(dep-1);opecnt--;copy(pad,backup);
	path[opecnt++]='C';
	doC();dfs(dep-1);opecnt--;copy(pad,backup);
}

bool check()
{
	for (int i=0;i<2;i++)
		for (int j=0;j<4;j++)
			if (pad[i][j]!=target[i][j])	return false;
	return true;
}

void copy(int to[][4],int from[][4])
{
	for (int i=0;i<2;i++)
		for (int j=0;j<4;j++)
			to[i][j]=from[i][j];
}

void doA()
{
	for (int i=0;i<4;i++)
	{
		int temp=pad[0][i];pad[0][i]=pad[1][i];pad[1][i]=temp;
	}
}

void doB()
{
	int temp[2]={pad[0][3],pad[1][3]};
	for (int i=3;i>0;i--)
	{
		pad[0][i]=pad[0][i-1];
		pad[1][i]=pad[1][i-1];
	}
	pad[0][0]=temp[0];pad[1][0]=temp[1];
}

void doC()
{
	int temp=pad[1][1];
	pad[1][1]=pad[1][2];
	pad[1][2]=pad[0][2];
	pad[0][2]=pad[0][1];
	pad[0][1]=temp;
}

void show(int to[][4])
{
	for (int i=0;i<2;i++)
	{
		for (int j=0;j<4;j++)
			cout<<to[i][j]<<' ';
		cout<<endl;
	}
}

int gethash()
{
	int temp=0;
	for (int i=0;i<2;i++)
		for (int j=0;j<4;j++)
		{
			temp*=10;temp+=pad[i][j];
		}
	return temp;
}
