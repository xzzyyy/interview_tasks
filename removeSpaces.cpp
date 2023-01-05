// This is potential task
// Vasily was given it for BMW interview

#include <iostream>
#include <string>
#include <vector>
 
void remove_spaces(std::string &s)
{
    size_t seq_space = 0;
    size_t shift = 0;
   
    for (size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == '_')
            ++seq_space;
        
		// we should check if we are at last letter to correctly process strings like this: "___"
		if (s[i] != '_' || i == s.length() - 1)
            if (seq_space)
            {
                shift += seq_space - 1;
                seq_space = 0;
            }

        s[i - shift] = s[i];
    }

    s.resize(s.length() - shift);
}

int main()
{
    std::vector<std::string> v{ "abc__def_xx___1", "___" };

	for (std::string& s : v)
	{
		std::cout << s << std::endl;
		remove_spaces(s);
		std::cout << s << std::endl << std::endl;
	}
}
 