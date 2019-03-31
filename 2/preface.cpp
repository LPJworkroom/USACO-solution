/*ID: lpjwork1
TASK: preface
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
const int MAXN=3500;
const char basicchar[8]={' ','I','V','X','L','C','D','M'};
const char numbers[][5]={"I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M"};
const int charset[]={1,4,5,9,10,40,50,90,100,400,500,900,1000};	// 13 nums
const int addup[13][2]={{1,0},{1,2},{2,0},{1,3},{3,0},{3,4},{4,0},{3,5},{5,0},{5,6},{6,0},{5,7},{7,0}};
// I V X L C D M
// I IV V IX X XL //VL// L XC C CD //LD// D CM M
int cnt[8],known[MAXN+10][8];
bool vis[MAXN];
ofstream fout ("preface.out");
ifstream fin ("preface.in");
int main() {
	int N;
	memset(cnt,0,sizeof(cnt));
	memset(vis,false,sizeof(vis));
	for (int i=0;i<MAXN+10;i++)	memset(known[i],0,sizeof(known[i]));
	fin>>N;
	for (int n=1;n<=N;n++)
	{
		int curn=n;
		cout<<n<<' ';
		while (curn)
		{
			/*if (vis[curn]){
				for (int i=1;i<=7;i++)
				{
					cnt[i]+=known[curn][i];
					known[n][i]+=known[curn][i];
				}
				break;
			}*/
			int nowind=upper_bound(charset,charset+13,curn)-charset-1;
			//cout<<curn<<' '<<nowind<<endl;
			for (int i=0;i<2;i++)
			{
				known[n][addup[nowind][i]]++;
				cnt[addup[nowind][i]]++;
			}
//			cout<<numbers[nowind]<<' ';
			curn-=charset[nowind];
		}
//		cout<<endl;
		vis[n]=true;
	}
	for (int i=1;i<=7;i++)
		if (cnt[i])	fout<<basicchar[i]<<' '<<cnt[i]<<endl;
    fout.close();fin.close();
    return 0;
}
