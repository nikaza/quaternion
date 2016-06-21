#include <iostream>
#include "Quaternion.h"

using std::cout;
using std::cin;
using std::endl;
using std::shared_ptr;
using namespace Quaternions;

typedef shared_ptr<Quaternion> QuaternionPtr;

int main()
{
//	Quaternion q = (QuaternionPtr) new Quaternion(1,2,3,4);
	QuaternionPtr q = (QuaternionPtr) new Quaternion(0,2,0,4);
	QuaternionPtr q1 = (QuaternionPtr) new Quaternion(1,5,2,4);

	cout<<endl<<endl;
	cout<<"My shared_ptr quaternions are : "<<endl<<endl;
	cout<<"q      : \t";q->write(cout);cout<<endl;
	cout<<"q1     : \t";q1->write(cout);
	cout<<"\nq2=q+q1:\t";
	QuaternionPtr q2 = q+q1;
	q2->write(cout);
	cout<<"\nq3=q-q1:\t";
	QuaternionPtr q3 = q-q1;
	q3->write(cout);

	cout<<"\nNorm(q3) : "<<q3->norm()<<endl;
	cout<<"2.5*q1   : ";(2.5*q2)->write(cout);cout<<endl;
	cout<<"q3=q1*q2 : ";
	q3=q1*q2;
	q3->write(cout);cout<<endl;


	Quaternion qt = Quaternion(1,1,1,1);
	Quaternion qt1 = Quaternion(0,1,1,1);

	cout<<"\ncreating regular quaternions"<<endl;
	// Use move assignment operator
	Quaternion qt2;
	cout<<"Using move assignment operator for qt2=qt*qt1  :  qt2 = ";
	qt2=qt*qt1;
	qt2.write(cout);
	cout<<endl;

	// Use copy constructor with move assignment operator
	cout<<"Using copy constructor with move assignment operator for qt3=qt2*qt1  :  qt3 = ";
	Quaternion qt3=Quaternion(qt2*qt1);
	qt3.write(cout);

	cout<<endl<<endl;

	return 0;
}
