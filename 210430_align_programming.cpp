/*
Write in C++ a text-based car simulator
	• Program shall run as a console application
	• Program shall print the car direction as a symbol:
		0 “^” for North (initial direction)
		0 “>” for East
		0 “v” for South
		0 “<” for West
	• User shall type command:
		0 “L” to turn car left by 90 degrees
		0 “R” to turn car right by 90 degrees
		0 “B” to beep (see below)
	• After receiving the command, program shall print on a new line:
		0 The updated car direction
		0 Text “beep” if the command was to beep
Example:
> ^
> L
> <
> L
> v
> B
> v beep
> R
> <
The requirements are straightforward, and the program shall first and foremost be complete and working as described. However, think about future development and support of this program. Try to demonstrate sound
design, modern style and good practices, as best as you can in the allowed time.
*/

//---auto.h---
#ifndef AUTO_H
#define AUTO_H

#include <string_view>
#include <string>

class Auto
{
	static constexpr std::string_view DIRS_STR = "^>v<";
	int _dir = 0;
	bool _beep = false;

public:
	Auto();
	void new_cycle();
	char turn_right();
	char turn_left();
	void should_beep();
	std::string get_state() const;
};

#endif
//---auto.h---


//---auto.cpp---
#include <string>
#include "auto.h"
using namespace std;


Auto::Auto()
{
}

void Auto::new_cycle()
{
	_beep = false;
}

char Auto::turn_right()
{
	++_dir;
	if (_dir == DIRS_STR.length())
		_dir = 0;
	return DIRS_STR[_dir];
}

char Auto::turn_left()
{
	--_dir;
	if (_dir == -1)
		_dir = DIRS_STR.length() - 1;
	return DIRS_STR[_dir];
}

void Auto::should_beep()
{
	_beep = true;
}

string Auto::get_state() const
{
	string res;
	res += DIRS_STR[_dir];
	if (_beep)
		res += " beep";
	return res;
}
//---auto.cpp---


//---align.cpp---
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
//---align.cpp---


//---unit_tests.cpp---
#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "../align/auto.h"

BOOST_AUTO_TEST_CASE(TestAuto)
{
	Auto a;

	BOOST_TEST(a.get_state() == "^");
	BOOST_TEST(a.turn_left() == '<');
	BOOST_TEST(a.turn_right() == '^');
	BOOST_TEST(a.turn_right() == '>');
	BOOST_TEST(a.turn_right() == 'v');
	BOOST_TEST(a.turn_right() == '<');
	BOOST_TEST(a.turn_left() == 'v');

	a.should_beep();
	BOOST_TEST(a.get_state() == "v beep");
	a.new_cycle();
	BOOST_TEST(a.get_state() == "v");
}
//---unit_tests.cpp---