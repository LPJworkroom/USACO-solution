/*ID: lpjwork1
TASK: zerosum
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
#include<sstream>
using namespace std;
const int base='0';
const char Ope[]={' ','+','-'};
int N;
string formu;
void generate(int);
void calcu();
ofstream fout ("zerosum.out");
ifstream fin ("zerosum.in");
int main() {
	fin>>N;
	generate(1);
    fout.close();fin.close();
    return 0;
}

void generate(int now)
{
	if (now==N){
		formu+=(N+base);
		calcu();
		formu.pop_back();
		return;
	}
	formu+=(now+base);
	for (int i=0;i<3;i++)
	{
		formu+=Ope[i];
		//cout<<formu<<endl;
		generate(now+1);
		formu.pop_back();
	}
	formu.pop_back();
}

void calcu()
{
	int ans,curnum;
	char curope;
	string now;
	for (int i=0;i<2*N;i++)
		if (formu[i]!=' ')	now+=formu[i];
	//cout<<now<<endl;
	stringstream ss;
	ss<<now;
	ss>>ans;
	while (ss>>curope>>curnum)
	{
		if (curope=='+')	ans+=curnum;
		else				ans-=curnum;
	}
	if (ans==0)	fout<<formu<<endl;
}
