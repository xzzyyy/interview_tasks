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
