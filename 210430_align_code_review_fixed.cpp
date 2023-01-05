#include <iostream>
using namespace std;

template<class T>
class Vector3D
{
    T* d_data;
 
public:
    Vector3D() : d_data(0)				    // no function body {}
                                            // shouldn't we specify nullptr_t instead of 0?
											// if we will have d_data initialized like that, all below functions will cause segfault
	{
	    d_data = new T[3];
	    memset(d_data, sizeof(d_data), 0);
	}										
 
    Vector3D(const T& v1, const T& v2, const T& v3)
    {
        d_data = new T[3];					// should be new S[3]
											// d_date should be d_data
											// shouldn't parameters be of type const T&?
        d_data[0] = v1;
        d_data[1] = v2;
        d_data[2] = v3;
    }
 
    Vector3D& operator=(const Vector3D& v)  // operator= should return 3DVector&
    {
        d_data[0] = v[0];
        d_data[1] = v[1];
        d_data[2] = v[2];
    }
 
    T& operator[](int i) { return d_data[i]; }
    const T& operator[](int i) const { return d_data[i]; }
											// should return T&
											// we should also add const T& operator[](int i) const
 
    Vector3D operator+=(const Vector3D& v)  // Did author mean operator+=? Should have 3DVector& as return type then
    {
        d_data[0] += v[0];
        d_data[1] += v[1];
        d_data[2] += v[2];
    }
   
    Vector3D& operator*=(T v)				// Did author mean operator*=? Should have 3DVector& as return type then
    {
        d_data[0] *= v;
        d_data[1] *= v;
        d_data[2] *= v;
    }
   
    T operator*(const Vector3D& v)
    {
        return d_data[0] * v[0] + d_data[1] * v[1] + d_data[2] * v[2];
    }
   
    Vector3D operator^(const Vector3D& v) const  
                                            // function should be const
    {
        Vector3D result;
        result[0] = d_data[1] * v[2] - d_data[2] * v[1];
        result[1] = d_data[0] * v[2] - d_data[2] * v[0];
        result[2] = d_data[0] * v[1] - d_data[1] * v[0];
        return result;			            // std::move is not needed, because return statement provides copy elision
    }

    ~Vector3D()							    // private destructor, should we really use it?
											// 3DVector<T>
    {
        delete d_data;						// we should use delete[] as d_data is array
    }
};

int main()
{
    Vector3D<int> int_vector(1, 2, 3);
    cout << (int_vector * int_vector) << endl;
}
