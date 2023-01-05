#include <iostream>
#include "auto.h"
using namespace std;


int main()
{
	Auto a;
	char command = '\0';

	while (command != 'q')
	{
		cout << a.get_state() << endl;
		a.new_cycle();

		cin >> command;
		switch (command)
		{
		case 'R':
			a.turn_right();
			break;
		case 'L':
			a.turn_left();
			break;
		case 'B':
			a.should_beep();
			break;
		case 'q':
			break;
		default:
			cout << "no such command, allowed commands: R, L, B, q\n";
		}
	}
}
