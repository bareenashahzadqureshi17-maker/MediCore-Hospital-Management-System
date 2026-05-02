#ifndef BILL_H
#define BILL_H
class Bill{
    int billID, patientID, appointmentID; float amount; char status[20], date[11];
public:
    Bill(); Bill(int,int,int,float,const char*,const char*);
    int getBillID() const;
    
    int getPatientID() const;
    int getAppointmentID() const;
    float getAmount() const;
    const char* getStatus() const;
    const char* getDate() const;
    void setBillID(int);
    void setPatientID(int); 
    void setAppointmentID(int);
    void setAmount(float);
    void setStatus(const char*); 
    void setDate(const char*);
};
#endif
