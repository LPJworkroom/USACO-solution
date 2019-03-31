/*ID: lpjwork1
TASK: buylow
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
const int MAXN=5000,INF=(1<<30);
const int base=100000,digit=5,MAXSIZE=25;
struct bignum{
	/*sign:0 + 1 -*/
	int size=0,sign=0;
	int* data;
	bignum()
	{
		data=new int[MAXSIZE];
		size=sign=0;
		for (int i=0;i<MAXSIZE;i++)	data[i]=0;
	}
	
	~bignum()
	{
		delete []data;
	}
	
	bignum(int vec[],int s)
	{
		data=new int[MAXSIZE];
		sign=0;
		int i;
		for (i=0;i<s;i++)	data[i]=vec[i];
		for (;i<MAXSIZE;i++)	data[i]=0;
		size=s;
	}
	
	void operator=(int num)
	{
		delete []data;
		data=new int[MAXSIZE];
		int numv[10];
		int cnt=0;
		while (num)
		{
			numv[cnt++]=num%base;
			num/=base;
		}
		bignum bnum(numv,cnt);
		size=bnum.size;sign=bnum.sign;
		for (int i=0;i<size;i++)	data[i]=bnum.data[i];
	}
	
	void operator=(bignum& mod)
	{
		delete []data;
		data=new int[MAXSIZE];
		size=mod.size;sign=mod.sign;
		for (int i=0;i<size;i++)	data[i]=mod.data[i];
	}
};

void sub(bignum&,bignum&,bignum&);
void add(bignum&,bignum&,bignum&);
void add(bignum&,int,bignum&);
void abs_add(bignum&,bignum&,bignum&);
void abs_sub(bignum&,bignum&,bignum&);
int compare(bignum&,bignum&);
int abs_compare(bignum&,bignum&);
void clear(bignum&);
bool operator>(bignum& a,bignum& b);
bool operator<(bignum& a,bignum& b);
bool operator==(bignum& a,bignum& b);
ostream& operator<<(ostream& f,bignum& b);


int dp[MAXN+1],data[MAXN+1];
bignum waycnt[MAXN+1];
int N;
ofstream fout ("buylow.out");
ifstream fin ("buylow.in");
int main() {
	fin>>N;
	//bignum a,b,c;a=0;b=5;add(a,b,c);cout<<c<<endl;
	for (int i=1;i<=N;i++)	fin>>data[i];
	for (int i=1;i<=N;i++)	waycnt[i]=dp[i]=1;
	
	/*new bignum var cost a lot!must be outside the loop*/
	bignum b;
	for (int i=1;i<=N;i++)
		for (int j=1;j<i;j++)
		{
			if (data[j]>data[i]){
				
			/*if b is here,runtime mults 6 times!*/
				if (dp[j]+1==dp[i]){
					add(waycnt[j],waycnt[i],b);
					waycnt[i]=b;
				}
				
				else if (dp[j]+1>dp[i]){
					dp[i]=dp[j]+1;waycnt[i]=waycnt[j];
				}
				
			}
			else if (data[j]==data[i]){
				waycnt[i]=0;
			}
		}
	//for (int i=0;i<=N;i++)	cout<<dp[i]<<' ';cout<<endl;
	//for (int i=0;i<=N;i++)	cout<<waycnt[i]<<' ';cout<<endl;
	int ans=0;
	bignum cnt,temp;cnt=0;temp=0;
	for (int i=1;i<=N;i++)	ans=max(ans,dp[i]);
	for (int i=1;i<=N;i++)
		if (dp[i]==ans){
			add(cnt,waycnt[i],temp);
			cnt=temp;
		}
	fout<<ans<<' '<<cnt<<endl;
	cout<<cnt<<endl;
    fout.close();fin.close();
    return 0;
}

