#include "Quaternion.h"
#include <vector>
#include <cassert>

using namespace Quaternions;

// Default constructor: create zero quaternion
Quaternion::Quaternion()
{
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

// Default destructor
Quaternion::~Quaternion()
{
	elements_.clear();
}

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

void Quaternion::write(std::ostream &out)
{
	int counter=0;
	for (auto &element : elements_ ){
//		cout<<element.second<<endl;
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
			break;
			// No default handled
		}
		++counter;
	}
	cout<<std::noshowpos; // Reset the showpos format
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

bool Quaternion::isEmpty()
{
	if (elements_.empty()){
		return true;
	}else{
		return false;
	}
}
// QuaternionPtr addition
QuaternionPtr Quaternions::operator+(const QuaternionPtr q1, const QuaternionPtr q2)
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion(
			q1->getAxis(qw)+q2->getAxis(qw),
			q1->getAxis(qi)+q2->getAxis(qi),
			q1->getAxis(qj)+q2->getAxis(qj),
			q1->getAxis(qk)+q2->getAxis(qk) );

	return q;
}

// Quaternion addition
Quaternion &Quaternions::operator+(Quaternion &q1, Quaternion &q2)
{
	if (q1.isEmpty() && q2.isEmpty() ){
		assert(!"Addition of two uninitialized quaternions");
	}
	Quaternion q = Quaternion(
			q1.getAxis(qw)+q2.getAxis(qw),
			q1.getAxis(qi)+q2.getAxis(qi),
			q1.getAxis(qj)+q2.getAxis(qj),
			q1.getAxis(qk)+q2.getAxis(qk) );

	return q;
}

QuaternionPtr Quaternions::operator-(const QuaternionPtr q1, const QuaternionPtr q2)
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion(
			q1->getAxis(qw)-q2->getAxis(qw),
			q1->getAxis(qi)-q2->getAxis(qi),
			q1->getAxis(qj)-q2->getAxis(qj),
			q1->getAxis(qk)-q2->getAxis(qk) );
	return q;
}

QuaternionPtr Quaternions::operator*(const double c, const QuaternionPtr q2)
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion();
	for (auto &&it=q2->elementsBegin();it!=q2->elementsEnd();++it){ // Compiler should unroll this loop
		q->operator[]((*it).first)=c*(*it).second;
	}
	return q;
}
//
QuaternionPtr Quaternions::operator*(const int c, const QuaternionPtr q2)
{
	QuaternionPtr q = (QuaternionPtr) new Quaternion();
	for (auto &&it=q2->elementsBegin();it!=q2->elementsEnd();++it){ // Compiler should unroll this loop
		q->operator[]((*it).first)=(double)(c)*(*it).second;
	}
	return q;
}

QuaternionPtr Quaternions::operator*(const QuaternionPtr q1, const QuaternionPtr q2)
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

// Quanternion multiplication
Quaternion Quaternions::operator*(Quaternion &q1, Quaternion &q2)
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


