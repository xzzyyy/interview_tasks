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
