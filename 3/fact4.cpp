/*ID: lpjwork1
TASK: fact4
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
int N;
ofstream fout ("fact4.out");
ifstream fin ("fact4.in");
int main() {
	fin>>N;
	int T=1;
	for (int i=1;i<=N;i++){
		T*=i;
		//cout<<i<<' ';
		while (T%10==0)	T/=10;
		if(T*(i+1)%10!=0)	T%=10;
		//cout<<T<<endl;
	}
	while (T%10==0)	T/=10;
	fout<<T%10<<endl;
    fout.close();fin.close();
    return 0;
}
