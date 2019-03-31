/*ID: lpjwork1
TASK: milk4
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
const int MAXN=100;
vector<int > pails,chosen;
int N,Q,depth;
bool found;
void dfs(int,int);
bool canmasure(int,int);
ofstream fout ("milk4.out");
ifstream fin ("milk4.in");
int main() {
	fin>>Q>>N;
	found=false;
	pails.resize(N+1);chosen.resize(N+1);
	for (int i=0;i<N;i++)	fin>>pails[i];
	sort(pails.begin(),pails.begin()+N);
	for (depth=1;depth<=N;depth++)
	{
		dfs(0,0);
		if (found)	break;
	}
	fout<<depth;
	sort(chosen.begin(),chosen.begin()+depth);
	for (int i=0;i<depth;i++)	fout<<' '<<chosen[i];	fout<<endl;
    fout.close();fin.close();
    return 0;
}

void dfs(int dep,int minind)
{
	if (found)	return;
	if (dep==depth){
		//for (int i=0;i<dep;i++)	cout<<chosen[i]<<' ';cout<<endl;
		//sort(chosen.begin(),chosen.end(),greater<int>());
		if (canmasure(0,Q)){
			found=true;
			cout<<"a tta ri!!"<<endl;
			for (int i=0;i<depth;i++)	cout<<chosen[i]<<' ';cout<<endl;
		}
		return;
	}
	for (int i=minind;i<N;i++)
	{
		if (found)	return;
		chosen[dep]=pails[i];
		//for (int j=0;j<=dep;j++)	cout<<chosen[j]<<' ';cout<<endl;
		dfs(dep+1,i+1);
		if (found)	return;
	}
}

bool canmasure(int dep,int num)
{
	if (dep==depth-1)
		if (num%chosen[dep]==0)	return true;
		else					return false;
		
	for (int i=1;i<=num/chosen[dep];i++)
		if (canmasure(dep+1,num-i*chosen[dep]))	return true;
	return false;
}
