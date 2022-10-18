#include <iostream>
#include <signal.h>
#include "Board.h"
using namespace std;
void ctrl_c(int signum)
{
	Board::buffer(-1);
	Board::cursor(true);
	exit(0);
}
int main()
{
	signal(SIGINT,ctrl_c);
	Board::buffer(1);
	Board::cursor(false);
	Board b;
	while(true)
	{
		b.printBoard();
		b.move();
	}
}
