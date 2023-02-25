// Cтроятся дома на улице, солнце освещает горизонтально справа. У дома есть высота. Нужно сделать класс с двумя
// методами: добавить дом и получить список освещённых в данный момент домов.Домов может быть очень много и функция
// добавить дом будет вызываться очень часто.Система высоконагруженная, так что решение должно быть оптимальным.

#include <vector>

#define BOOST_TEST_MODULE yandex_houses
#include <boost/test/included/unit_test.hpp>

// complexity: O(n)
class LitHouses
{
public:
    void add_house(int height)
    {
        if (height > visibility_h)
        {
            houses.push_back(house_idx);
            visibility_h = height;
        }
        ++house_idx;
    }

    std::vector<int> lit_houses() const
    {
        return houses;
    }

private:
    int visibility_h = 0;
    int house_idx = 0;
    std::vector<int> houses;
};

BOOST_AUTO_TEST_CASE(test_lit_houses)
{
    const std::vector<int> tc1{ 1, 2, 3 }, tc1_exp{ 0, 1, 2 };
    const std::vector<int> tc2{ 3, 2, 2, 10 }, tc2_exp{ 0, 3 };

    {
        LitHouses lh;
        for (int h : tc1)
            lh.add_house(h);
        BOOST_TEST(tc1_exp == lh.lit_houses());
    }

    {
        LitHouses lh;
        for (int h : tc2)
            lh.add_house(h);
        BOOST_TEST(tc2_exp == lh.lit_houses());
    }
}
