#include "Doctor.h"
#include "Utils.h"
using namespace std;
Doctor::Doctor():Person(){specialization=0; 
Utils::copy(specialization,"");
contact[0]='\0'; fee=0;}
Doctor::Doctor(int i,const char* n,const char* s,const char* c,const char* p,float f):Person(i,n,p){specialization=0; Utils::copy(specialization,s); Utils::copyArr(contact,c,20); fee=f;}
Doctor::Doctor(const Doctor& o):Person(o){specialization=0; Utils::copy(specialization,o.specialization); Utils::copyArr(contact,o.contact,20); fee=o.fee;}
Doctor& Doctor::operator=(const Doctor& o){ if(this!=&o){Person::operator=(o); Utils::copy(specialization,o.specialization); Utils::copyArr(contact,o.contact,20); fee=o.fee;} return *this; }
Doctor::~Doctor(){delete[] specialization;}
void Doctor::setSpecialization(const char* v){Utils::copy(specialization,v);} void Doctor::setContact(const char* v){Utils::copyArr(contact,v,20);} void Doctor::setFee(float v){fee=v;}
const char* Doctor::getSpecialization() const{return specialization;} const char* Doctor::getContact() const{return contact;} float Doctor::getFee() const{return fee;} bool Doctor::operator==(const Doctor& o) const{return id==o.id;} void Doctor::display() const{cout<<*this<<"\n";} void Doctor::printRole() const{cout<<"Doctor";}
ostream& operator<<(ostream& out,const Doctor& d){out<<"Doctor ID: "<<d.id<<" | Name: "<<d.name<<" | Specialization: "<<d.specialization<<" | Contact: "<<d.contact<<" | Fee: PKR "<<d.fee; return out;}
