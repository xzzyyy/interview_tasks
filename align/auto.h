#ifndef AUTO_H
#define AUTO_H

#include <string_view>
#include <string>

struct Auto
{
    Auto();
    std::string turn_right();
    std::string turn_left();
    std::string should_beep();
    std::string state() const;

private:
    static constexpr std::string_view _DIRS_STR = "^>v<";
    int _dir = 0;
};

#endif
