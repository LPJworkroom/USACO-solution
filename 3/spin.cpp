/*ID: lpjwork1
TASK: spin
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
bool wheel[5][360];
int speed[5],nowde[5]={0};
void color(int,int,int);
ofstream fout ("spin.out");
ifstream fin ("spin.in");
int main() {
	for (int i=0;i<5;i++)	for (int j=0;j<360;j++)	wheel[i][j]=false;
	for (int i=0;i<5;i++)
	{
		nowde[i]=0;
		fin>>speed[i];
		int n;fin>>n;
		for (int j=0;j<n;j++)
		{
			int l,r;fin>>l>>r;r+=l;
			color(l,r,i);
		}
	}
	int ans=0;
	bool ok=false;
	for (;ans<=360&&!ok;ans++)
	{
		for (int i=0;i<360;i++)
		{
			ok=true;
			for (int j=0;j<5;j++){
				ok&=wheel[j][(360+nowde[j]-i)%360];
			}	
			if (ok){
				cout<<i<<endl;
				fout<<ans<<endl;
				break;
			}
		}
		if (ok)	break;
		for (int i=0;i<5;i++)	nowde[i]=(360+nowde[i]-speed[i])%360;
	}
	if (ans==361)	fout<<"none"<<endl;
    fout.close();fin.close();
    return 0;
}

void color(int l,int r,int ind)
{
	l%=360;r%=360;
	if (r<l){
		for (int i=0;i<=r;i++)	wheel[ind][i]=true;
		for (int i=l;i<=359;i++)	wheel[ind][i]=true;
	}
	else{
		for (int i=l;i<=r;i++)	wheel[ind][i]=true;
	}
}
