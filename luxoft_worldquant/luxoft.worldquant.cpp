#include <string>
#include <vector>
#include <utility>      // std::move
#include <stdexcept>

#define BOOST_TEST_MODULE luxoft_worldquant
#include <boost/test/included/unit_test.hpp>

// написать template функцию с двумя итераторами на входе и унарным оператором, которая ходит между итераторами и
// выполняет оператор для каждого элемента
template<typename ForwardIt, typename Func> void process(ForwardIt first, ForwardIt last, Func f)
{
    auto it = first;
    while (it != last)
    {
        f(*it);
        ++it;
    }
}

BOOST_AUTO_TEST_CASE(test_template_func)
{
    std::vector<int> arr{ 9, 9, 4, 2, 1, 9, 9, 9, 7, 7 };
    const std::vector<int> expected{ 9 * 9, 9 * 9, 4 * 4, 2 * 2, 1 * 1, 9 * 9, 9 * 9, 9 * 9, 7 * 7, 7 * 7 };

    process(arr.begin(), arr.end(), [](int& val) { val *= val; });
    BOOST_TEST(expected == arr);
}

// написать класс с move-конструктором
// rem.: Did they mean implicit move-constructor is not solution and I should write it by hand?
struct MoveConstrImplicit
{
    std::string val;

    MoveConstrImplicit()
        : val(10000, 'x')
    {
        
    }

    // move-constructor is implicitly created
};

struct MoveConstr
{
    std::string val;

    MoveConstr()
        : val(10000, 'x')
    {
        
    }

    MoveConstr(MoveConstr&& from) noexcept
        : val(std::move(from.val))
    {

    }
};

template<typename T> void get_addresses(uint64_t& from_addr, uint64_t& to_addr)
{
    T from;
    from_addr = reinterpret_cast<uint64_t>(from.val.c_str());
    
    T to{ std::move(from) };
    to_addr = reinterpret_cast<uint64_t>(to.val.c_str());
}

BOOST_AUTO_TEST_CASE(test_move_constr)
{
    uint64_t from_addr = 0;
    uint64_t to_addr = 0;
    
    get_addresses<MoveConstrImplicit>(from_addr, to_addr);
    BOOST_TEST(from_addr == to_addr);

    get_addresses<MoveConstr>(from_addr, to_addr);
    BOOST_TEST(from_addr == to_addr);
}

// задание на рефакторинг. 
// - дан класс. интерфейс менять нельзя. всё остальное можно и нужно поменять. в продакшене должно работать без проблем
// - добавить конструктор копирования и оператор присваивания

/*
class Pair {
public:
    Pair(const char *b, const char *q) {
        b_ = new char[strlen(b)];
        strcpy(b_, b);
        
        q_ = new char[strlen(q)];
        strcpy(q_, q);
    }
private:
    char * b_;	// base
    char * q_;	// quoted
};

int main() {
    
    return 0;
}
*/

class Pair
{
public:
    Pair() = default;
    Pair(const char* b, const char* q) {
        if (!b || !q)
            throw std::invalid_argument("null parameter in `Pair` constructor");
        
        b_ = std::string(b);
        q_ = std::string(q);
    }
    std::string str() const { return b_ + ", " + q_; }

private:
    std::string b_;     // base
    std::string q_;     // quoted
};

BOOST_AUTO_TEST_CASE(test_Pair)
{
    BOOST_REQUIRE_THROW((Pair{ nullptr, nullptr }), std::invalid_argument);

    Pair empty;
    BOOST_TEST(", " == empty.str());

    const char* str1 = "gopa";
    const char* str2 = "pizda";

    Pair orig{ str1, str2 };
    Pair copy_constr(orig);
    BOOST_TEST(orig.str() == copy_constr.str());
    
    Pair copy_assignment = orig;
    BOOST_TEST(orig.str() == copy_assignment.str());
    
    Pair move_into_c(std::move(copy_constr));
    BOOST_TEST(orig.str() == move_into_c.str());
    
    Pair move_into_a(std::move(copy_assignment));
    BOOST_TEST(orig.str() == move_into_a.str());
}
