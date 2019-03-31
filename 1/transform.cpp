/*ID: lpjwork1
TASK: transform
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
ofstream fout ("transform.out");
ifstream fin ("transform.in");
int N;
void rotate(vector<vector<char> >&);
void reflect(vector<vector<char> >&);
bool equal(vector<vector<char> >& A,vector<vector<char> >& B);
//void show(vector<vector<char> >& A);
int main() {
	fin>>N;
	vector<vector<char> > bef(N,vector<char>(N)),aft=bef;
	for (int i=0;i<N;i++)
		for (int j=0;j<N;j++)	fin>>bef[i][j];
	for (int i=0;i<N;i++)
		for (int j=0;j<N;j++)	fin>>aft[i][j];
	int ans=1,sign=0;
	//show(bef);show(aft);
	while (1)
	{
		for (;ans<4;ans++)
		{
			rotate(bef);
			if (equal(bef,aft)){
				sign=1;break;
			}
		}
		if (sign)	break;
		rotate(bef);
		reflect(bef);			//4
		if (bef==aft)	break;
		ans++;					//5
		for (int i=1;i<4;i++)
		{
			rotate(bef);
			if (bef==aft){
				sign=1;break;
			}
		}
		if (sign)	break;
		rotate(bef);
		ans++;					//6
		if (bef==aft)	break;
		ans++;	break;
	}
	fout<<ans<<endl;
	fout.close();fin.close();
    return 0;
}

void rotate(vector<vector<char> >& A)
{
	vector<vector<char> > B(N,vector<char>(N));
	for (int i=0;i<N;i++)
		for (int j=0;j<N;j++)
			B[i][j]=A[N-j-1][i];
	for (int i=0;i<N;i++)
		for (int j=0;j<N;j++)
			A[i][j]=B[i][j];
}

/*void show(vector<vector<char> >& A)
{
	for (int i=0;i<N;i++)
	{
		for (int j=0;j<N;j++)
			cout<<A[i][j]<<' ';
		cout<<endl;
	}
}*/

void reflect(vector<vector<char> >& A)
{
	for (int i=0;i<N;i++)
		reverse(A[i].begin(),A[i].end());
}

bool equal(vector<vector<char> >& A,vector<vector<char> >& B)
{
	for (int i=0;i<N;i++)
		for (int j=0;j<N;j++)
			if (A[i][j]!=B[i][j])	return false;
	return true;
}
