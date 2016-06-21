/* File Quaternion.cpp
 * 
 * Copyright (c) Nikos Kazazakis 2016
 * \brief Implementation of a Quaternion library in C++14
 */
/* Include the header file of the class. Note that this carries over 
 * any includes we made in the header
 * \author Nikos Kazazakis
 */
#include "Quaternion.h" 
#include <cassert>

// Define our namespace. This conveniently allows us to use all our
// definitions without the Quaternions:: prefix
using namespace Quaternions;

// Default constructor: create zero (nonempty!) quaternion
Quaternion::Quaternion()
{
	// TODO: See about creating a sparse quaternion instead
	// Assign quaternion values
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

// Default destructor. All data in an object is stored in its private members
// so when the object is destroyed we must deallocate that memory.
// An exception is when using shared pointers, where the destructor will simply
// decrease the reference count by 1.
Quaternion::~Quaternion()
{
	elements_.clear();
}

// ===Begin member operator overloading===
// Copy constructor
Quaternion::Quaternion(const Quaternion &q)
{
	cout<<"Copy constructor invoked"<<endl;
}

// Copy assignment operator
void Quaternion::operator=(Quaternion &q)
{
	for (auto it=q.elementsBegin();it!=q.elementsEnd();++it){
		elements_[(*it).first]=(*it).second;
	}
}

// Move assignment operator
void Quaternion::operator=(Quaternion &&q)
{
//	cout<<"Move assignment operator invoked"<<endl;
	for (auto &&it=q.elementsBegin();it!=q.elementsEnd();++it){
		elements_[(*it).first]=(*it).second;
	}

}
// ====End member operator overloading====

Quaternion Quaternion::conjugate()
{
	Quaternion q = Quaternion(w(),-i(),-j(),-k());
	return q;
}

double Quaternion::norm() const
{
	double norm=0.0;
	// Use a const_iterator even though its redundant
	for ( std::map<AxisType,double>::const_iterator element=elements_.begin();element!=elements_.end();++element )
	{
		norm+=pow((*element).second,2);
	}
	norm=std::sqrt(norm);
	return norm;
}

bool Quaternion::isEmpty() const
{
	if (elements_.empty()){
		return true;
	}else{
		return false;
	}
}

void Quaternion::write(std::ostream &out)
{
	for (auto &element : elements_ ){
		if (element.second != 0.0 ){
			cout<<std::showpos<<element.second; // Show the +/- sign if non-zero
		}else{
			cout<<element.second;
		}
		switch (element.first){ // Print the unit vector
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

// ==== Begin non-member operator overloading ===
// shared_ptr versions
// - QuaternionPtr addition
QuaternionPtr Quaternions::operator+(const QuaternionPtr q1, const QuaternionPtr q2)
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion(
			q1->getAxisValue(qw)+q2->getAxisValue(qw),
			q1->getAxisValue(qi)+q2->getAxisValue(qi),
			q1->getAxisValue(qj)+q2->getAxisValue(qj),
			q1->getAxisValue(qk)+q2->getAxisValue(qk) );

	return q;
}

// - QuaternionPtr subtraction
QuaternionPtr Quaternions::operator-(const QuaternionPtr q1, const QuaternionPtr q2)
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion(
			q1->getAxisValue(qw)-q2->getAxisValue(qw),
			q1->getAxisValue(qi)-q2->getAxisValue(qi),
			q1->getAxisValue(qj)-q2->getAxisValue(qj),
			q1->getAxisValue(qk)-q2->getAxisValue(qk) );
	return q;
}

// - Multiplications
//   == Scalar multiplication
QuaternionPtr Quaternions::operator*(const double c, const QuaternionPtr &q2) // double
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion();
	for (auto &&it=q2->elementsBegin();it!=q2->elementsEnd();++it){ // FIXME: Help compiler unroll this loop
		q->operator[]((*it).first)=c*(*it).second;
	}
	return q;
}

QuaternionPtr Quaternions::operator*(const int c, const QuaternionPtr &q2) // int
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion();
	for (auto &&it=q2->elementsBegin();it!=q2->elementsEnd();++it){ // FIXME: Help compiler unroll this loop
		q->operator[]((*it).first)=(double)(c)*(*it).second;
	}
	return q;
}

