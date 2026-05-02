#include "Patient.h"
#include "Utils.h"
using namespace std;
Patient::Patient():Person(){age=0; gender[0]='\0'; contact[0]='\0'; balance=0;}
Patient::Patient(int i,const char* n,int a,const char* g,const char* c,const char* p,float b):Person(i,n,p){age=a; Utils::copyArr(gender,g,10); Utils::copyArr(contact,c,20); balance=b;}
Patient::Patient(const Patient& o):Person(o){age=o.age; Utils::copyArr(gender,o.gender,10); Utils::copyArr(contact,o.contact,20); balance=o.balance;}
Patient& Patient::operator=(const Patient& o){ if(this!=&o){Person::operator=(o); age=o.age; Utils::copyArr(gender,o.gender,10); Utils::copyArr(contact,o.contact,20); balance=o.balance;} return *this; }
void Patient::setAge(int v){age=v;} void Patient::setGender(const char* v){Utils::copyArr(gender,v,10);} void Patient::setContact(const char* v){Utils::copyArr(contact,v,20);} void Patient::setBalance(float v){balance=v;}
int Patient::getAge() const{return age;} const char* Patient::getGender() const{return gender;} const char* Patient::getContact() const{return contact;} float Patient::getBalance() const{return balance;}
void Patient::operator+=(float x){balance+=x;} void Patient::operator-=(float x){balance-=x;} bool Patient::operator==(const Patient& o) const{return id==o.id;} void Patient::display() const{cout<<*this<<"\n";} void Patient::printRole() const{cout<<"Patient";}
ostream& operator<<(ostream& out,const Patient& p){out<<"Patient ID: "<<p.id<<" | Name: "<<p.name<<" | Age: "<<p.age<<" | Gender: "<<p.gender<<" | Contact: "<<p.contact<<" | Balance: PKR "<<p.balance; return out;}
