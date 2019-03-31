/*ID: lpjwork1
TASK: barn1
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
ofstream fout ("barn1.out");
ifstream fin ("barn1.in");
int main() {
	int M,S,C;fin>>M>>S>>C;
	int ans=0;
	int cow[C+1],gap[C];
	for (int i=1;i<=C;i++)	fin>>cow[i];
	sort(cow+1,cow+1+C);
	ans=cow[C]-cow[1]+1;
	for (int i=1;i<C;i++)	gap[i]=cow[i+1]-cow[i]-1;
	sort(gap+1,gap+C,greater<int>());
	for (int i=1;i<M;i++)	ans-=gap[i];
	if (ans<C)	ans=C;
	fout<<ans<<endl;
    fout.close();fin.close();
    return 0;
}
