/*ID: lpjwork1
TASK: shuttle
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<vector>
#include<fstream>
using namespace std;
const int MAXN=30;
enum color{nil,w,b};
color board[MAXN];
int len,ans=0,gap,N;
vector<int> op;
void shuttle(int);
void swap(int,int);
bool onboard(int);
bool final();
void show();
ofstream fout ("shuttle.out");
ifstream fin ("shuttle.in");
int main() {
	fin>>N;
	len=N*2+1;gap=N;
	board[N]=nil;
	for (int i=0;i<N;i++)
	{
		board[i]=w;board[i+N+1]=b;
	}
	shuttle(N);
    fout.close();fin.close();
    return 0;
}


void shuttle(int N)
{
	while (1)
	{
		//show();
		if (final())	break;
		ans++;
	/*check if can jump*/
		/*check w jump*/
		if (onboard(gap-2)&&board[gap-2]==w&&board[gap-1]==b){
			swap(gap,gap-2);continue;
		}
		/*check b jump*/
		if (onboard(gap+2)&&board[gap+2]==b&&board[gap+1]==w){
			swap(gap,gap+2);continue;
		}
	/*check if can make gap*/
		if (onboard(gap+2)&&onboard(gap-1)&&
			board[gap+2]==w&&board[gap-1]==w){
				swap(gap,gap-1);continue;
			}
			
		if (onboard(gap-2)&&onboard(gap+1)&&
			board[gap-2]==b&&board[gap+1]==b){
				swap(gap,gap+1);continue;
			}
	/*if nothing,move*/
		if (onboard(gap-1)&&board[gap-1]==w)	swap(gap,gap-1);
		else				swap(gap,gap+1);
	}
	for (int i=0;i<op.size();i++)
	{
		if ((i)%20==0){
			fout<<op[i];
		}
		else	fout<<' '<<op[i];
		if ((i+1)%20==0)	fout<<endl;
	}
	if ((op.size())%20!=0)	fout<<endl;
}

void swap(int g,int b)
{
	gap=b;op.push_back(b+1);
	board[g]=board[b];
	board[b]=nil;
}

bool onboard(int pos)
{
	return (pos>=0&&pos<len);
}

bool final()
{
	for (int i=0;i<N;i++)	if (board[i]!=b)	return false;
	for (int i=N+1;i<len;i++)	if (board[i]!=w)	return false;
	return true;
}

void show()
{
	for (int i=0;i<len;i++)
		if (board[i]==w)	cout<<'w';
		else if (board[i]==b)	cout<<'b';
		else if (board[i]==nil)	cout<<' ';
		else	cout<<'?';
	cout<<endl;
}
