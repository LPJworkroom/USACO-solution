/*ID: lpjwork1
TASK: hamming
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
int bef[100];
int tot=0,digi,D,N;
bool canadd(int);
int hamdist(int,int);
ofstream fout ("hamming.out");
ifstream fin ("hamming.in");
int main() {
	fin>>N>>digi>>D;
	for (int i=0;i<(1<<digi);i++)
		if (canadd(i)){
			bef[++tot]=i;
			if (tot==N)	break;
		}
	for (int i=1;i<=10&&tot>0;i++,tot--)
	{
		fout<<bef[N-tot+1];
		if (i==10||tot==1){
			fout<<endl;i=0;	
		}
		else	fout<<' ';
	}
    fout.close();fin.close();
    return 0;
}

bool canadd(int todo)
{
	for (int i=1;i<=tot;i++)
		if (hamdist(todo,bef[i])<D)	return false;
	return true;
}

int hamdist(int a,int b)
{
	int cnt=0;
	for (int i=(a^b);i;i&=(i-1))	cnt++;
	return cnt;
}
