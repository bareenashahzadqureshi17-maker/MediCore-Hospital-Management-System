#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <iostream>
class Appointment{
    int appointmentID, patientID, doctorID; char date[11], timeSlot[6], status[20];
public:
    Appointment();
    Appointment(int,int,int,const char*,const char*,const char*);
    void setAppointmentID(int); 
    void setPatientID(int);
    void setDoctorID(int);
    void setDate(const char*);
    void setTimeSlot(const char*);
    void setStatus(const char*);
    int getAppointmentID() const; 
    int getPatientID() const; 
    
   int getDoctorID() const; 
   const char* getDate() const; 
   const char* getTimeSlot() const; 
   const char* getStatus() const;
    bool operator==(const Appointment&) const;
    friend std::ostream& operator<<(std::ostream&, const Appointment&);
};
#endif
