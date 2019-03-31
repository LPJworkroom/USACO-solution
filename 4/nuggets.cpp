/*ID: lpjwork1
TASK: nuggets
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
/*base equals turn*256*/
int base=0,N,ans;
/*bulast is bool of first half of CanMakeUp,back is second half*/ 
bool bulast[260],back[260];
queue<int> last;
/*pack is given numbers*/
vector<int> pack;
ofstream fout ("nuggets.out");
ifstream fin ("nuggets.in");
int main() {
	fin>>N;
	for (int i=0;i<260;i++)	bulast[i]=true;
	for (int i=0;i<N;i++)
	{
		int temp;fin>>temp;
		pack.push_back(temp);
	}
	sort(pack.begin(),pack.end());
	for (int i=pack.size()-1;i>=1;i--)
		for (int j=i-1;j>=0;j--)	
			if (pack[i]%pack[j]==0){
				pack.erase(pack.begin()+i);break;
			}
	int maxnum=pack[pack.size()-1],minnum=pack[0];
	bulast[0]=false;
	for (int i=0;i<pack.size();i++)
		for (int j=0;j<maxnum;j++)
			if (bulast[j]==false&&j+pack[i]<=maxnum)	bulast[j+pack[i]]=false;
	for (int i=1;i<maxnum;i++)	
		if (bulast[i]){
			last.push(i);
			ans=i;
		}
	int befsize=last.size();
	for (int i=0;i<260;i++)	back[i]=bulast[i];
	if (minnum!=1&&pack.size()!=1)
	while (1)
	{
		for (int k=0,m=last.size();k<m;k++)
		{
			int now=last.front();last.pop();
			for (int i=0;i<pack.size();i++)
			{
				if (now-pack[i]>0&&back[now-pack[i]]==false){
					back[now]=false;break;
				}
				if (now-pack[i]<=0&&bulast[now-pack[i]+maxnum]==false){
					back[now]=false;break;
				}
			}
			if (back[now]==true){
				ans=now;
				last.push(now);	
			}
		}
		if (last.size()==0)	break;
		if (last.size()==befsize){
			ans=base=0;break;
		}
		befsize=last.size();
		base+=maxnum;
		for (int i=0;i<260;i++)	bulast[i]=back[i];
	}
	else	ans=0;
    fout.close();fin.close();
    return 0;
}
