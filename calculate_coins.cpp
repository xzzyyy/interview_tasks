/**
* Задание от компании Форсайт (январь 2020), которое дал рекрутер как пример задач, которые они спрашивают.
*
* Пример: если change == 27, то результат должен быть map со следующими парами:
*   std::pair<int, int>(10: 2),
*   std::pair<int, int>(5: 1),
*   std::pair<int, int>(2: 2),
*   std::pair<int, int>(1: 0)
*/

#include <map>
#include <vector>
#include <iostream>


std::map<int, int> calculate_coins(int change) {
    // Напишите свое решение.
    
    static const std::vector<int> COINS = { 10, 5, 2, 1 };
    std::map<int, int> coins;
    int money = change;
    
    size_t i = 0;
    while (money > 0 && i < COINS.size())
    {
        int coins_num = change / COINS[i];
        change = change % COINS[i];
        
        if (coins_num > 0)
        {
            coins[COINS[i]] = coins_num;
        }
        
        ++i;
    }
    
    if (change > 0)
    {
        throw std::runtime_error("Impossible to give a change");
    }
    
    return coins;
}

int main()
{
    auto coins = calculate_coins(27);
    
    for (auto &coin : coins)
    {
        std::cout << coin.first << ' ' << coin.second << std::endl;
    }
}
