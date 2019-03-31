/*ID: lpjwork1
TASK: ride
LANG: C++11
*/
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
	string str1,str2;
	fin>>str1>>str2;
	//cout<<str1<<endl<<str2<<endl;
	int sum1=1,sum2=1;
	for (auto i:str1){
		sum1*=(i-'A'+1);sum1%=47;
	}
	for (auto i:str2){
		sum2*=(i-'A'+1);sum2%=47;
	}
	if (sum1==sum2)	fout<<"GO"<<endl;
	else			fout<<"STAY"<<endl;
	//cout<<sum1<<' '<<sum2<<endl;
	fout.close();
	fin.close();
    return 0;
}
