#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <tuple>
#include <signal.h>
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
		static void cursor(bool x); //0=hide, 1=unhide
};
#endif
