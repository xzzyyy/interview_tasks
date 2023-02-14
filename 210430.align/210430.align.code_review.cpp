// code review

template<class T>
class 3DVector								// identifier can't start with number
{
    T* d_data;
 
public:
    3DVector() : d_data(0)					// no function body {}
											// shouldn't we specify nullptr_t instead of 0?
											// if we will have d_data initialized like that, all below functions will cause segfault
 
    template<class S>
    3DVector(const S& v1, const S& v2, const S& v3)
    {
        d_date = new S(3);					// should be new S[3]
											// d_date should be d_data
											// shouldn't parameters be of type const T&?
        d_data[0] = v1;
        d_data[1] = v2;
        d_data[2] = v3;
    }
 
    void operator=(const 3DVector& v)		// operator= should return Vector3D&
    {
        d_data[0] = v[0];
        d_data[1] = v[1];
        d_data[2] = v[2];
    }
 
    T operator[](int i) { return d_data[i]; }
											// should return T&
											// we should also add const T& operator[](int i) const
 
    void operator+(const 3DVector& v)		// Did author mean operator+=? Should have Vector3D& as return type then
    {
        d_data[0] += v[0];
        d_data[1] += v[1];
        d_data[2] += v[2];
    }
   
    void operator*(T v)						// Did author mean operator*=? Should have Vector3D& as return type then
    {
        d_data[0] *= v;
        d_data[1] *= v;
        d_data[2] *= v;
    }
   
    T operator*(const 3DVector& v)			// function should be const
    {
        return d_data[0] * v[0] + d_data[1] * v[1] + d_data[2] * v[2];
    }
   
    3DVector<T> operator^(const 3DVector& v)
											// function should be const
    {
        3DVector result;					
        result[0] = d_data[1] * v[2] - d_data[2] * v[1];
        result[1] = d_data[0] * v[2] - d_data[2] * v[0];
        result[2] = d_data[0] * v[1] - d_data[1] * v[0];
        return std::move(result);			// std::move is not needed, because return statement provides copy elision
    }
 
private:
    ~3DVector()								// private destructor, should we really use it?
    {
      delete d_data;						// we should use delete[] as d_data is array
    }
}
