#include <iostream>
#include <array>

template<typename T> class Vector3D
{
public:
    template<typename S> Vector3D(const S& x, const S& y, const S& z)
    {
        coords[0] = x;
        coords[1] = y;
        coords[2] = z;
    }
 
    Vector3D& operator=(const Vector3D& v)
    {
        coords[0] = v[0];
        coords[1] = v[1];
        coords[2] = v[2];
    }
 
    T& operator[](int i) { return coords[i]; }
    const T& operator[](int i) const { return coords[i]; }
 
    Vector3D& operator+=(const Vector3D& v)
    {
        coords[0] += v[0];
        coords[1] += v[1];
        coords[2] += v[2];
    }
   
    Vector3D& operator*=(const T& v)
    {
        coords[0] *= v;
        coords[1] *= v;
        coords[2] *= v;
    }
   
    T operator*(const Vector3D& v) const
    {
        return coords[0] * v[0] + coords[1] * v[1] + coords[2] * v[2];
    }
   
    Vector3D operator^(const Vector3D& v) const  
    {
        Vector3D result;
        result[0] = coords[1] * v[2] - coords[2] * v[1];
        result[1] = coords[0] * v[2] - coords[2] * v[0];
        result[2] = coords[0] * v[1] - coords[1] * v[0];
        return result;
    }

private:
    std::array<T, 3> coords;
};

int main()
{
    // Vector3D<int> i_err;     // error
    Vector3D<int> i_vec(1, 2, 3);
    Vector3D<double> d_vec(1.1, 2.2, 3.3);
    std::cout << (i_vec * i_vec) << std::endl;
    std::cout << (d_vec * d_vec) << std::endl;
}
