#ifndef HOSPITALSYSTEM_H
#define HOSPITALSYSTEM_H
#include "Storage.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
class HospitalSystem{
    Storage<Patient> patients;
    Storage<Doctor> doctors;
    Storage<Admin> admins;
    Storage<Appointment> appointments;
    Storage<Bill> bills; 
    Storage<Prescription> prescriptions;
    int currentPatientIndex,currentDoctorIndex,currentAdminIndex;
public:
    HospitalSystem();
    void loadAllData(); 
    void saveAllData(); 
    void runConsole(); 
    void showStartupMenu();
    bool patientLogin();
    bool doctorLogin();
    bool adminLogin();
    void patientMenu();
    void doctorMenu(); 
    void adminMenu();
    int findPatientIndexByID(int) const; 
    int findDoctorIndexByID(int) const; 
    int findAdminIndexByID(int) const; 
    int findAppointmentIndexByID(int) const;
    int findBillIndexByID(int) const; 
    int findPrescriptionIndexByAppointmentID(int) const;
    void bookAppointment();
    void cancelAppointment(); 
    void viewMyAppointments();
    void viewMyMedicalRecords(); 
    void viewMyBills(); 
    void payBill(); 
    void topUpBalance();
    void viewTodayAppointments(); 
    void markAppointmentComplete();
    void markAppointmentNoShow(); 
    void writePrescription();
    void viewPatientMedicalHistory();
    void addDoctor(); 
    void removeDoctor(); 
    void viewAllPatients(); 
    void viewAllDoctors(); 
    void viewAllAppointments(); 
    void viewUnpaidBills();
    void dischargePatient();
    void viewSecurityLog();
    void generateDailyReport();
    bool addPatientGUI(const char* name, int age, const char* gender, const char* contact, const char* password, float balance, char* msg);
    bool addDoctorGUI(const char* name, const char* specialization, const char* contact, const char* password, float fee, char* msg);
    bool addAdminGUI(const char* name, const char* password, char* msg);
 
    bool patientLoginGUI(int id, const char* pass);
    bool doctorLoginGUI(int id, const char* pass);
    bool adminLoginGUI(int id, const char* pass);

    Patient* getCurrentPatient();
    Doctor* getCurrentDoctor();

    int getPatientsCount() const;
    int getDoctorsCount() const;
    int getAppointmentsCount() const;
    int getBillsCount() const;
    int getPrescriptionsCount() const;

    Patient* getPatientAt(int index);
    Doctor* getDoctorAt(int index);
    Appointment* getAppointmentAt(int index);
    Bill* getBillAt(int index);
    Prescription* getPrescriptionAt(int index);

    bool topUpBalanceGUI(float amount, char* msg);
    bool payBillGUI(int billID, char* msg);
    bool cancelAppointmentGUI(int appointmentID, char* msg);

    bool bookAppointmentGUI(const char* specialization, int doctorID, const char* date, const char* slot, char* msg);
};
#endif
