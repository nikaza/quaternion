/* File Quaternion.cpp
 * 
 * Copyright (c) Nikos Kazazakis 2016
 * \brief Implementation of a Quaternion arithmetic library in C++14
 * \author Nikos Kazazakis
 */

/* Include the header file of the class. Note that this carries over 
 * any includes we made in the header */
#include "Quaternion.h"

// Other includes
#include <cassert>

// Define our namespace. This conveniently allows us to use all our
// definitions without the Quaternions:: prefix
using namespace Quaternions;

// Default constructor: create zero (nonempty!) quaternion
Quaternion::Quaternion() // TODO: Think about creating a sparse quaternion instead
{
	// Assign quaternion values using std::map
	// - Real part
	elements_[qw]=0;
	// - Vector part
	elements_[qi]=0;
	elements_[qj]=0;
	elements_[qk]=0;
}

// Consrtuct a quaternion by defining all its elements
Quaternion::Quaternion(double w, double i, double j, double k)
{
	// Assign quaternion values
	// - Real part
	if (w!=0){elements_[qw]=w;} // The quaternion is sparse; we only assign a value if it's non-zero
	// - Vector part
	if (i!=0){elements_[qi]=i;}
	if (j!=0){elements_[qj]=j;}
	if (k!=0){elements_[qk]=k;}
}

// Default destructor. All data in an object is (usually) stored in its private members
// so when the object is destroyed we must deallocate that memory.
// An exception is when using shared pointers, where the destructor will simply
// decrease the reference count by 1.
// It is good practice to write code for the destruction of an object here when you 
// first create it, to avoid memory leaks
Quaternion::~Quaternion()
{
	 // Techincally not necessary because it's an STL object, but good practice to 
	//  get in the habid of destroying the private members
	elements_.clear();
}

// ===Begin member operator overloading===
// Copy constructor
Quaternion::Quaternion(const Quaternion &q)
{
	// Currently a place holder, we don't use this yet
	cout<<"Copy constructor invoked (not yet implemented)"<<endl;
	// Don't let the user run this thinking it's working
	assert(!"Copy constructor invoked (not yet implemented)"); 
}

// Copy assignment operator
void Quaternion::operator=(Quaternion &q) // has to return void to agree with our move semantics
{
	/* Use ranged-for loop for better performance. We don't want to give this permission
	 * to access the map, by writing a public function to return it, so we access it as 
	 * a private member
	 */
	/* Note: you'll see further down that we use old-style C++ loops for the non-member operators
	 *       this is because non-members don't have access to elements_ (it's private)! Can be 
	 *       changed using "friends", but I find that too permissive
	 */
	for (auto &element : q.elements_ ){ 
		elements_[element.first]=element.second;                 
	}  
}

// Move assignment operator
void Quaternion::operator=(Quaternion &&q)
{
//	cout<<"Move assignment operator invoked"<<endl;
	for (auto &&element : q.elements_ ){ 
		elements_[element.first]=element.second;                 
	}  
}

// ====End member operator overloading====

// Return the conjugate of this quaternion. C++11 moves the q stack variable to
// the return output automatically
Quaternion Quaternion::conjugate()
{
	Quaternion q = Quaternion(w(),-i(),-j(),-k());
	return q;
}

// Return the norm of the quaternion
double Quaternion::norm() const
{
	double norm=0.0;
	// Use a const_iterator even though its redundant (it's good practice!)
	// This is an old-style C++ loop, here for demonstration reasons. 
	// For the new loops we can use for (const auto ...) instead of the const_iterator
	// TODO: replace this with a C++11 version in next revision
	for ( std::map<AxisType,double>::const_iterator element=elements_.begin();element!=elements_.end();++element )
	{
		norm+=pow((*element).second,2); // TODO: Use bitwise operations to massively improve speed
	}
	norm=std::sqrt(norm);
	return norm;
}

// Return whether the elements_ map size is zero
bool Quaternion::isEmpty() const
{
	if (elements_.empty()){
		return true;
	}else{
		return false;
	}
}

// Print output. Prints to cout by default
void Quaternion::write(std::ostream &out) const
{
	for (const auto &element : elements_ ){ // We use a reference to the elements to avoid a copy!
		if (element.second != 0.0 ){
			cout<<std::showpos<<element.second; // Show the +/- sign if non-zero
		}else{
			cout<<element.second;
		}
		switch (element.first){ // Print the appropriate unit vectors
		case qw:
			break;
		case qi:
			cout<<"i";
			break;
		case qj:
			cout<<"j";
			break;
		case qk:
			cout<<"k";
			break;
		default:
			// No default behaviour specified, break
			break;
		}
	}
	cout<<std::noshowpos; // Reset the showpos format
}

double Quaternion::w() const
{
	if ( elements_.find(qw) == elements_.end() ) {
		return 0.0;
	} else {
		return elements_.at(qw);
	}
}

double Quaternion::i() const
{
	if ( elements_.find(qi) == elements_.end() ) {
		return 0.0;
	} else {
		return elements_.at(qi);
	}
}

double Quaternion::j() const
{
	if ( elements_.find(qj) == elements_.end() ) {
		return 0.0;
	} else {
		return elements_.at(qj);
	}
}

