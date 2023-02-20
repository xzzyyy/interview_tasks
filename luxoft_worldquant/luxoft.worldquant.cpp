#include <utility>      // std::move
#include <string>       // std::string
#include <stdexcept>    // std::invalid_argument

#define BOOST_TEST_MODULE luxoft_worldquant
#include <boost/test/included/unit_test.hpp>

// написать template функцию с двумя итераторами на входе и унарным оператором, которая ходит между итераторами и
// выполняет оператор для каждого элемента
template<typename ForwardIt, typename Func>
void iterate(ForwardIt first, ForwardIt last, Func f)
{
    auto it = first;
    while (it != last)
    {
        f(*it);
        ++it;
    }
}

// написать класс с move-конструктором
template<typename T> struct AcceptsMoveInit
{
    T val;

    // move-constructor is implicitly created
};

BOOST_AUTO_TEST_CASE(test_move_const_class)
{
    constexpr std::string_view STR = "Hello";
    
    AcceptsMoveInit<std::string> from = { std::string{ STR } };
    AcceptsMoveInit<std::string> to{ std::move(from) };

    BOOST_CHECK_EQUAL(STR, to.val);
    BOOST_TEST_MESSAGE("to avoid compiler removal of this code: " << to.val);
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
    BOOST_CHECK_THROW((Pair{ nullptr, nullptr }), std::invalid_argument);

    Pair empty;
    BOOST_CHECK_EQUAL(", ", empty.str());

    const char* str1 = "gopa";
    const char* str2 = "pizda";

    Pair orig{ str1, str2 };
    Pair copy_constr(orig);
    BOOST_CHECK(orig.str() == copy_constr.str());
    
    Pair copy_assignment = orig;
    BOOST_CHECK(orig.str() == copy_assignment.str());
    
    Pair move_into_c(std::move(copy_constr));
    BOOST_CHECK(orig.str() == move_into_c.str());
    
    Pair move_into_a(std::move(copy_assignment));
    BOOST_CHECK(orig.str() == move_into_a.str());
}
