#ifndef ADMIN_H
#define ADMIN_H
#include "Person.h"
class Admin: public Person{
public:
    Admin();
    Admin(int,const char*,const char*);
    void display() const;
    void printRole() const;
};
#endif