ostream& operator<<(ostream& f,bignum& b)
{
	if (b.size==0){
		f<<0;return f;
	}
	if (b.sign)	f<<'-';
	f<<b.data[b.size-1];
	for (int i=b.size-2;i>=0;i--){
		int cnt=0;
		for (int j=b.data[i];j>0;j/=10,cnt++);
		for (;cnt<digit;cnt++)	f<<'0';
		f<<b.data[i];
	}
	return f;
}

bool operator>(bignum& a,bignum& b)
{
	if (compare(a,b)>0)	return true;
	return false;
}

bool operator<(bignum& a,bignum& b)
{
	if (compare(a,b)<0)	return true;
	return false;
}

bool operator==(bignum& a,bignum& b)
{
	if (compare(a,b)==0)	return true;
	return false;
}


void sub(bignum& a,bignum& b,bignum& c)
{
	b.sign=1-b.sign;
	add(a,b,c);
	b.sign=1-b.sign;
}

void abs_sub(bignum& a,bignum& b,bignum& c)
{
	clear(c);
	int borrow=0,msize=max(a.size,b.size);
	for (int i=0;i<msize;i++)
	{
		c.data[i]=a.data[i]-(i<=b.size-1?b.data[i]:0)-borrow;
		if (c.data[i]<0){
			c.data[i]+=base;
			borrow=1;
		}
		else borrow=0;
		if (c.data[i]>0)	c.size=i+1;
	}
	if (borrow==1){
		cout<<"wrong! abs(b) is bigger!A:"<<a<<"  B:"<<b<<" C:"<<c<<endl;
	}
}

void abs_add(bignum& a,bignum& b,bignum& c)
{
	clear(c);
	int carry=0,msize=max(a.size,b.size);
	for (int i=0;i<msize;i++)
	{
		c.data[i]=(i<a.size?a.data[i]:0)+(i<b.size?b.data[i]:0)+carry;
		carry=c.data[i]/base;
		c.data[i]%=base;
	}
	if (carry!=0){
		c.size=msize+1;
		c.data[c.size-1]=carry;
	}
	else c.size=msize;
}

void add(bignum& a,int b,bignum& c)
{
	int sign=b<0?1:0;
	if (b<0)	b=-b;
	int vec[40],cnt=0;
	for (;b;cnt++)
	{
		vec[cnt]=b%base;b/=base;
	}
	bignum B(vec,cnt);
	B.sign=sign;
	add(a,B,c);
}

void add(bignum& a,bignum& b,bignum& c)
{
	clear(c);
	//cout<<a<<' '<<b<<' ';
	if (a.sign==b.sign){
	//	cout<<"1 ";
		abs_add(a,b,c);
		c.sign=a.sign;
	}
	else if (abs_compare(a,b)>0){
	//	cout<<"2 ";
		abs_sub(a,b,c);
		c.sign=a.sign;
	}
	else{
	//	cout<<"3 ";
		abs_sub(b,a,c);
		c.sign=b.sign;
	}
}

int abs_compare(bignum& a,bignum& b)
{
	if (a.size!=b.size){
		if (a.size>b.size)	return 1;
		else	return -1;
	}
	for (int i=a.size-1;i>=0;i--)
		if (a.data[i]==b.data[i])	continue;
		else if (a.data[i]>b.data[i])	return 1;
				else	return -1;
	return 0;
}

int compare(bignum& a,bignum& b)
{
	if (a.size==b.sign&&a.size==0)	return 0;
	if (a.sign==1&&b.sign==0)	return -1;
	if (b.sign==1&&a.sign==0)	return 1;
	if (a.size!=b.size){
		if ((a.size>b.size&&a.sign==0)||(a.size<b.size&&a.sign==1))	return 1;
		else	return -1;
	}
	for (int i=a.size-1;i>=0;i--)
		if (a.data[i]==b.data[i])	continue;
		else{
			if ((a.data[i]>b.data[i]&&a.sign==0)||(a.data[i]<b.data[i]&&a.sign==1))	return 1;
			else	return -1;
		}
	return 0;
}

void clear(bignum& c)
{
	for (int i=0;i<c.size;i++)	c.data[i]=0;
	c.sign=c.size=0;
}
