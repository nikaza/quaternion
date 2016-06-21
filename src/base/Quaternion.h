#ifndef QUATERNION_LIB
#define QUATERNION_LIB

#include <iostream>
#include <cmath>
#include <memory>
#include <map>
#include <vector>

using std::shared_ptr;
using std::vector;
using std::cout;
using std::endl;

namespace Quaternions{

// Define quaternion basis vector types
typedef enum{
	qw,
	qi,
	qj,
	qk
}AxisType;

// Forward-declare the class to define its shared pointer and operators
class Quaternion;
typedef shared_ptr<Quaternion> QuaternionPtr;

// - Addition
//   - Pointer versions
QuaternionPtr operator+(const QuaternionPtr q1, const QuaternionPtr q2);
QuaternionPtr operator-(const QuaternionPtr q1, const QuaternionPtr q2);

//   - Object versions
Quaternion &operator+(Quaternion &q1, Quaternion &q2);  // std::map[] can't be const
Quaternion operator-(Quaternion &q1, Quaternion &q2);


// Scalar multiplications
QuaternionPtr operator*(const double c, const QuaternionPtr q2);
QuaternionPtr operator*(const int c, const QuaternionPtr q2); // int will be casted to double

// - Quaternion multiplication
//   - Pointer version
QuaternionPtr operator*(const QuaternionPtr q1, const QuaternionPtr q2);
//   - Object version
Quaternion operator*(Quaternion &q1, Quaternion &q2);

class Quaternion
{
public :
	// Default constructor, initialize to zero
	Quaternion();
	
	// Constructor for all 4 parts
	Quaternion(double w, double i, double j, double k);
	
	// Destructor
	~Quaternion();
//
	// Copy constructor
	Quaternion(const Quaternion &q);

	// Copy Assignment operator
	void operator=(Quaternion &q);

	// Move assignment operator
	void operator=(Quaternion &&q);

	// Print quaternion
	void write(std::ostream &out);
	
	// Retrieval functions for individual elements
	auto getAxis(AxisType axis){return elements_[axis];}
	
	// Get element iterators
	auto elementsBegin(){return elements_.begin();}
	auto elementsEnd(){return elements_.end();}

	bool isEmpty();

	// Get individual values
	double &w(){return elements_[qw];}
	double &i(){return elements_[qi];}
	double &j(){return elements_[qj];}
	double &k(){return elements_[qk];}

	/* Return the norm |q| = sqrt(\sum a_i^2)*/
	double norm()const;
	
	// Overload operator to get and assign individual values
	double &operator[](AxisType axis){return elements_[axis];}

private:

	// Elements container. Use map for sparse storage and O(log(n)) lookup complexity
	std::map<AxisType,double> elements_;

};

//class Quaternion;
//typedef std::shared_ptr<Quaternion> QuaternionPtr;

}

#endif
