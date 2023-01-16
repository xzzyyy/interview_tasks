// Дано множество 2Д точек. Найти вертикальную линию относительно которой точки расположены зеркально, если она есть.

//  ответ x = 6.           ответ x = 6            ответ - нету
//  oY                     oY                     oY
//  |*    |    *           |  *  |  *             |  *       *  
//  |  *  |  *             |  *  |  *             |    *       *
//  |     *                |     |                |       *
//  |     |                |     |                |        
//  +1-3--6--9-11---- oX   +--3--6--9------- oX   +--3-5--7------- oX

//  ответ нету             ответ x = 6            ответ нету
//  oY                     oY                     oY
//  |*         *           |     |                |     |
//  |        *             |  ***|***             |  ***|** *
//  |  *                   |     |                |     |
//  |                      |     |                |     |   
//  +1-3--6--9-11---- oX   +--3--6--9------- oX   +--3--6--9------- oX

#include <vector>
#include <numeric>
#include <limits>
#include <iostream>

struct Point 
{
    int x;
    int y;
};

float find_vertical_x(const std::vector<Point> &in) 
{
    size_t size = in.size();
    int x_sum = std::accumulate(cbegin(in), cend(in), 0, [](int sum, const Point &p){ return sum + p.x; });
    float middle = float(x_sum) / size;
    
    std::vector<Point> in_sorted(in);
    sort(begin(in_sorted), end(in_sorted), [middle](const Point &p1, const Point &p2)
    { 
        return (p1.y < p2.y) || (p1.y == p2.y && std::abs(p1.x - middle) < std::abs(p2.x - middle)); 
    });
    
    for (size_t i = 0; i < size - 1; )
    {
        if (in_sorted[i].x == middle)
        {
            ++i;
            continue;
        }
        
        if (in_sorted[i].y != in_sorted[i+1].y || std::abs(in_sorted[i].x - middle) != std::abs(in_sorted[i+1].x - middle))
            return std::numeric_limits<float>::infinity();
        i += 2;
    }

    return middle;
}

int main()
{
    std::cout << find_vertical_x({{1,4},{3,3},{6,2},{9,3},{11,4}}) << std::endl;
    std::cout << find_vertical_x({{3,3},{3,4},{9,3},{9,4}}) << std::endl;
    std::cout << find_vertical_x({{3,4},{5,3},{7,2},{9,4},{11,3}}) << std::endl;
    std::cout << find_vertical_x({{1,4},{3,2},{9,3},{11,4}}) << std::endl;
    std::cout << find_vertical_x({{3,3},{4,3},{5,3},{7,3},{8,3},{9,3}}) << std::endl;
    std::cout << find_vertical_x({{3,3},{4,3},{5,3},{7,3},{8,3},{10,3}}) << std::endl;
}