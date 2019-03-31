/*ID: lpjwork1
TASK: skidesign
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
using namespace std;
int cnt[101];
int N,ans=1<<30;
ofstream fout ("skidesign.out");
ifstream fin ("skidesign.in");
int main() {
	memset(cnt,0,sizeof(cnt));
	fin>>N;
	for (int i=1;i<=N;i++)
	{
		int temp;fin>>temp;
		cnt[temp]++;
	}
	int l=0,r=17;
	for (;r<=100;l++,r++)
	{
		int tempans=0;
		for (int i=0;i<l;i++)	tempans+=(l-i)*(l-i)*cnt[i];
		for (int i=r+1;i<=100;i++)	tempans+=(i-r)*(i-r)*cnt[i];
		ans=min(ans,tempans);
	}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}
