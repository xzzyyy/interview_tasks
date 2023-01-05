// Palindrome with special symbols
// Empty string is palindrome? (yes)

#include <iostream>
#include <cctype>
#include <vector>


bool isPalindrome(const std::string& s)
{
    if (s.length() <= 1)
        return true;
    
    size_t l = 0;
    size_t r = s.length() - 1;
    
    while (true)
    {
        while (r - l > 1 && ispunct(s[l]))
            ++l;
        if (ispunct(s[l]))
            return true;
            
        while (r - l > 1 && ispunct(s[r]))
            --r;
        if (ispunct(s[r]))
            return true;
            
        // std::cout << s[l] << "-" << s[r] << ";";
        if (tolower(s[l]) != tolower(s[r]))
            return false;
            
        // no place to move cursors further: .......!.!..
        if (r - l <= 2)
            return true;
            
        ++l;
        --r;
    }
}


int main()
{
    const std::vector<std::string> strs {
        "aaa",
        "aab",
        "-a-",
        "---",
        "",
        "--!",
        "-aga-",
        "--ab,.cc.ba",
        "--ab,.cd.ba"
    };
    
    std::cout << std::boolalpha;
    
    for (auto& s : strs)
        std::cout << s << "\t" << isPalindrome(s) << std::endl;
}
