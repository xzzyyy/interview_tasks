#include <string>
#include "auto.h"
using namespace std;


Auto::Auto()
{
}

string Auto::turn_right()
{
	++_dir;
	if (_dir == _DIRS_STR.length())
		_dir = 0;
	return string(1, _DIRS_STR[_dir]);
}

string Auto::turn_left()
{
	--_dir;
	if (_dir == -1)
		_dir = _DIRS_STR.length() - 1;
	return string(1, _DIRS_STR[_dir]);
}

string Auto::should_beep()
{
	return state() + " beep";
}

string Auto::state() const
{
	return string(1, _DIRS_STR[_dir]);
}
