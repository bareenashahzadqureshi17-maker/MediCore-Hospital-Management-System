#ifndef PATIENT_H
#define PATIENT_H
#include "Person.h"
#include <iostream>
class Patient: public Person{
    int age; char gender[10]; char contact[20]; float balance;
public:
    Patient(); 
    Patient(int,const char*,int,const char*,const char*,const char*,float); 
    Patient(const Patient&); Patient& operator=(const Patient&);
    void setAge(int);
    void setGender(const char*);
    void setContact(const char*);
    void setBalance(float);
    int getAge() 
    const;
    const char* getGender() const; const char* getContact() const;
    float getBalance() const;
    void operator+=(float); void operator-=(float); 
    bool operator==(const Patient&) const;
    void display() const;
    void printRole() const;
    friend std::ostream& operator<<(std::ostream&, const Patient&);
};
#endif
