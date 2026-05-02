#ifndef PERSON_H
#define PERSON_H
class Person{
protected:
    int id; char* name; char* password;
public:
    Person(); 
    Person(int,const char*,const char*); 
    Person(const Person&);
    Person& operator=(const Person&); 
    virtual ~Person();
    int getID() const; 
    const char* getName() const;
    const char* getPassword() const;
    void setID(int); 
    void setName(const char*);
    void setPassword(const char*);
    virtual void display() const=0;
    virtual void printRole() const=0;
};
#endif
