#include "Bill.h"
#include "Utils.h"
Bill::Bill(){billID=patientID=appointmentID=0; amount=0; status[0]=date[0]='\0';}
Bill::Bill(int b,int p,int a,float am,const char* s,const char* d){billID=b; patientID=p; appointmentID=a; amount=am; Utils::copyArr(status,s,20); Utils::copyArr(date,d,11);} 
int Bill::getBillID() const{return billID;} int Bill::getPatientID() const{return patientID;} int Bill::getAppointmentID() const{return appointmentID;} float Bill::getAmount() const{return amount;} const char* Bill::getStatus() const{return status;} const char* Bill::getDate() const{return date;} void Bill::setBillID(int v){billID=v;} void Bill::setPatientID(int v){patientID=v;} void Bill::setAppointmentID(int v){appointmentID=v;} void Bill::setAmount(float v){amount=v;} void Bill::setStatus(const char* v){Utils::copyArr(status,v,20);} void Bill::setDate(const char* v){Utils::copyArr(date,v,11);} 
