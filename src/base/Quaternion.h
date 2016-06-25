/* File Quaternion.h
 * 
 * Copyright (c) Nikos Kazazakis 2016
 * \brief Define Quaternion class for quaternion arithmetic in C++14
 * \author Nikos Kazazakis
 */

#ifndef QUATERNION_LIB // Define macro headers so that this file is only included once
#define QUATERNION_LIB

// Include STL headers
#include <iostream>
#include <cmath>
#include <map>

// Define some commonly used std functions for convenience
/* Note how we don't simply use "using namespace std;"
 * This is bad practice because we implicitly load all the std library
 * names, causing unnecessary potential naming conflicts.
 * Even worse, if someone includes a library using namespace std,
 * it will include all the std names without the user realising.
 * Ideally, all "using" statements should be placed on the .cpp files
 */
using std::cout;
using std::endl;

/* Define our project's namespace. This is important in order to
 * avoid naming conflicts between our functions/members and library
 * functions.
 */
namespace Quaternions{

// Define quaternion basis vector types
/* Note: although these are integers, ALWAYS use the enum types to
 * refer to them e.g.:
 * getAxisValue(2) will return the value along the j axis just like
 * getAxisValue(qj). However, if in the future someone adds another
 * type in this list (e.g. UndefinedValue), it can potentially break
 * your code if you are not using the enum type.
 */
typedef enum{
	qw,
	qi,
	qj,
	qk
}AxisType;

// Forward-declare the class to define operators
class Quaternion;

// === Object versions ===
// - Addition and subtraction
Quaternion operator+(const Quaternion &q1, const Quaternion &q2);  // std::map[] can't be const, however map.at is!
Quaternion operator-(const Quaternion &q1, const Quaternion &q2);

Quaternion operator+(const double c, const Quaternion &q2);
Quaternion operator+(const Quaternion &q2,const double c);

Quaternion operator-(const double c, const Quaternion &q2);
Quaternion operator-(const Quaternion &q2, const double c);

// - Multiplication
//   == Scalar multiplications
/* Note that we forego passing the quaternions as const so that we
 * can take advantage of r-value semantics
 */
Quaternion operator*(const double c, Quaternion &q2);
Quaternion operator*(const int c, Quaternion &q2);
Quaternion operator*(Quaternion &q2, const double c);
Quaternion operator*(Quaternion &q2, const int c);

//   == Quaternion-quaternion multiplication
/* We use the formula for the Hamilton product:
 * https://en.wikipedia.org/wiki/Quaternion#Hamilton_product */
/* Note: Using const here is important! It allows us to chain
 *       multiplications, i.e., q1*q2*q3*q4. This is only possible
 *       if the 2nd argument is a CONST reference. For instance,
 *       q3*q4 returns a temporary object. This cannot bind to the
 *       second argument of the operator for the calculation
 *       q2*(q3*q4) unless it's const (otherwise it will be destroyed
 *       and we will assign a value that's about to disappear!)
 */
Quaternion operator*(const Quaternion &q1, const Quaternion &q2);

// Comparison operators
bool operator==(const Quaternion &q1, const Quaternion &q2);
bool operator!=(const Quaternion &q1, const Quaternion &q2);


/**
 * Quaternion is a base class for performing fast Quaternion arithmetic.
 * A quaternion is a vector with 4 components: q = w + a*i + b*j + c*k,
 * where w is the "real part" of the quaternion and "a*i + b*j + c*k" is
 * the "imaginary" or "vector" part.
 * 
 * This class uses commutative operator overloading for basic arithmetic operations,
 * and supports move semantics for efficient calculations.
 * 
 * The quaternion elements are stored in an std::map container to support
 * sparsity and logarithmic lookup complexity (although it's only 4 elements anyway)
 * 
 * The class implements operations with shared pointers to quaternions
 * as well as regular operations, for increased functionality.
 * 
 * Quaternions are particularly interesting in 3D calculations because they
 * provide a more efficient representation of 3D rotations, e.g., if we
 * want to rotate vector p in 3 space, the new vector p' can be acquired
 * by the operation: p'=qpq^{-1}. Notice how this operation involves less calculations
 * than a regular rotation matrix rotation.
 * 
 * Make sure to report any bugs/design improvements you find! Have fun!
 */

class Quaternion
{
public :
	// Default constructor, initialize to zero
	Quaternion();
	
	// Constructor for all 4 parts
	// Note: to build a quaternion with a custom number of elements
	// use the [] operator.
	Quaternion(double w, double i, double j, double k);
	
	// Destructor
	~Quaternion();
//
	// Copy constructor
	Quaternion(const Quaternion &q);

	// ==========Overload member operators=========
	/* TRIVIA: The binary operators = (assignment), [] (array subscription),
	 * -> (member access), as well as the n-ary () (function call) operator,
	 * must always be implemented as member functions, because the syntax of
	 * the language requires them to.  */

	// Copy Assignment operator
	/* Note: Once we assign a move assignment operator, the default copy
	 * assignment operator is deleted, so we have to explicitly define it if
	 * we wish to maintain the functionality.
	 */
	/* Note how these functions are not marked as inline.
	 * This is because the compiler is smart enough (in most cases) to decide 
	 * on its own what should be inlined when we turn on optimizations
	 */
	void operator=(Quaternion &q); // FIXME: Consider different design, as this doesn't allow reference chaining, i.e., q1=q2=q3

	// Move assignment operator. Activates in instances such as q1=q2*q3
	/* Note: the operator overloading for q2*q3 returns a regular l-value.
	 * The move assignment operator activates if it's used in a temporary
	 * context, e.g.:
	 * Quaternion q1;
	 * q1=q2*q3	 */
	void operator=(Quaternion &&q);

	// Overload operator to get and assign individual values
	double &operator[](AxisType axis){return elements_[axis];}
	// =========Done overloading operators========
	
	/* Get the conjugate of this quaternion */
	Quaternion conjugate();
	
	// Get element iterators
	/* Note: can't be const because the return value is an std::map
	 * element
	 */
	auto elementsBegin(){return elements_.begin();}
	auto elementsEnd(){return elements_.end();}
	
	// Retrieval function for individual elements
	auto getAxisValue(AxisType axis){return elements_[axis];}
	
	// Check whether the quaternion is empty
	/* Note: is the map has not been initilized this will always
	 * return false
	 */
	bool isEmpty() const;

	// Print quaternion
	/* Note: this function has a default argument, as denoted by the "="
	 * assignment. If no argument is provided, it will use cout by default
	 */
	void write(std::ostream &out=cout) const;

	// Get individual values.
	double w()const;
	double i()const;
	double j()const;
	double k()const;

	/* Return the norm |q| = sqrt(\sum a_i^2)*/
	/* Note: Notice that this function is flagged as const. This means that
	 * it is forbidden to modify any private member, such as elements
	 * Also note that we don't return a reference. This is because in C++11
	 * a move operation will be used automatically for all STL objects.
	 * CAUTION: If the return object is of custom type, the programmer needs
	 * to code the move semantics for this to work, even if the object is in
	 * an STL container (e.g. vector<Quaternion> giveMeAQuaternion() const)
	 */
	double norm()const;

private:

	// Elements container. Use map for sparse storage and O(log(n)) lookup complexity
	std::map<AxisType,double> elements_;

}; // End of quaternion class

} // End namespace Quaternions

#endif
