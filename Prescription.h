#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H
class Prescription{
    int prescriptionID, appointmentID, patientID, doctorID; char date[11], medicines[500], notes[300];
public:
    Prescription(); 
    Prescription(int,int,int,int,const char*,const char*,const char*);
    int getPrescriptionID() const;
    int getAppointmentID() const; 
    int getPatientID() const;
    int getDoctorID() const; 
    const char* getDate() const;
    const char* getMedicines() const; 
    const char* getNotes() const;
    void setPrescriptionID(int); 
    void setAppointmentID(int); 
    void setPatientID(int); 
    void setDoctorID(int); 
    void setDate(const char*);
    void setMedicines(const char*);
    void setNotes(const char*);
};
#endif
