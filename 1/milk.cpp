/*ID: lpjwork1
TASK: milk
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
struct farmer{
	int per,amon;
};
farmer fa[6000];
bool operator<(farmer a,farmer b)
{
	return a.per<b.per;
}
ofstream fout ("milk.out");
ifstream fin ("milk.in");
int main() {
	int N,M,ans=0;fin>>N>>M;
	for (int i=1;i<=M;i++)
		fin>>fa[i].per>>fa[i].amon;
	sort(fa+1,fa+1+M);
	for (int i=1;N>0;i++)
	{
		int cur=min(N,fa[i].amon);
		N-=cur;
		ans+=cur*fa[i].per;
	}
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}
