#include "Person.h"
#include "Utils.h"
Person::Person(){id=0; name=0; password=0; Utils::copy(name,""); Utils::copy(password,"");}
Person::Person(int i,const char* n,const char* p){id=i; name=0; password=0; Utils::copy(name,n); Utils::copy(password,p);} 
Person::Person(const Person& o){id=o.id; name=0; password=0; Utils::copy(name,o.name); Utils::copy(password,o.password);} 
Person& Person::operator=(const Person& o){ if(this!=&o){id=o.id; Utils::copy(name,o.name); Utils::copy(password,o.password);} return *this; }
Person::~Person(){delete[] name; delete[] password;}
int Person::getID() const{return id;} const char* Person::getName() const{return name;} const char* Person::getPassword() const{return password;}
void Person::setID(int v){id=v;} void Person::setName(const char* v){Utils::copy(name,v);} void Person::setPassword(const char* v){Utils::copy(password,v);} 
