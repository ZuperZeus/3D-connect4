#include <iostream>
#include <vector>
#include <tuple>
#include <termios.h>
using namespace std;
void printBoard(tuple<int,int,int> t, vector< vector< vector<int> > > v)
{
	string f="\e[96m#\e[0m";
	string s="\e[34m#\e[0m";
	string sel="\e[5m◯\e[0m";
	string p1="\e[91m";
	string p2="\e[93m";
	vector< vector<string> > strvec(40,vector<string>(25," "));
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			for(int k=0;k<4;k++)
				if(v[i][j][k]==1)
					if(t==make_tuple(i,j,k))
						strvec[i*10+1+j*2][k*4+(4-j)*2+1]=p1+sel;
					else
						strvec[i*10+1+j*2][k*4+(4-j)*2+1]=p1+"⬤\e[0m";
				else if(v[i][j][k]==2)
					if(t==make_tuple(i,j,k))
						strvec[i*10+1+j*2][k*4+(4-j)*2+1]=p2+sel;
					else
						strvec[i*10+1+j*2][k*4+(4-j)*2+1]=p2+"⬤\e[0m";
				else if(t==make_tuple(i,j,k))
					strvec[i*10+1+j*2][k*4+(4-j)*2+1]=sel;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<=8;j+=2)
			for(int k=j;k<17+j;k++)
				strvec[i*10+(8-j)][k]=f;
		for(int j=1;j<8;j+=2)
			for(int k=j;k<17+j;k+=4)
				strvec[i*10+(8-j)][k]=f;
	}
	for(int i=0;i<3;i++)
		strvec[i*10+9][8]=strvec[(i+1)*10][8]=s;
	for(int i=8;i<=38;i++)
		strvec[i][0]=strvec[i][16]=strvec[i-8][24]=s;
	for(int i=0;i<40;i++)
	{
		for(int j=0;j<25;j++)
		{
			cout<<strvec[i][j];
		}
		cout<<endl;
	}
}
int get_key()
{
	char x;
	x=cin.get();
	if(tp==make_tuple(-1,-1,-1))
		tp=make_tuple(0,0,0);
	else if(get<0>(tp)!=0&&x=='q')
		get<0>(tp)--;
	else if(get<0>(tp)!=3&&x=='e')
		get<0>(tp)++;
	else if(get<1>(tp)!=0&&x=='w')
		get<1>(tp)--;
	else if(get<1>(tp)!=3&&x=='s')
		get<1>(tp)++;
	else if(get<2>(tp)!=0&&x=='a')
		get<2>(tp)--;
	else if(get<2>(tp)!=3&&x=='d')
		get<2>(tp)++;
	else if(x=='\n')
	{
		vec[get<0>(tp)][get<1>(tp)][get<2>(tp)]=curr;
		curr=3-curr;
		tp=make_tuple(-1,-1,-1);
	}
	system("clear");
	printBoard(tp,vec);
}
int main()
{
	// Black magic to prevent Linux from buffering keystrokes.
	struct termios t;
	tcgetattr(0, &t);
	t.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &t);
	vector< vector< vector<int> > > vec(4,vector< vector<int> >(4,vector<int>(4,0)));
	tuple<int,int,int> tp=make_tuple(0,0,0);
	system("clear");
	printBoard(tp,vec);
}
