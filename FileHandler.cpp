#define _CRT_SECURE_NO_WARNINGS
#include "FileHandler.h"
#include "Utils.h"
#include <fstream>
#include <ctime>
using namespace std;
void FileHandler::ensureFilesExist()
{
const char* n[8]={"patients.txt","doctors.txt","admin.txt","appointments.txt","prescriptions.txt","bills.txt","security_log.txt","discharged.txt"};
for(int i=0;i<8;i++)
{fstream f(n[i],ios::in);
if(!f)
{fstream c(n[i],ios::out); 
c.close();
}

else 
f.close();
}
}
void FileHandler::loadPatients(Storage<Patient>& s)
{
s.clear();
ifstream f("patients.txt"); 
char line[1000];
while(f.getline(line,1000))
{
if(Utils::len(line)==0)
continue;
char t[7][500]; 
int c=0;
Utils::splitCSV(line,t,c,7);
if(c==7) 
s.add(Patient(Utils::toInt(t[0]),t[1],Utils::toInt(t[2]),t[3],t[4],t[5],Utils::toFloat(t[6])));
}
}
void FileHandler::loadDoctors(Storage<Doctor>& s)
{
s.clear();
ifstream f("doctors.txt"); 
char line[1000]; 
while(f.getline(line,1000))
{
if(Utils::len(line)==0)
continue; 

char t[6][500];
int c=0; Utils::splitCSV(line,t,c,6); 
if(c==6)
s.add(Doctor(Utils::toInt(t[0]),t[1],t[2],t[3],t[4],Utils::toFloat(t[5])));
}
}
void FileHandler::loadAdmins(Storage<Admin>& s)
{
s.clear(); 
ifstream f("admin.txt");
char line[1000];
while(f.getline(line,1000))
{
if(Utils::len(line)==0)
continue; 
char t[3][500];
int c=0; Utils::splitCSV(line,t,c,3);
if(c==3)
s.add(Admin(Utils::toInt(t[0]),t[1],t[2]));
}
}
void FileHandler::loadAppointments(Storage<Appointment>& s)
{
s.clear();
ifstream f("appointments.txt");
char line[1000];
while(f.getline(line,1000))
{
if(Utils::len(line)==0)
continue; 
char t[6][500]; 
int c=0; Utils::splitCSV(line,t,c,6);
if(c==6)
s.add(Appointment(Utils::toInt(t[0]),Utils::toInt(t[1]),Utils::toInt(t[2]),t[3],t[4],t[5]));
}
}
void FileHandler::loadBills(Storage<Bill>& s)
{
s.clear();
ifstream f("bills.txt"); 
char line[1000];
while(f.getline(line,1000))
{
if(Utils::len(line)==0)
continue; 
char t[6][500]; 
int c=0; 
Utils::splitCSV(line,t,c,6); 
if(c==6) 
s.add(Bill(Utils::toInt(t[0]),Utils::toInt(t[1]),Utils::toInt(t[2]),Utils::toFloat(t[3]),t[4],t[5]));
}
}
void FileHandler::loadPrescriptions(Storage<Prescription>& s)
{
s.clear();
ifstream f("prescriptions.txt");
char line[1500];
while(f.getline(line,1500))
{
if(Utils::len(line)==0) 
continue;
char t[7][500];
int c=0;
Utils::splitCSV(line,t,c,7);
if(c==7) 
s.add(Prescription(Utils::toInt(t[0]),Utils::toInt(t[1]),Utils::toInt(t[2]),Utils::toInt(t[3]),t[4],t[5],t[6]));
}
}
void FileHandler::savePatients(const Storage<Patient>& s){ofstream f("patients.txt"); const Patient* a=s.getAll(); for(int i=0;i<s.size();i++) f<<a[i].getID()<<","<<a[i].getName()<<","<<a[i].getAge()<<","<<a[i].getGender()<<","<<a[i].getContact()<<","<<a[i].getPassword()<<","<<a[i].getBalance()<<"\n"; }
void FileHandler::saveDoctors(const Storage<Doctor>& s){ofstream f("doctors.txt"); const Doctor* a=s.getAll(); for(int i=0;i<s.size();i++) f<<a[i].getID()<<","<<a[i].getName()<<","<<a[i].getSpecialization()<<","<<a[i].getContact()<<","<<a[i].getPassword()<<","<<a[i].getFee()<<"\n"; }
void FileHandler::saveAppointments(const Storage<Appointment>& s){ofstream f("appointments.txt"); const Appointment* a=s.getAll(); for(int i=0;i<s.size();i++) f<<a[i].getAppointmentID()<<","<<a[i].getPatientID()<<","<<a[i].getDoctorID()<<","<<a[i].getDate()<<","<<a[i].getTimeSlot()<<","<<a[i].getStatus()<<"\n"; }
void FileHandler::saveBills(const Storage<Bill>& s){ofstream f("bills.txt"); const Bill* a=s.getAll(); for(int i=0;i<s.size();i++) f<<a[i].getBillID()<<","<<a[i].getPatientID()<<","<<a[i].getAppointmentID()<<","<<a[i].getAmount()<<","<<a[i].getStatus()<<","<<a[i].getDate()<<"\n"; }
void FileHandler::savePrescriptions(const Storage<Prescription>& s){ofstream f("prescriptions.txt"); const Prescription* a=s.getAll(); for(int i=0;i<s.size();i++) f<<a[i].getPrescriptionID()<<","<<a[i].getAppointmentID()<<","<<a[i].getPatientID()<<","<<a[i].getDoctorID()<<","<<a[i].getDate()<<","<<a[i].getMedicines()<<","<<a[i].getNotes()<<"\n"; }
int FileHandler::nextPatientID(const Storage<Patient>& s){int m=0; for(int i=0;i<s.size();i++) if(s.getAt(i)->getID()>m) m=s.getAt(i)->getID(); return m+1;} int FileHandler::nextDoctorID(const Storage<Doctor>& s){int m=0; for(int i=0;i<s.size();i++) if(s.getAt(i)->getID()>m) m=s.getAt(i)->getID(); return m+1;} int FileHandler::nextAppointmentID(const Storage<Appointment>& s){int m=0; for(int i=0;i<s.size();i++) if(s.getAt(i)->getAppointmentID()>m) m=s.getAt(i)->getAppointmentID(); return m+1;} int FileHandler::nextBillID(const Storage<Bill>& s){int m=0; for(int i=0;i<s.size();i++) if(s.getAt(i)->getBillID()>m) m=s.getAt(i)->getBillID(); return m+1;} int FileHandler::nextPrescriptionID(const Storage<Prescription>& s){int m=0; for(int i=0;i<s.size();i++) if(s.getAt(i)->getPrescriptionID()>m) m=s.getAt(i)->getPrescriptionID(); return m+1;}
void FileHandler::appendSecurityLog(const char* role,int enteredID,const char* result){ofstream f("security_log.txt",ios::app); time_t now=time(0); tm* c=localtime(&now); char stamp[30]; strftime(stamp,30,"%d-%m-%Y %H:%M:%S",c); f<<stamp<<","<<role<<","<<enteredID<<","<<result<<"\n"; }
void FileHandler::appendDischargedPatientRecord(const Patient& p){ofstream f("discharged.txt",ios::app); f<<p.getID()<<","<<p.getName()<<","<<p.getAge()<<","<<p.getGender()<<","<<p.getContact()<<","<<p.getPassword()<<","<<p.getBalance()<<"\n"; }
void FileHandler::copyPatientArchiveData(int patientID,const Storage<Appointment>& apps,const Storage<Prescription>& pres,const Storage<Bill>& bills){ofstream f("discharged.txt",ios::app); for(int i=0;i<apps.size();i++) if(apps.getAt(i)->getPatientID()==patientID) f<<apps.getAt(i)->getAppointmentID()<<","<<apps.getAt(i)->getPatientID()<<","<<apps.getAt(i)->getDoctorID()<<","<<apps.getAt(i)->getDate()<<","<<apps.getAt(i)->getTimeSlot()<<","<<apps.getAt(i)->getStatus()<<"\n"; for(int i=0;i<pres.size();i++) if(pres.getAt(i)->getPatientID()==patientID) f<<pres.getAt(i)->getPrescriptionID()<<","<<pres.getAt(i)->getAppointmentID()<<","<<pres.getAt(i)->getPatientID()<<","<<pres.getAt(i)->getDoctorID()<<","<<pres.getAt(i)->getDate()<<","<<pres.getAt(i)->getMedicines()<<","<<pres.getAt(i)->getNotes()<<"\n"; for(int i=0;i<bills.size();i++) if(bills.getAt(i)->getPatientID()==patientID) f<<bills.getAt(i)->getBillID()<<","<<bills.getAt(i)->getPatientID()<<","<<bills.getAt(i)->getAppointmentID()<<","<<bills.getAt(i)->getAmount()<<","<<bills.getAt(i)->getStatus()<<","<<bills.getAt(i)->getDate()<<"\n"; }
