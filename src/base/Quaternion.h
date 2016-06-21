/* File Quaternion.h
 * 
 * Copyright (c) Nikos Kazazakis 2016
 * \brief Define Quaternion class for quaternion arithmetic in C++14
 * \author Nikos Kazazakis
 */

#ifndef QUATERNION_LIB // Define macro headers so that this file doesn't get included twice
#define QUATERNION_LIB

// Include STL headers
#include <iostream>
#include <cmath>
#include <memory>
#include <map>

// Define some commonly used std functions for convenience
/* Note how we don't simply use "using namespace std;"
 * This is bad practice because we implicitly load all the std library
 * names, causing unnecessary potential naming conflicts.
 * Even worse, if someone includes a library using namespace std,
 * it will include all the std names without the user realising.
 */
using std::shared_ptr;
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

// Forward-declare the class to define its shared pointer and operators
class Quaternion;
typedef shared_ptr<Quaternion> QuaternionPtr;

// You might be tempted to make these const, but remember! Non-member functions
// cannot be const!
// == Pointer versions
// - Addition and subtraction
QuaternionPtr operator+(const QuaternionPtr q1, const QuaternionPtr q2);  
QuaternionPtr operator-(const QuaternionPtr q1, const QuaternionPtr q2);

// - Multiplication
//   == Scalar multiplications
/* Note how we DO NOT pass primitives (double, int) by reference. This is because:
 *  - primitives are blitable, so the cost of the copy depends on the size
 *  - primitives are small, only double and long long are bigger than a reference in most environments
 *  - pass-by-value avoids aliasing, allowing the optimizer to really do its thing
 */ 
QuaternionPtr operator*(const double c, const QuaternionPtr &q2);
QuaternionPtr operator*(const int c, const QuaternionPtr &q2); // int will be casted to double
QuaternionPtr operator*(const QuaternionPtr &q2,const double c);
QuaternionPtr operator*(const QuaternionPtr q2, const int c); // int will be casted to double
//   ==Quaternion multiplication
QuaternionPtr operator*(const QuaternionPtr &q1, const QuaternionPtr &q2);

// == Object versions
// - Addition and subtraction
Quaternion operator+(Quaternion &q1, Quaternion &q2);  // std::map[] can't be const
Quaternion operator-(Quaternion &q1, Quaternion &q2);
// - Multiplication
//   == Scalar multiplications
Quaternion operator*(const double c, Quaternion &q2);
Quaternion operator*(const int c, Quaternion &q2);
//   ==Quaternion multiplication
Quaternion operator*(Quaternion &q1, Quaternion &q2);

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
 * sparsity and logarithmic lookup complexity.
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

	// ====Overload member operators===
	/* TRIVIA: The binary operators = (assignment), [] (array subscription),
	 * -> (member access), as well as the n-ary () (function call) operator,
	 * must always be implemented as member functions, because the syntax of
	 * the language requires them to.  */

	// Copy Assignment operator
	/* Note: Once we assign a move assignment operator, the default copy
	 * assignment operator is deleted, so we have to explicitly define it if
	 * we wish to maintain the functionality.
	 */
	void operator=(Quaternion &q);

	// Move assignment operator. Activates in instances such as q1=q2*q3
	/* Note: the operator overloading for q2*q3 returns a regular l-value.
	 * The move assignment operator activates if it's used in a temporary
	 * context, e.g.:
	 * Quaternion q1;
	 * q1=q2*q3	 */
	void operator=(Quaternion &&q);

	// Overload operator to get and assign individual values
	double &operator[](AxisType axis){return elements_[axis];}
	// ===Done overloading operators===

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
	 * assignment. If not argument is provided, it will use cout by default
	 */
	void write(std::ostream &out=cout);

	// Get individual values. Note: to return a reference use operator[]
	/* Note: even though these are not const, direct assignment is illegal
	* because you are retrieving a copy of the value. 
	*/
	double w(){return elements_[qw];}
	double i(){return elements_[qi];}
	double j(){return elements_[qj];}
	double k(){return elements_[qk];}

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

};

}

#endif
