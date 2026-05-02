#include "Admin.h"
#include <iostream>
using namespace std;
Admin::Admin():Person(){
} 
Admin::Admin(int i,const char* n,const char* p):Person(i,n,p){} 
void Admin::display() const{
cout<<"Admin ID: "<<id<<" | Name: "<<name<<"\n";
} 
void Admin::printRole() const{cout<<"Admin";
}
