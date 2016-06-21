/* File main.cpp
 * 
 * Copyright (c) Nikos Kazazakis 2016
 * \brief Example of performing quaternion calcluations using the Quaternion class
 * \author Nikos Kazazakis
 */

// Program description: 
// Sample program to test the operator overloading and assignment operators. 
// Will implement quaternion rotations in the next revision.

#include "Quaternion.h"

using namespace Quaternions;

int main()
{
	// Test shared pointer quaternions
	// ===============================
	// - Initialize some quaternion shared pointers
	QuaternionPtr q = (QuaternionPtr) new Quaternion(0,2,0,4);
	QuaternionPtr q1 = (QuaternionPtr) new Quaternion(1,5,2,4);

	// - Print the quaternions
	cout<<"\n\nMy shared_ptr quaternions are : "<<endl;
	cout<<"==============================="<<endl;
	cout<<"q   : \t";q->write();
	cout<<"\nq1  : \t";q1->write();
	
	// - Test addition operator
	cout<<"\n\nTest affine operators :"<<endl;
	cout<<"======================="<<endl;	
	// -- Addition
	QuaternionPtr q2 = q+q1;
	cout<<"q2=q+q1  :  ";q2->write();
	// -- Subtraction
	QuaternionPtr q3 = q-q1;
	cout<<"\nq3=q-q1  :  ";q3->write();

	cout<<"\n\nTest multiplication and assignment:"<<endl;
	cout<<"==================================="<<endl;	
	// -- Multiplication and assignment
	q3=q1*q2;
	cout<<"q3=q1*q2 : ";q3->write();cout<<endl;
	cout<<"2.5*q2   : ";(2.5*q2)->write(cout);cout<<endl;
	cout<<"q2*2.5   : ";(q2*2.5)->write(cout);cout<<endl;

	// Test non-pointer operator overloading and move semantics
	// ========================================================
	cout<<"\n\nCreating regular quaternions"<<endl;
	cout<<"============================"<<endl;	
	Quaternion qt = Quaternion(1,1,1,1);
	Quaternion qt1 = Quaternion(0,1,1,1);
	cout<<"qt  : \t";qt.write();
	cout<<"\nqt1 : \t";qt1.write();

	// - Use move assignment operator
	Quaternion qt2; // Declare but don't call constructor
	cout<<"\n\nUsing move assignment operator for qt2=qt*qt1  :\n  qt2 = ";
	qt2=qt*qt1;
	qt2.write();cout<<endl;

	// - Use copy constructor with move assignment operator
	cout<<"Using copy constructor with move assignment operator for qt3=qt2*qt1  :\n  qt3 = ";
	Quaternion qt3=Quaternion(qt2*qt1);
	qt3.write(cout);cout<<endl;
	
	// - Test other member functions
	cout<<"\n\nTesting other member functions"<<endl;
	cout<<"==============================="<<endl;
	// -- Conjugate quaternion
	cout<<"Conjugate of qt3 : ";
	Quaternion qt4=qt3.conjugate();
	qt4.write(cout);cout<<endl;
	// -- Quaternion norm
	cout<<"Norm(qt3)        : "<<qt3.norm()<<endl;
	cout<<endl<<endl; // Insert two trailing lines at the end of the test

	return 0;
	// Shared_ptrs will be automatically deallocated at the end of scope!
}
