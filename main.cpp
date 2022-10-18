#include <iostream>
#include <vector>
#include <tuple>
#include <signal.h>
#include <termios.h>
using namespace std;
class Board
{
	private:
		vector< vector< vector<int> > > v;
		tuple<int,int,int> t;
		int curr;
	public:
		Board();
		void printBoard();
		void move();
		static void buffer(int x); //0=clear, 1=create, -1=delete
};
Board::Board()
{
	struct termios term;
	tcgetattr(0, &term);
	term.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &term);

	v=vector< vector< vector<int> > >(4,vector< vector<int> >(4,vector<int>(4,0)));
	t=make_tuple(-1,-1,-1);
	curr=1;
	buffer(1);
}
static void Board::buffer(int x)
{
	if(x==1)	cout<<"\e[?1049h";
	else if(x==0)	cout<<"\e[;H\e[2J";
	else if(x==-1)	cout<<"\e[?1049l";
}
void Board::printBoard()
{
	buffer(0);
	string f="\e[96m#\e[0m",s="\e[34m#\e[0m",sel="\e[5m◯\e[0m",p1="\e[91m",p2="\e[93m";
	vector< vector<string> > strvec(40,vector<string>(25," "));
	for(int i=0;i<4;i++) for(int j=0;j<4;j++) for(int k=0;k<4;k++)
		if(v[i][j][k]==1)
			if(t==make_tuple(i,j,k)) strvec[i*10+1+j*2][k*4+(4-j)*2+1]=p1+sel;
			else strvec[i*10+1+j*2][k*4+(4-j)*2+1]=p1+"⬤\e[0m";
		else if(v[i][j][k]==2)
			if(t==make_tuple(i,j,k)) strvec[i*10+1+j*2][k*4+(4-j)*2+1]=p2+sel;
			else strvec[i*10+1+j*2][k*4+(4-j)*2+1]=p2+"⬤\e[0m";
		else if(t==make_tuple(i,j,k)) strvec[i*10+1+j*2][k*4+(4-j)*2+1]=sel;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<=8;j+=2) for(int k=j;k<17+j;k++) strvec[i*10+(8-j)][k]=f;
		for(int j=1;j<8;j+=2) for(int k=j;k<17+j;k+=4) strvec[i*10+(8-j)][k]=f;
	}
	for(int i=0;i<3;i++) strvec[i*10+9][8]=strvec[(i+1)*10][8]=s;
	for(int i=8;i<=38;i++) strvec[i][0]=strvec[i][16]=strvec[i-8][24]=s;
	for(int i=0;i<40;i++)
	{
		for(int j=0;j<25;j++)
		{
			cout<<strvec[i][j];
		}
		cout<<endl;
	}
}
void Board::move()
{
	char x;
	x=cin.get();
	if(t==make_tuple(-1,-1,-1))	t=make_tuple(0,0,0);
	else if(get<0>(t)!=0&&x=='q')	get<0>(t)--;
	else if(get<0>(t)!=3&&x=='e')	get<0>(t)++;
	else if(get<1>(t)!=0&&x=='w')	get<1>(t)--;
	else if(get<1>(t)!=3&&x=='s')	get<1>(t)++;
	else if(get<2>(t)!=0&&x=='a')	get<2>(t)--;
	else if(get<2>(t)!=3&&x=='d')	get<2>(t)++;
	else if(x=='\n')
	{
		v[get<0>(t)][get<1>(t)][get<2>(t)]=curr;
		curr=3-curr;
		t=make_tuple(-1,-1,-1);
	}
	printBoard();
}
void ctrl_c(int signum)
{
	Board::buffer(-1);
}
int main()
{
	signal(SIGINT,ctrl_c);
	Board b;
	while(true)
	{
		b.move();
	}
}
