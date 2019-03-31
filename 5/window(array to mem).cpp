/*ID: lpjwork1
TASK: window
LANG: C++11
*/
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<string.h>
#include<vector>
#include<queue>
#include<iomanip>
#include<algorithm>
#include<set>
#include<fstream>
using namespace std;
const int MAXN=124+10;

/*bool array to color*/
bool inhold[MAXN][MAXN];

struct rect{
	double x1,x2,y1,y2;
};

struct win{
	rect data;
	char id;
};

bool operator==(rect a,rect b)
{
	return a.x1==b.x1&&a.x2==b.x2&&
		   a.y1==b.y1&&a.y2==b.y2;
}

/*structure to save all window*/ 
vector<win> stack;
/*save coordinate,x and y coordinate*/
vector<double> xvec,yvec;

double area(rect&);
double area(win&);
double caculate(int);
int findbyid(char todo);
void swp(double&,double&);
void disolve(win& todo,bool color);

ofstream fout ("window.out");
ifstream fin ("window.in");
int main() {
	bool flag=true;
	while (flag)
	{
		char comm='\0';
		fin>>comm;fin.get();
		switch (comm)
		{
			/*create window*/
			case 'w':
			{	
				win temp;fin>>temp.id;fin.get();
				fin>>temp.data.x1;fin.get();
				fin>>temp.data.y1;fin.get();
				fin>>temp.data.x2;fin.get();
				fin>>temp.data.y2;fin.get();
				if (temp.data.x2<temp.data.x1)	swp(temp.data.x2,temp.data.x1);
				if (temp.data.y2<temp.data.y1)	swp(temp.data.y2,temp.data.y1);
				stack.push_back(temp);
				break;
			}
			/*bring to top*/
			case 't':
			{
				char todo;fin>>todo;fin.get();
				int temp=findbyid(todo);
				win twin=stack[temp];
				stack.erase(stack.begin()+temp);
				stack.push_back(twin);
				break;
			}
			/*put to bottom*/
			case 'b':
			{
				char todo;fin>>todo;fin.get();
				int temp=findbyid(todo);
				win twin=stack[temp];
				stack.erase(stack.begin()+temp);
				stack.insert(stack.begin(),twin);
				break;
			}
			/*destroy*/
			case 'd':
			{
				char todo;fin>>todo;fin.get();
				int temp=findbyid(todo);
				stack.erase(stack.begin()+temp);
				break;
			}
			/*show visble*/
			case 's':
			{
				char todo;fin>>todo;fin.get();
				int temp=findbyid(todo);
				caculate(temp);
				break;
			}
			/*over*/
			default:flag=false;break;
		}
	}
    fout.close();fin.close();
    return 0;
}

double area(rect& todo)
{
	return (todo.y2-todo.y1)*(todo.x2-todo.x1);
}

double area(win& todo)
{
	return area(todo.data);
}

int findbyid(char todo)
{
	int ret=0;
	while (stack[ret].id!=todo)	ret++;
	return ret;
}

double caculate(int todo)
{
	double raw_area=area(stack[todo]);
	
	xvec.clear();yvec.clear();	
	for (int i=0;i<=stack.size()*2;i++)
		for (int j=0;j<=stack.size()*2;j++)	inhold[i][j]=false;
	/*first,get all x,y in stack and discretization*/
	for (int i=stack.size()-1;i>=todo;i--)
	{
		rect& now=stack[i].data;
		double x1=now.x1,x2=now.x2,y1=now.y1,y2=now.y2;
		xvec.push_back(x1);xvec.push_back(x2);
		yvec.push_back(y1);yvec.push_back(y2);
	}
	sort(xvec.begin(),xvec.end());
	sort(yvec.begin(),yvec.end());
	xvec.resize(unique(xvec.begin(),xvec.end())-xvec.begin());
	yvec.resize(unique(yvec.begin(),yvec.end())-yvec.begin());
	
	disolve(stack[todo],true);
	/*disolve windows above and check overlap*/
	for (int i=stack.size()-1;i>todo;i--)
		disolve(stack[i],false);
	/*sum area*/
	double new_area=0;
	for (int i=0;i<=stack.size()*2;i++)
		for (int j=0;j<=stack.size()*2;j++)
			if (inhold[i][j]){
				rect temp=rect{xvec[i],xvec[i+1],yvec[j],yvec[j+1]};
				new_area+=area(temp);
			}
		
	fout<<setprecision(3)<<fixed<<new_area*100/raw_area<<endl;
}

void disolve(win& todo,bool color)
{
	int x1=todo.data.x1,x2=todo.data.x2,y1=todo.data.y1,y2=todo.data.y2;
	/*binary search,for index of high and low boundary of x and y*/
	int xl=lower_bound(xvec.begin(),xvec.end(),todo.data.x1)-xvec.begin(),
	xu=lower_bound(xvec.begin(),xvec.end(),todo.data.x2)-xvec.begin(),
	yu=lower_bound(yvec.begin(),yvec.end(),todo.data.y2)-yvec.begin(),
	yl=lower_bound(yvec.begin(),yvec.end(),todo.data.y1)-yvec.begin();
	for (int i=xl;i!=xu;i++)
		for (int j=yl;j!=yu;j++)
			inhold[i][j]=color;
}

void swp(double& a,double& b)
{
	double t=a;a=b;b=t;
}
