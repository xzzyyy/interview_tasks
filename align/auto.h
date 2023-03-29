#ifndef AUTO_H
#define AUTO_H

#include <string_view>
#include <string>

struct Auto
{
    std::string turn_right()
    {
        ++_dir;
        if (_dir == static_cast<int>(_DIRS_STR.length()))
            _dir = 0;
        return std::string(1, _DIRS_STR[_dir]);
    }

    std::string turn_left()
    {
        --_dir;
        if (_dir == -1)
            _dir = _DIRS_STR.length() - 1;
        return std::string(1, _DIRS_STR[_dir]);
    }

    std::string should_beep()
    {
        return state() + " beep";
    }

    std::string state() const
    {
        return std::string(1, _DIRS_STR[_dir]);
    }

private:
    static constexpr std::string_view _DIRS_STR = "^>v<";
    int _dir = 0;
};

#endif
