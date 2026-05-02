#include "Appointment.h"
#include "Utils.h"
using namespace std;
Appointment::Appointment(){appointmentID=patientID=doctorID=0; date[0]=timeSlot[0]=status[0]='\0';}
Appointment::Appointment(int a,int p,int d,const char* dt,const char* ts,const char* st){appointmentID=a; patientID=p; doctorID=d; Utils::copyArr(date,dt,11); Utils::copyArr(timeSlot,ts,6); Utils::copyArr(status,st,20);} 
void Appointment::setAppointmentID(int v){appointmentID=v;} void Appointment::setPatientID(int v){patientID=v;} void Appointment::setDoctorID(int v){doctorID=v;} void Appointment::setDate(const char* v){Utils::copyArr(date,v,11);} void Appointment::setTimeSlot(const char* v){Utils::copyArr(timeSlot,v,6);} void Appointment::setStatus(const char* v){Utils::copyArr(status,v,20);} 
int Appointment::getAppointmentID() const{return appointmentID;} int Appointment::getPatientID() const{return patientID;} int Appointment::getDoctorID() const{return doctorID;} const char* Appointment::getDate() const{return date;} const char* Appointment::getTimeSlot() const{return timeSlot;} const char* Appointment::getStatus() const{return status;}
bool Appointment::operator==(const Appointment& o) const{ if(Utils::eq(status,"cancelled")||Utils::eq(o.status,"cancelled")) return false; return doctorID==o.doctorID && Utils::eq(date,o.date) && Utils::eq(timeSlot,o.timeSlot);} 
ostream& operator<<(ostream& out,const Appointment& a){out<<"Appointment ID: "<<a.appointmentID<<" | Patient ID: "<<a.patientID<<" | Doctor ID: "<<a.doctorID<<" | Date: "<<a.date<<" | Time: "<<a.timeSlot<<" | Status: "<<a.status; return out;}
