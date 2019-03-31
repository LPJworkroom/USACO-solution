/*ID: lpjwork1
TASK: friday
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
ofstream fout ("friday.out");
ifstream fin ("friday.in");
int main() {
	int month[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};
	int count[7];	for (int i=0;i<7;i++)	count[i]=0;
	int now=13%7,N;fin>>N;
	for (int year=1900;year<1900+N;year++)
	{
		int leap=0;
		if (year%100==0){
			if (year%400==0)	leap=1;
		}
		else
		if (year%4==0)	leap=1;
		for (int i=0;i<12;i++)
		{
			count[now]++;
			now=(now+month[leap][i])%7;	
		}
	}
	fout<<count[6];
	for (int i=0;i<6;i++){
		fout<<' '<<count[i];
		//cout<<count[i]<<' ';
	}
	fout<<"\n";
    fout.close();fin.close();
    return 0;
}
