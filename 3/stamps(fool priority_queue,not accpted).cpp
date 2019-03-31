/*ID: lpjwork1
TASK: stamps
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
const int MAXN=50;
map<int,int> cnt;
int K,N;
int stamp[MAXN+10];
ofstream fout ("stamps.out");
ifstream fin ("stamps.in");
int main() {
	fin>>K>>N;
	for (int i=1;i<=N;i++)	
	{
		fin>>stamp[i];
		cnt[stamp[i]]=1;
		pq.push(stamp[i]);
	}
	int M=1;
	while ((*cnt.begin()).first==M)
	{
		if (cnt[M]>K){
			M--;break;
		}
		for (int i=1;i<=N;i++)
		{
			if (cnt[M+stamp[i]]==0)	cnt[M+stamp[i]]=cnt[M]+1;
			else					cnt[M+stamp[i]]=min(cnt[M+stamp[i]],cnt[M]+1);
		}
		cnt.erase(M);
		M++;
	}
	fout<<M<<endl;
    fout.close();fin.close();
    return 0;
}