QuaternionPtr Quaternions::operator*(const QuaternionPtr &q2, const double c) // double
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion();
	for (auto &&it=q2->elementsBegin();it!=q2->elementsEnd();++it){ // FIXME: Help compiler unroll this loop
		q->operator[]((*it).first)=c*(*it).second;
	}
	return q;
}

QuaternionPtr Quaternions::operator*(const QuaternionPtr &q2, const int c) // int
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion();
	for (auto &&it=q2->elementsBegin();it!=q2->elementsEnd();++it){ // FIXME: Help compiler unroll this loop
		q->operator[]((*it).first)=(double)(c)*(*it).second;
	}
	return q;
}

//   == Quaternion multiplication
QuaternionPtr Quaternions::operator*(const QuaternionPtr &q1, const QuaternionPtr &q2) // FIXME: See if I can speed this up
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion();

	// Real part
	q->operator[](qw)=
			 q1->w()*q2->w()
			-q1->i()*q2->i()
			-q1->j()*q2->j()
			-q1->k()*q2->k();
	// i
	q->operator[](qi)=
			 q1->w()*q2->i()
			+q1->i()*q2->w()
			+q1->j()*q2->k()
			-q1->k()*q2->j();
	// j
	q->operator[](qj)=
			 q1->w()*q2->j()
			-q1->i()*q2->k()
			+q1->j()*q2->w()
			+q1->k()*q2->i();
	// k
	q->operator[](qk)=
			 q1->w()*q2->k()
			+q1->i()*q2->j()
			-q1->j()*q2->i()
			+q1->k()*q2->w();

	return q;
}

// Object operator overloading
// - Quaternion addition
Quaternion Quaternions::operator+(Quaternion &q1, Quaternion &q2)
{
	if (q1.isEmpty() && q2.isEmpty() ){
		assert(!"Addition of two uninitialized quaternions"); // FIXME: this doesn't properly detect the uninitialized map
	}
	Quaternion q = Quaternion(
			q1.getAxisValue(qw)+q2.getAxisValue(qw),
			q1.getAxisValue(qi)+q2.getAxisValue(qi),
			q1.getAxisValue(qj)+q2.getAxisValue(qj),
			q1.getAxisValue(qk)+q2.getAxisValue(qk) );

	return q;
}
// Quaternion subtraction
Quaternion Quaternions::operator-(Quaternion &q1, Quaternion &q2)
{
	if (q1.isEmpty() && q2.isEmpty() ){
		assert(!"Subtraction of two uninitialized quaternions"); // FIXME: this doesn't properly detect the uninitialized map
	}
	Quaternion q = Quaternion(
			q1.getAxisValue(qw)-q2.getAxisValue(qw),
			q1.getAxisValue(qi)-q2.getAxisValue(qi),
			q1.getAxisValue(qj)-q2.getAxisValue(qj),
			q1.getAxisValue(qk)-q2.getAxisValue(qk) );

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
		q[(*it).first]=(double)(c)*(*it).second;
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
		q[(*it).first]=(double)(c)*(*it).second;
	}
	return q;
}

// == Quaternion multiplication
Quaternion Quaternions::operator*(Quaternion &q1, Quaternion &q2) // FIXME: See if I can speed this up
{
	Quaternion q = Quaternion();
	// Real part
	q[qw]=	 q1.w()*q2.w()
			-q1.i()*q2.i()
			-q1.j()*q2.j()
			-q1.k()*q2.k();
	// i
	q[qi]=
			 q1.w()*q2.i()
			+q1.i()*q2.w()
			+q1.j()*q2.k()
			-q1.k()*q2.j();
	// j
	q[qj]=
			 q1.w()*q2.j()
			-q1.i()*q2.k()
			+q1.j()*q2.w()
			+q1.k()*q2.i();
	// k
	q[qk]=
			 q1.w()*q2.k()
			+q1.i()*q2.j()
			-q1.j()*q2.i()
			+q1.k()*q2.w();
//	cout<<"returning move operation"<<endl;
//	q.write(cout);cout<<endl;
	return q;
}
// ======End non-member operator overloading======


