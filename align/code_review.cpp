// code review

template<class T>
class 3DVector							// identifier can't start with number
{
	T* d_data;							// it's better not to use pointers (we can use containers or smart pointers)
										// public interface first, private part after visible part

public:
	3DVector() : d_data(0)				// probably author meant deleted default constructor
										// (it will not be created already as-is as there user-defined constructors)
										// member initializer list, but no constructor body `{}`
										// `nullptr_t` instead of 0?

	template<class S>					// member function can't be templated
	3DVector(const S& v1, const S& v2, const S& v3)	// better variable names possible
	{									// (for ex. use x, y, z instead of v1, v2, v3)
		d_date = new S(3);				// typo in identifier
										// wrong array-new / array-delete syntax
		d_data[0] = v1;
		d_data[1] = v2;
		d_data[2] = v3;
	}
 
	void operator=(const 3DVector& v)	// wrong operator signature
	{
		d_data[0] = v[0];
		d_data[1] = v[1];
		d_data[2] = v[2];
	}
 
	T operator[](int i) { return d_data[i]; }	// wrong operator signature
										// missing `const` operator versions
 
	void operator+(const 3DVector& v)	// wrong operator signature
	{
		d_data[0] += v[0];
		d_data[1] += v[1];
		d_data[2] += v[2];
	}
   
	void operator*(T v)					// wrong operator signature
	{
		d_data[0] *= v;
		d_data[1] *= v;
		d_data[2] *= v;
	}
   
	T operator*(const 3DVector& v)		// member function can be `const`
	{
		return d_data[0] * v[0] + d_data[1] * v[1] + d_data[2] * v[2];
	}
   
	3DVector<T> operator^(const 3DVector& v)	// member function can be `const`
	{
		3DVector result;
		result[0] = d_data[1] * v[2] - d_data[2] * v[1];
		result[1] = d_data[0] * v[2] - d_data[2] * v[0];
		result[2] = d_data[0] * v[1] - d_data[1] * v[0];
		return std::move(result);		// copy elision (`move` in `return` statement redundant)
	}
 
private:
	~3DVector()							// destructor should be `public`
	{
		delete d_data;					// wrong array-new / array-delete syntax
	}
}
