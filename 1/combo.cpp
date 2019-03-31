/*ID: lpjwork1
TASK: combo
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
int N;
int FJ[3][2],mas[3][2];
void swap(int& a,int& b);
void input(int fj[][2]);
int intersect(int pos);
ofstream fout ("combo.out");
ifstream fin ("combo.in");
int main() {
	fin>>N;
	if (N<=5){
		fout<<N*N*N<<endl;
		fout.close();fin.close();return 0;
	}
	input(FJ);input(mas);
	N=min(N,5);
	//count known ans
	int ans=2*N*N*N,todele=1;
	//delete intersection
	for (int i=0;i<3;i++)
		todele*=intersect(i);
	fout<<ans-todele<<endl;
    fout.close();fin.close();
    return 0;
}

void input(int fj[][2])
{
	for (int i=0;i<3;i++){
		fin>>fj[i][1];fj[i][1]+=2;
		if (fj[i][1]>=N-1)	fj[i][1]-=N;
		fj[i][0]=fj[i][1]-4;
	}
}

int intersect(int pos)
{
	int fj1=FJ[pos][0],fj2=FJ[pos][1],mas1=mas[pos][0],mas2=mas[pos][1];
	if (fj1>mas1){
		swap(fj1,mas1);swap(fj2,mas2);
	}
//	cout<<fj1<<' '<<fj2<<' '<<mas1<<' '<<mas2<<' '<<min(fj2,mas2)-mas1+1<<endl;
	if (fj2<mas1)	return 0;
	return min(fj2,mas2)-mas1+1;
}

void swap(int& a,int& b)
{
	int temp=a;a=b;b=temp;
}
