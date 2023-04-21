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

#ifndef _4_ALG_VERTICAL_LINE_HPP
#define _4_ALG_VERTICAL_LINE_HPP

#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>

struct VerticalLine
{
    struct Point 
    {
        int x;
        int y;
    };

    static double find_vertical_x(const std::vector<Point> &in)
    {
        size_t size = in.size();
        int x_sum = std::accumulate(in.cbegin(), in.cend(), 0, [](int sum, const Point &p){ return sum + p.x; });
        double middle = double(x_sum) / size;

        std::vector<Point> in_sorted(in);
        sort(in_sorted.begin(), in_sorted.end(), [middle](const Point &p1, const Point &p2)
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
            
            if (in_sorted[i].y != in_sorted[i + 1].y
                || std::abs(in_sorted[i].x - middle) != std::abs(in_sorted[i + 1].x - middle))
            {
                return std::numeric_limits<float>::infinity();
            }
            i += 2;
        }

        return middle;
    }
};

// TODO
// - float > doublt
// - cbegin > cont.cbegin()

#endif