double Quaternion::k() const
{
	if ( elements_.find(qk) == elements_.end() ) {
		return 0.0;
	} else {
		return elements_.at(qk);
	}
}
// ==== Begin non-member operator overloading ===
// - Quaternion addition
Quaternion Quaternions::operator+(const Quaternion &q1, const Quaternion &q2)
{
	if (q1.isEmpty() && q2.isEmpty() ){
		assert(!"Addition of two uninitialized quaternions"); // FIXME: this doesn't properly detect the uninitialized map
	}
	Quaternion q = Quaternion(
			q1.w()+q2.w(),
			q1.i()+q2.i(),
			q1.j()+q2.j(),
			q1.k()+q2.k() );

	return q;
}

Quaternion Quaternions::operator+(const double c, const Quaternion &q2)
{
	if (q2.isEmpty() ){
		assert(!"Addition of two uninitialized quaternions"); // FIXME: this doesn't properly detect the uninitialized map
	}
	Quaternion q = Quaternion(
			c+q2.w(),
			c+q2.i(),
			c+q2.j(),
			c+q2.k() );

	return q;
}

Quaternion Quaternions::operator+(const Quaternion &q2, const double c)
{
	if (q2.isEmpty() ){
		assert(!"Addition of two uninitialized quaternions"); // FIXME: this doesn't properly detect the uninitialized map
	}
	Quaternion q = Quaternion(
			c+q2.w(),
			c+q2.i(),
			c+q2.j(),
			c+q2.k() );

	return q;
}

// Quaternion subtraction
Quaternion Quaternions::operator-(const Quaternion &q1, const Quaternion &q2)
{
	if (q1.isEmpty() && q2.isEmpty() ){
		assert(!"Subtraction of two uninitialized quaternions"); // FIXME: this doesn't properly detect the uninitialized map
	}
	Quaternion q = Quaternion(
			q1.w()-q2.w(),
			q1.i()-q2.i(),
			q1.j()-q2.j(),
			q1.k()-q2.k() );

	return q;
}

Quaternion Quaternions::operator-(const double c, const Quaternion &q2)
{
	if (q2.isEmpty() ){
		assert(!"Subtraction of two uninitialized quaternions"); // FIXME: this doesn't properly detect the uninitialized map
	}
	Quaternion q = Quaternion(
			c-q2.w(),
			c-q2.i(),
			c-q2.j(),
			c-q2.k() );

	return q;
}

Quaternion Quaternions::operator-(const Quaternion &q2, const double c)
{
	if (q2.isEmpty() ){
		assert(!"Subtraction of two uninitialized quaternions"); // FIXME: this doesn't properly detect the uninitialized map
	}
	Quaternion q = Quaternion(
			q2.w()-c,
			q2.i()-c,
			q2.j()-c,
			q2.k()-c );

	return q;
}

// - Multiplication
//   == Scalar multiplication
Quaternion Quaternions::operator*(const double c, Quaternion &q2) // double
{
	Quaternion q = Quaternion();
	for (auto &&it=q2.elementsBegin();it!=q2.elementsEnd();++it){ // FIXME: Help compiler unroll this loop
		q[(*it).first]=c*(*it).second;
	}
	return q;
}

Quaternion Quaternions::operator*(const int c, Quaternion &q2) // int
{
	Quaternion q = Quaternion();
	for (auto &&it=q2.elementsBegin();it!=q2.elementsEnd();++it){ // FIXME: Help compiler unroll this loop
		q[(*it).first]=(double)(c)*(*it).second;  // Typecast int to double
	}
	return q;
}

Quaternion Quaternions::operator*(Quaternion &q2, const double c) // double
{
	Quaternion q = Quaternion();
	for (auto &&it=q2.elementsBegin();it!=q2.elementsEnd();++it){ // FIXME: Help compiler unroll this loop
		q[(*it).first]=c*(*it).second;
	}
	return q;
}

Quaternion Quaternions::operator*(Quaternion &q2, const int c) // int
{
	Quaternion q = Quaternion();
	for (auto &&it=q2.elementsBegin();it!=q2.elementsEnd();++it){ // FIXME: Help compiler unroll this loop
		q[(*it).first]=(double)(c)*(*it).second;  // Typecast int to double
	}
	return q;
}

// == Quaternion multiplication
Quaternion Quaternions::operator*(const Quaternion &q1, const Quaternion &q2) // FIXME: See if I can speed this up
{
	Quaternion q = Quaternion();
	// Real part
	q[qw]=	 q1.w()*q2.w()
		-q1.i()*q2.i()
		-q1.j()*q2.j()
		-q1.k()*q2.k();
	// i
	q[qi]=   q1.w()*q2.i()
		+q1.i()*q2.w()
		+q1.j()*q2.k()
		-q1.k()*q2.j();
	// j
	q[qj]=   q1.w()*q2.j()
		-q1.i()*q2.k()
		+q1.j()*q2.w()
		+q1.k()*q2.i();
	// k
	q[qk]=   q1.w()*q2.k()
		+q1.i()*q2.j()
		-q1.j()*q2.i()
		+q1.k()*q2.w();
//	cout<<"returning move operation"<<endl;
	return q;
}

// Comparison operators
bool Quaternions::operator==(const Quaternion &q1, const Quaternion &q2)
{
	bool isEqual=true; // Initialize in case q1.w is empty

	isEqual = (q1.w()==q2.w());
	if (isEqual){isEqual = (q1.i()==q2.i());}
	if (isEqual){isEqual = (q1.j()==q2.j());}
	if (isEqual){isEqual = (q1.k()==q2.k());}

	return isEqual;
}

bool Quaternions::operator!=(const Quaternion &q1, const Quaternion &q2)
{
	return !(q1==q2);
}
// ======End non-member operator overloading======

// End of file
