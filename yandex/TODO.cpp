// ""
// "a"
// "aga"
// "agb"
// ",,,"
// ",,."
// ",a,"
// ",,,aaa"
// ".,aa.b,a.a"

// Palindrome

bool isalphanum(char c);
char tolower(char c);

bool IsPalindrome(const std::string& str) {
    size_t len = str.length();
    
    if (len == 0)
        return true;
    
    size_t l = 0;
    size_t r = len - 1;
    
    do
    {
        while (l < r && !isalphanum(str[l]))
            ++l;
        while (l < r && !isalphanum(str[r]))
            --r;
        if (l == r)
            return true;
        
        if (tolower(str[l]) != tolower(str[r]))
            return false;
            
        if (r - l <= 2)
            break;
          
        ++l;
        --r;
    }
    while (true);
    
    return true;
}

// Equiilibrium Point

// { }
// { 0 }
// { 1 1 1 }

int GetEquilibriumPoint(const std::vector<int>& numbers) {
    size_t size = numbers.size();
    
    if (size == 0)
        return -1;
    if (size == 1)
        return 0;
    
    std::vector<int> sums{ size };
    
    sums[0] = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i)
    {
        sums[i] = sums[i - 1] + numbers[i];
    }
    
    r_sum = numbers[numbers.size() - 1];
    if (r_sum == sums[size - 1])
        return static_cast<int>(size - 1);
        
    for (size_t i = numbers.size() - 2; ; --i)
    {
        r_sum += numbers[i];
        if (r_sum == sum[i])
            return static_cast<int>(i);
            
        if (i == 0)
            return -1;
    }
    
    throw;
}