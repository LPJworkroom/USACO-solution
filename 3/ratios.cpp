/*ID: lpjwork1
TASK: ratios
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
int target[3],food[3][3];
ofstream fout ("ratios.out");
ifstream fin ("ratios.in");
int main() {
	bool found=false;
	fin>>target[0]>>target[1]>>target[2];
	if (target[0]==0&&target[1]==0&&target[2]==0){
		fout<<"0 0 0 0"<<endl;
		found=true;
	}
	for (int i=0;i<3;i++)
		for (int j=0;j<3;j++)	fin>>food[i][j];
	int sum;
	for (sum=1;sum<300-2&&!found;sum++)
		for (int a=0;a<=sum&&a<100&&!found;a++)
			for (int b=0;a+b<=sum&&b<100&&!found;b++)
			{
				int c=sum-a-b;
				if (c>=100)	continue;
				int now[3];
				for (int i=0;i<3;i++)	now[i]=a*food[0][i]+b*food[1][i]+c*food[2][i];
				if ((target[0]==0||now[0]%target[0]==0)&&(target[1]==0||now[1]%target[1]==0)&&(target[2]==0||now[2]%target[2]==0)&&
					now[0]*target[1]==now[1]*target[0]&&now[1]*target[2]==now[2]*target[1]){
					int rate=target[0]!=0?now[0]/target[0]:target[1]!=0?now[1]/target[1]:target[2]!=0?now[2]/target[2]:0;
					fout<<a<<' '<<b<<' '<<c<<' '<<rate<<endl;
					found=true;
				}
			}
	if (!found)	fout<<"NONE"<<endl;
    fout.close();fin.close();
    return 0;
}
