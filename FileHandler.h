#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "Storage.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
class FileHandler{
public:
    static void ensureFilesExist();
    static void loadPatients(Storage<Patient>&);
    static void loadDoctors(Storage<Doctor>&);
    static void loadAdmins(Storage<Admin>&); 
    static void loadAppointments(Storage<Appointment>&); 
    static void loadBills(Storage<Bill>&); 
    static void loadPrescriptions(Storage<Prescription>&);
    static void savePatients(const Storage<Patient>&); 
    static void saveDoctors(const Storage<Doctor>&);
    static void saveAppointments(const Storage<Appointment>&);
    static void saveBills(const Storage<Bill>&);
    static void savePrescriptions(const Storage<Prescription>&);
    static int nextPatientID(const Storage<Patient>&);
    static int nextDoctorID(const Storage<Doctor>&);
    static int nextAppointmentID(const Storage<Appointment>&); 
    static int nextBillID(const Storage<Bill>&);
    static int nextPrescriptionID(const Storage<Prescription>&);
    static void appendSecurityLog(const char*,int,const char*); 
    static void appendDischargedPatientRecord(const Patient&);
    static void copyPatientArchiveData(int,const Storage<Appointment>&,const Storage<Prescription>&,const Storage<Bill>&);
};
#endif
