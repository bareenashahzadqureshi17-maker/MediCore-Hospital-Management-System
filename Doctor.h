#ifndef DOCTOR_H
#define DOCTOR_H
#include "Person.h"
#include <iostream>
class Doctor: public Person{
    char* specialization; 
    char contact[20];
    float fee;
public:
    Doctor();
    Doctor(int,const char*,const char*,const char*,const char*,float);
    Doctor(const Doctor&); Doctor& operator=(const Doctor&); 
    ~Doctor();
    void setSpecialization(const char*); 
    void setContact(const char*); 
    void setFee(float);
    const char* getSpecialization() const; 
    const char* getContact() const; 
    float getFee() const;
    bool operator==(const Doctor&) const;
    void display() const;
    void printRole() const;
    friend std::ostream& operator<<(std::ostream&, const Doctor&);
};
#endif
