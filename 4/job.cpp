/*ID: lpjwork1
TASK: job
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
const int INF=(1<<30);
int J,N1,N2;
int cost[100],used[100];
vector<int> data;
bool canfill(int);
ofstream fout ("job.out");
ifstream fin ("job.in");
int main() {
	fin>>J>>N1>>N2;
	for (int i=1;i<=N1;i++)	fin>>cost[i];
	for (int i=0;i<J;i++)
	{
		int mid=INF,Ama;
		for (int i=1;i<=N1;i++)
			if (used[i]+cost[i]<mid){
				mid=used[i]+cost[i];Ama=i;
			}
		used[Ama]+=cost[Ama];data.push_back(used[Ama]);
	}
	sort(data.begin(),data.end(),greater<int>());
	
	for (int i=0;i<J;i++)	cout<<data[i]<<' ';cout<<endl;
	
	fout<<data[0]<<' ';
	/*now B cost*/
	for (int i=1;i<=N2;i++)	fin>>cost[i];
	sort(cost+1,cost+1+N2);
	
	for (int i=1;i<=N2;i++)	cout<<cost[i]<<' ';cout<<endl;
	
	int l=1,r=20000,mid;
	while (l<r-1)
	{
		mid=(l+r)/2;
		cout<<mid<<endl;
		if (canfill(mid))	r=mid;
		else				l=mid;
	}
	if (canfill(l))	fout<<l<<endl;
	else			fout<<r<<endl;
    fout.close();fin.close();
    return 0;
}

bool canfill(int limit)
{
	vector<int> vec=data;
	int cnt=0;
	for (int i=1;i<=N2;i++)
	{
		int time=limit;
		for (int j=0;j<J;j++)
		{
			if (vec[j]==-1)	continue;
			if (time-cost[i]<vec[j])	continue;
			time-=cost[i];
			vec[j]=-1;cnt++;
		}
	}
	//cout<<cnt<<endl;
	if (cnt!=J)	return false;
	return true;
}
