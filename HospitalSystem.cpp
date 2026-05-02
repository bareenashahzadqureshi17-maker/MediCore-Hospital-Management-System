#define _CRT_SECURE_NO_WARNINGS
#include "HospitalSystem.h"
#include "FileHandler.h"
#include "Validator.h"
#include "Utils.h"
#include "HospitalException.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <fstream>
using namespace std;

HospitalSystem::HospitalSystem() {
    currentPatientIndex = currentDoctorIndex = currentAdminIndex = -1;
}
void HospitalSystem::loadAllData() 
{
    ofstream f1("patients.txt", ios::app); f1.close();
    ofstream f2("doctors.txt", ios::app); f2.close();
    ofstream f3("admin.txt", ios::app); f3.close();
    ofstream f4("appointments.txt", ios::app); f4.close();
    ofstream f5("bills.txt", ios::app); f5.close();
    ofstream f6("prescriptions.txt", ios::app); f6.close();
    ofstream f7("security_log.txt", ios::app); f7.close();
    ofstream f8("discharged.txt", ios::app); f8.close();
    FileHandler::ensureFilesExist();
    FileHandler::loadPatients(patients);
    FileHandler::loadDoctors(doctors);
    FileHandler::loadAdmins(admins);
    FileHandler::loadAppointments(appointments);
    FileHandler::loadBills(bills);
    FileHandler::loadPrescriptions(prescriptions);
}
void HospitalSystem::saveAllData() {
    FileHandler::savePatients(patients);
    FileHandler::saveDoctors(doctors);
    FileHandler::saveAppointments(appointments);
    FileHandler::saveBills(bills);
    FileHandler::savePrescriptions(prescriptions);
}
int HospitalSystem::findPatientIndexByID(int id) const { for(int i=0;i<patients.size();i++) if(patients.getAt(i)->getID()==id) return i; return -1; }
int HospitalSystem::findDoctorIndexByID(int id) const { for(int i=0;i<doctors.size();i++) if(doctors.getAt(i)->getID()==id) return i; return -1; }
int HospitalSystem::findAdminIndexByID(int id) const { for(int i=0;i<admins.size();i++) if(admins.getAt(i)->getID()==id) return i; return -1; }
int HospitalSystem::findAppointmentIndexByID(int id) const { for(int i=0;i<appointments.size();i++) if(appointments.getAt(i)->getAppointmentID()==id) return i; return -1; }
int HospitalSystem::findBillIndexByID(int id) const { for(int i=0;i<bills.size();i++) if(bills.getAt(i)->getBillID()==id) return i; return -1; }
int HospitalSystem::findPrescriptionIndexByAppointmentID(int id) const { for(int i=0;i<prescriptions.size();i++) if(prescriptions.getAt(i)->getAppointmentID()==id) return i; return -1; }

bool HospitalSystem::patientLogin() {
    int id, fail = 0; char pass[100];
    while (fail < 3) {
        cout << "Enter Patient ID: "; cin >> id;
        cout << "Enter Password: "; cin >> pass;
        int x = findPatientIndexByID(id);
        if (x != -1 && Utils::eq(patients.getAt(x)->getPassword(), pass)) {
            currentPatientIndex = x; return true;
        }
        fail++;
        FileHandler::appendSecurityLog("Patient", id, "FAILED");
        cout << "Invalid credentials.\n";
    }
    cout << "Account locked. Contact admin.\n";
    return false;
}
bool HospitalSystem::doctorLogin() {
    int id, fail = 0; char pass[100];
    while (fail < 3) {
        cout << "Enter Doctor ID: "; cin >> id;
        cout << "Enter Password: "; cin >> pass;
        int x = findDoctorIndexByID(id);
        if (x != -1 && Utils::eq(doctors.getAt(x)->getPassword(), pass)) {
            currentDoctorIndex = x; return true;
        }
        fail++;
        FileHandler::appendSecurityLog("Doctor", id, "FAILED");
        cout << "Invalid credentials.\n";
    }
    cout << "Account locked. Contact admin.\n";
    return false;
}
bool HospitalSystem::adminLogin() {
    int id, fail = 0; char pass[100];
    while (fail < 3) {
        cout << "Enter Admin ID: "; cin >> id;
        cout << "Enter Password: "; cin >> pass;
        int x = findAdminIndexByID(id);
        if (x != -1 && Utils::eq(admins.getAt(x)->getPassword(), pass)) {
            currentAdminIndex = x; return true;
        }
        fail++;
        FileHandler::appendSecurityLog("Admin", id, "FAILED");
        cout << "Invalid credentials.\n";
    }
    cout << "Account locked. Contact admin.\n";
    return false;
}
void HospitalSystem::showStartupMenu() {
    cout << "\nWelcome to MediCore Hospital Management System\n";
    cout << "===============================================\n";
    cout << "1. Patient\n2. Doctor\n3. Admin\n4. Exit\n";
}
void HospitalSystem::runConsole() {
    loadAllData();
    int c = 0;
    do {
        showStartupMenu();
        cout << "Enter choice: ";
        cin >> c;
        if (c == 1) { if (patientLogin()) patientMenu(); }
        else if (c == 2) { if (doctorLogin()) doctorMenu(); }
        else if (c == 3) { if (adminLogin()) adminMenu(); }
        else if (c == 4) cout << "Goodbye.\n";
        else cout << "Invalid choice.\n";
    } while (c != 4);
}
void HospitalSystem::patientMenu() {
    int c = 0;
    do {
        Patient* p = patients.getAt(currentPatientIndex);
        cout << "\nWelcome, " << p->getName() << "\nBalance: PKR " << p->getBalance() << "\n";
        cout << "========================\n";
        cout << "1. Book Appointment\n2. Cancel Appointment\n3. View My Appointments\n4. View My Medical Records\n5. View My Bills\n6. Pay Bill\n7. Top Up Balance\n8. Logout\n";
        cout << "Enter choice: "; cin >> c;
        if (c == 1) bookAppointment();
        else if (c == 2) cancelAppointment();
        else if (c == 3) viewMyAppointments();
        else if (c == 4) viewMyMedicalRecords();
        else if (c == 5) viewMyBills();
        else if (c == 6) payBill();
        else if (c == 7) topUpBalance();
        else if (c != 8) cout << "Invalid choice.\n";
    } while (c != 8);
    currentPatientIndex = -1;
}
void HospitalSystem::doctorMenu() {
    int c = 0;
    do {
        Doctor* d = doctors.getAt(currentDoctorIndex);
        cout << "\nWelcome, Dr. " << d->getName() << " | Specialization: " << d->getSpecialization() << "\n";
        cout << "===============================================\n";
        cout << "1. View Today's Appointments\n2. Mark Appointment Complete\n3. Mark Appointment No-Show\n4. Write Prescription\n5. View Patient Medical History\n6. Logout\n";
        cout << "Enter choice: "; cin >> c;
        if (c == 1) viewTodayAppointments();
        else if (c == 2) markAppointmentComplete();
        else if (c == 3) markAppointmentNoShow();
        else if (c == 4) writePrescription();
        else if (c == 5) viewPatientMedicalHistory();
        else if (c != 6) cout << "Invalid choice.\n";
    } while (c != 6);
    currentDoctorIndex = -1;
}
void HospitalSystem::adminMenu() {
    int c = 0;
    do {
        cout << "\nAdmin Panel - MediCore\n======================\n";
        cout << "1. Add Doctor\n2. Remove Doctor\n3. View All Patients\n4. View All Doctors\n5. View All Appointments\n6. View Unpaid Bills\n7. Discharge Patient\n8. View Security Log\n9. Generate Daily Report\n10. Logout\n";
        cout << "Enter choice: "; cin >> c;
        if (c == 1) addDoctor();
        else if (c == 2) removeDoctor();
        else if (c == 3) viewAllPatients();
        else if (c == 4) viewAllDoctors();
        else if (c == 5) viewAllAppointments();
        else if (c == 6) viewUnpaidBills();
        else if (c == 7) dischargePatient();
        else if (c == 8) viewSecurityLog();
        else if (c == 9) generateDailyReport();
        else if (c != 10) cout << "Invalid choice.\n";
    } while (c != 10);
    currentAdminIndex = -1;
}
void HospitalSystem::bookAppointment() {
    char spec[100];
    cout << "Enter specialization to search: ";
    cin.ignore();
    cin.getline(spec, 100);
    int list[100], m = 0;
    for (int i = 0; i < doctors.size(); i++) if (Utils::eqi(doctors.getAt(i)->getSpecialization(), spec)) list[m++] = i;
    if (!m) { cout << "No doctors available for that specialization.\n"; return; }
    for (int i = 0; i < m; i++) {
        Doctor* d = doctors.getAt(list[i]);
        cout << d->getID() << " | " << d->getName() << " | Fee: PKR " << d->getFee() << "\n";
    }
    int doctorID; cout << "Enter Doctor ID: "; cin >> doctorID;
    int dx = findDoctorIndexByID(doctorID);
    if (dx == -1) { cout << "Doctor not found.\n"; return; }
    char date[20]; int tries = 0;
    do {
        cout << "Enter date (DD-MM-YYYY): "; cin >> date;
        if (Validator::validateDate(date)) break;
        cout << "Invalid date. Use format DD-MM-YYYY.\n";
        tries++;
    } while (tries < 3);
    if (tries == 3 && !Validator::validateDate(date)) return;
    const char valid[8][6] = {"09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00"};
    cout << "Available slots:\n";
    for (int i = 0; i < 8; i++) {
        bool open = true;
        for (int j = 0; j < appointments.size(); j++) {
            Appointment temp(0, 0, doctorID, date, valid[i], "pending");
            if (*appointments.getAt(j) == temp) open = false;
        }
        if (open) cout << valid[i] << "\n";
    }
    char slot[10]; cout << "Enter time slot: "; cin >> slot;
    try {
        if (!Validator::validateTimeSlot(slot)) throw InvalidInputException("Invalid time slot.");
        Appointment temp(0, 0, doctorID, date, slot, "pending");
        for (int j = 0; j < appointments.size(); j++) if (*appointments.getAt(j) == temp) throw SlotUnavailableException("Selected slot is already unavailable.");
        Patient* p = patients.getAt(currentPatientIndex);
        Doctor* d = doctors.getAt(dx);
        if (p->getBalance() < d->getFee()) throw InsufficientFundsException("Insufficient balance to book appointment.");
        (*p) -= d->getFee();
        int aid = FileHandler::nextAppointmentID(appointments);
        appointments.add(Appointment(aid, p->getID(), doctorID, date, slot, "pending"));
        bills.add(Bill(FileHandler::nextBillID(bills), p->getID(), aid, d->getFee(), "unpaid", date));
        saveAllData();
        cout << "Appointment booked successfully. Appointment ID: " << aid << ".\n";
    } catch (HospitalException& e) {
        cout << e.what() << "\n";
    }
}
void HospitalSystem::cancelAppointment() {
    int pid = patients.getAt(currentPatientIndex)->getID(), found = 0;
    for (int i = 0; i < appointments.size(); i++) {
        Appointment* a = appointments.getAt(i);
        if (a->getPatientID() == pid && Utils::eq(a->getStatus(), "pending")) {
            Doctor* d = doctors.getAt(findDoctorIndexByID(a->getDoctorID()));
            cout << a->getAppointmentID() << " | " << d->getName() << " | " << a->getDate() << " | " << a->getTimeSlot() << "\n";
            found++;
        }
    }
    if (!found) { cout << "You have no pending appointments.\n"; return; }
    int aid; cout << "Enter Appointment ID to cancel: "; cin >> aid;
    int ix = findAppointmentIndexByID(aid);
    if (ix == -1 || appointments.getAt(ix)->getPatientID() != pid || !Utils::eq(appointments.getAt(ix)->getStatus(), "pending")) { cout << "Invalid appointment ID.\n"; return; }
    appointments.getAt(ix)->setStatus("cancelled");
    Doctor* d = doctors.getAt(findDoctorIndexByID(appointments.getAt(ix)->getDoctorID()));
    (*patients.getAt(currentPatientIndex)) += d->getFee();
    for (int i = 0; i < bills.size(); i++) if (bills.getAt(i)->getAppointmentID() == aid) bills.getAt(i)->setStatus("cancelled");
    saveAllData();
    cout << "Appointment cancelled. PKR " << d->getFee() << " refunded to your balance.\n";
}
void HospitalSystem::viewMyAppointments() {
    int pid = patients.getAt(currentPatientIndex)->getID();
    for (int i = 0; i < appointments.size() - 1; i++) for (int j = 0; j < appointments.size() - i - 1; j++)
        if (Utils::cmpDate(appointments.getAt(j)->getDate(), appointments.getAt(j + 1)->getDate()) > 0) {
            Appointment t = *appointments.getAt(j); *appointments.getAt(j) = *appointments.getAt(j + 1); *appointments.getAt(j + 1) = t;
        }
    int found = 0;
    for (int i = 0; i < appointments.size(); i++) if (appointments.getAt(i)->getPatientID() == pid) {
        Doctor* d = doctors.getAt(findDoctorIndexByID(appointments.getAt(i)->getDoctorID()));
        cout << appointments.getAt(i)->getAppointmentID() << " | " << d->getName() << " | " << d->getSpecialization() << " | "
             << appointments.getAt(i)->getDate() << " | " << appointments.getAt(i)->getTimeSlot() << " | " << appointments.getAt(i)->getStatus() << "\n";
        found++;
    }
    if (!found) cout << "No appointments found.\n";
}
void HospitalSystem::viewMyMedicalRecords() {
    int pid = patients.getAt(currentPatientIndex)->getID();
    for (int i = 0; i < prescriptions.size() - 1; i++) for (int j = 0; j < prescriptions.size() - i - 1; j++)
        if (Utils::cmpDate(prescriptions.getAt(j)->getDate(), prescriptions.getAt(j + 1)->getDate()) < 0) {
            Prescription t = *prescriptions.getAt(j); *prescriptions.getAt(j) = *prescriptions.getAt(j + 1); *prescriptions.getAt(j + 1) = t;
        }
    int found = 0;
    for (int i = 0; i < prescriptions.size(); i++) if (prescriptions.getAt(i)->getPatientID() == pid) {
        Doctor* d = doctors.getAt(findDoctorIndexByID(prescriptions.getAt(i)->getDoctorID()));
        cout << prescriptions.getAt(i)->getDate() << " | " << d->getName() << " | " << prescriptions.getAt(i)->getMedicines() << " | " << prescriptions.getAt(i)->getNotes() << "\n";
        found++;
    }
    if (!found) cout << "No medical records found.\n";
}
void HospitalSystem::viewMyBills() {
    int pid = patients.getAt(currentPatientIndex)->getID(); float total = 0; int found = 0;
    for (int i = 0; i < bills.size(); i++) if (bills.getAt(i)->getPatientID() == pid) {
        cout << bills.getAt(i)->getBillID() << " | " << bills.getAt(i)->getAppointmentID() << " | PKR " << bills.getAt(i)->getAmount() << " | " << bills.getAt(i)->getStatus() << " | " << bills.getAt(i)->getDate() << "\n";
        if (Utils::eq(bills.getAt(i)->getStatus(), "unpaid")) total += bills.getAt(i)->getAmount();
        found++;
    }
    if (!found) cout << "No bills found.\n";
    else cout << "Total outstanding unpaid amount: PKR " << total << "\n";
}
void HospitalSystem::payBill() {
    int pid = patients.getAt(currentPatientIndex)->getID(), found = 0;
    for (int i = 0; i < bills.size(); i++) if (bills.getAt(i)->getPatientID() == pid && Utils::eq(bills.getAt(i)->getStatus(), "unpaid")) {
        cout << bills.getAt(i)->getBillID() << " | Appointment ID: " << bills.getAt(i)->getAppointmentID() << " | PKR " << bills.getAt(i)->getAmount() << " | " << bills.getAt(i)->getDate() << "\n";
        found++;
    }
    if (!found) { cout << "No unpaid bills.\n"; return; }
    int bid; cout << "Enter Bill ID to pay: "; cin >> bid;
    int bx = findBillIndexByID(bid);
    if (bx == -1 || bills.getAt(bx)->getPatientID() != pid || !Utils::eq(bills.getAt(bx)->getStatus(), "unpaid")) { cout << "Invalid bill ID.\n"; return; }
    try {
        if (patients.getAt(currentPatientIndex)->getBalance() < bills.getAt(bx)->getAmount()) throw InsufficientFundsException("Insufficient balance.");
        (*patients.getAt(currentPatientIndex)) -= bills.getAt(bx)->getAmount();
        bills.getAt(bx)->setStatus("paid");
        saveAllData();
        cout << "Bill paid successfully. Remaining balance: PKR " << patients.getAt(currentPatientIndex)->getBalance() << ".\n";
    } catch (HospitalException& e) { cout << e.what() << "\n"; }
}
void HospitalSystem::topUpBalance() {
    float amount; int x = 0;
    while (x < 3) {
        cout << "Enter amount to add (PKR): "; cin >> amount;
        try {
            if (!Validator::validatePositiveFloat(amount)) throw InvalidInputException("Amount must be greater than 0.");
            (*patients.getAt(currentPatientIndex)) += amount;
            saveAllData();
            cout << "Balance updated. New balance: PKR " << patients.getAt(currentPatientIndex)->getBalance() << ".\n";
            return;
        } catch (HospitalException& e) { cout << e.what() << "\n"; }
        x++;
    }
}
void HospitalSystem::viewTodayAppointments() {
    time_t now = time(0); tm* c = localtime(&now); char today[11]; strftime(today, 11, "%d-%m-%Y", c);
    int did = doctors.getAt(currentDoctorIndex)->getID();
    for (int i = 0; i < appointments.size() - 1; i++) for (int j = 0; j < appointments.size() - i - 1; j++)
        if (Utils::cmpTime(appointments.getAt(j)->getTimeSlot(), appointments.getAt(j + 1)->getTimeSlot()) > 0) {
            Appointment t = *appointments.getAt(j); *appointments.getAt(j) = *appointments.getAt(j + 1); *appointments.getAt(j + 1) = t;
        }
    int found = 0;
    for (int i = 0; i < appointments.size(); i++) if (appointments.getAt(i)->getDoctorID() == did && Utils::eq(appointments.getAt(i)->getDate(), today)) {
        Patient* p = patients.getAt(findPatientIndexByID(appointments.getAt(i)->getPatientID()));
        cout << appointments.getAt(i)->getAppointmentID() << " | " << p->getName() << " | " << appointments.getAt(i)->getTimeSlot() << " | " << appointments.getAt(i)->getStatus() << "\n";
        found++;
    }
    if (!found) cout << "No appointments scheduled for today.\n";
}
void HospitalSystem::markAppointmentComplete() {
    time_t now = time(0); tm* c = localtime(&now); char today[11]; strftime(today, 11, "%d-%m-%Y", c);
    int did = doctors.getAt(currentDoctorIndex)->getID();
    for (int i = 0; i < appointments.size(); i++) if (appointments.getAt(i)->getDoctorID() == did && Utils::eq(appointments.getAt(i)->getDate(), today) && Utils::eq(appointments.getAt(i)->getStatus(), "pending"))
        cout << appointments.getAt(i)->getAppointmentID() << " | " << appointments.getAt(i)->getTimeSlot() << "\n";
    int aid; cout << "Enter Appointment ID: "; cin >> aid;
    int ix = findAppointmentIndexByID(aid);
    if (ix == -1 || appointments.getAt(ix)->getDoctorID() != did || !Utils::eq(appointments.getAt(ix)->getDate(), today) || !Utils::eq(appointments.getAt(ix)->getStatus(), "pending")) { cout << "Invalid appointment ID.\n"; return; }
    appointments.getAt(ix)->setStatus("completed");
    saveAllData();
    cout << "Appointment marked as completed.\n";
}
void HospitalSystem::markAppointmentNoShow() {
    time_t now = time(0); tm* c = localtime(&now); char today[11]; strftime(today, 11, "%d-%m-%Y", c);
    int did = doctors.getAt(currentDoctorIndex)->getID();
    for (int i = 0; i < appointments.size(); i++) if (appointments.getAt(i)->getDoctorID() == did && Utils::eq(appointments.getAt(i)->getDate(), today) && Utils::eq(appointments.getAt(i)->getStatus(), "pending"))
        cout << appointments.getAt(i)->getAppointmentID() << " | " << appointments.getAt(i)->getTimeSlot() << "\n";
    int aid; cout << "Enter Appointment ID: "; cin >> aid;
    int ix = findAppointmentIndexByID(aid);
    if (ix == -1 || appointments.getAt(ix)->getDoctorID() != did || !Utils::eq(appointments.getAt(ix)->getDate(), today) || !Utils::eq(appointments.getAt(ix)->getStatus(), "pending")) { cout << "Invalid appointment ID.\n"; return; }
    appointments.getAt(ix)->setStatus("no-show");
    for (int i = 0; i < bills.size(); i++) if (bills.getAt(i)->getAppointmentID() == aid) bills.getAt(i)->setStatus("cancelled");
    saveAllData();
    cout << "Appointment marked as no-show.\n";
}
void HospitalSystem::writePrescription() {
    int aid; cout << "Enter Appointment ID: "; cin >> aid;
    int ix = findAppointmentIndexByID(aid);
    if (ix == -1 || appointments.getAt(ix)->getDoctorID() != doctors.getAt(currentDoctorIndex)->getID() || !Utils::eq(appointments.getAt(ix)->getStatus(), "completed")) { cout << "Invalid appointment ID.\n"; return; }
    if (findPrescriptionIndexByAppointmentID(aid) != -1) { cout << "Prescription already written for this appointment.\n"; return; }
    char meds[500], notes[300];
    cin.ignore();
    cout << "Enter medicines: "; cin.getline(meds, 500);
    cout << "Enter notes: "; cin.getline(notes, 300);
    prescriptions.add(Prescription(FileHandler::nextPrescriptionID(prescriptions), aid, appointments.getAt(ix)->getPatientID(), doctors.getAt(currentDoctorIndex)->getID(), appointments.getAt(ix)->getDate(), meds, notes));
    saveAllData();
    cout << "Prescription saved.\n";
}
void HospitalSystem::viewPatientMedicalHistory() {
    int pid; cout << "Enter Patient ID: "; cin >> pid;
    bool ok = false; int did = doctors.getAt(currentDoctorIndex)->getID();
    for (int i = 0; i < appointments.size(); i++) if (appointments.getAt(i)->getPatientID() == pid && appointments.getAt(i)->getDoctorID() == did && Utils::eq(appointments.getAt(i)->getStatus(), "completed")) ok = true;
    if (!ok) { cout << "Access denied. You can only view records of your own patients.\n"; return; }
    for (int i = 0; i < prescriptions.size(); i++) if (prescriptions.getAt(i)->getPatientID() == pid && prescriptions.getAt(i)->getDoctorID() == did)
        cout << prescriptions.getAt(i)->getDate() << " | " << prescriptions.getAt(i)->getMedicines() << " | " << prescriptions.getAt(i)->getNotes() << "\n";
}
void HospitalSystem::addDoctor() {
    char n[60], s[60], c[20], p[60]; float fee;
    cin.ignore();
    cout << "Enter name: "; cin.getline(n, 60);
    cout << "Enter specialization: "; cin.getline(s, 60);
    cout << "Enter contact: "; cin.getline(c, 20);
    cout << "Enter password: "; cin.getline(p, 60);
    cout << "Enter fee: "; cin >> fee;
    if (!Validator::validateContact(c) || !Validator::validatePassword(p) || !Validator::validatePositiveFloat(fee)) { cout << "Invalid input.\n"; return; }
    int id = FileHandler::nextDoctorID(doctors);
    doctors.add(Doctor(id, n, s, c, p, fee));
    saveAllData();
    cout << "Doctor added successfully. ID: " << id << ".\n";
}
void HospitalSystem::removeDoctor() {
    for (int i = 0; i < doctors.size(); i++) cout << doctors.getAt(i)->getID() << " | " << doctors.getAt(i)->getName() << " | " << doctors.getAt(i)->getSpecialization() << " | " << doctors.getAt(i)->getFee() << "\n";
    int did; cout << "Enter Doctor ID to remove: "; cin >> did;
    for (int i = 0; i < appointments.size(); i++) if (appointments.getAt(i)->getDoctorID() == did && Utils::eq(appointments.getAt(i)->getStatus(), "pending")) { cout << "Cannot remove doctor with pending appointments. Cancel or reassign them first.\n"; return; }
    int ix = findDoctorIndexByID(did);
    if (ix == -1) { cout << "Doctor not found.\n"; return; }
    doctors.removeByIndex(ix);
    saveAllData();
    cout << "Doctor removed.\n";
}
void HospitalSystem::viewAllPatients() {
    for (int i = 0; i < patients.size(); i++) {
        int unpaid = 0;
        for (int j = 0; j < bills.size(); j++) if (bills.getAt(j)->getPatientID() == patients.getAt(i)->getID() && Utils::eq(bills.getAt(j)->getStatus(), "unpaid")) unpaid++;
        cout << patients.getAt(i)->getID() << " | " << patients.getAt(i)->getName() << " | " << patients.getAt(i)->getAge() << " | " << patients.getAt(i)->getGender()
             << " | " << patients.getAt(i)->getContact() << " | " << patients.getAt(i)->getBalance() << " | " << unpaid << "\n";
    }
}
void HospitalSystem::viewAllDoctors() {
    for (int i = 0; i < doctors.size(); i++) cout << doctors.getAt(i)->getID() << " | " << doctors.getAt(i)->getName() << " | " << doctors.getAt(i)->getSpecialization() << " | " << doctors.getAt(i)->getContact() << " | " << doctors.getAt(i)->getFee() << "\n";
}
void HospitalSystem::viewAllAppointments() {
    for (int i = 0; i < appointments.size() - 1; i++) for (int j = 0; j < appointments.size() - i - 1; j++)
        if (Utils::cmpDate(appointments.getAt(j)->getDate(), appointments.getAt(j + 1)->getDate()) < 0) {
            Appointment t = *appointments.getAt(j); *appointments.getAt(j) = *appointments.getAt(j + 1); *appointments.getAt(j + 1) = t;
        }
    for (int i = 0; i < appointments.size(); i++) {
        Patient* p = patients.getAt(findPatientIndexByID(appointments.getAt(i)->getPatientID()));
        Doctor* d = doctors.getAt(findDoctorIndexByID(appointments.getAt(i)->getDoctorID()));
        cout << appointments.getAt(i)->getAppointmentID() << " | " << p->getName() << " | " << d->getName() << " | " << appointments.getAt(i)->getDate() << " | " << appointments.getAt(i)->getTimeSlot() << " | " << appointments.getAt(i)->getStatus() << "\n";
    }
}
void HospitalSystem::viewUnpaidBills() {
    time_t now = time(0); int found = 0;
    for (int i = 0; i < bills.size(); i++) if (Utils::eq(bills.getAt(i)->getStatus(), "unpaid")) {
        Patient* p = patients.getAt(findPatientIndexByID(bills.getAt(i)->getPatientID()));
        cout << bills.getAt(i)->getBillID() << " | " << p->getName() << " | PKR " << bills.getAt(i)->getAmount() << " | " << bills.getAt(i)->getDate();
        tm bt = {};
        const char* d = bills.getAt(i)->getDate();
        bt.tm_mday = (d[0]-'0')*10 + d[1]-'0';
        bt.tm_mon = ((d[3]-'0')*10 + d[4]-'0') - 1;
        bt.tm_year = ((d[6]-'0')*1000 + (d[7]-'0')*100 + (d[8]-'0')*10 + d[9]-'0') - 1900;
        if (difftime(now, mktime(&bt)) / (60*60*24) > 7) cout << " [OVERDUE]";
        cout << "\n";
        found++;
    }
    if (!found) cout << "No unpaid bills.\n";
}
void HospitalSystem::dischargePatient() {
    int pid; cout << "Enter Patient ID: "; cin >> pid;
    int px = findPatientIndexByID(pid);
    if (px == -1) { cout << "Patient not found.\n"; return; }
    for (int i = 0; i < bills.size(); i++) if (bills.getAt(i)->getPatientID() == pid && Utils::eq(bills.getAt(i)->getStatus(), "unpaid")) { cout << "Cannot discharge patient with unpaid bills.\n"; return; }
    for (int i = 0; i < appointments.size(); i++) if (appointments.getAt(i)->getPatientID() == pid && Utils::eq(appointments.getAt(i)->getStatus(), "pending")) { cout << "Cannot discharge patient with pending appointments.\n"; return; }
    FileHandler::appendDischargedPatientRecord(*patients.getAt(px));
    FileHandler::copyPatientArchiveData(pid, appointments, prescriptions, bills);
    for (int i = appointments.size() - 1; i >= 0; i--) if (appointments.getAt(i)->getPatientID() == pid) appointments.removeByIndex(i);
    for (int i = prescriptions.size() - 1; i >= 0; i--) if (prescriptions.getAt(i)->getPatientID() == pid) prescriptions.removeByIndex(i);
    for (int i = bills.size() - 1; i >= 0; i--) if (bills.getAt(i)->getPatientID() == pid) bills.removeByIndex(i);
    patients.removeByIndex(px);
    saveAllData();
    cout << "Patient discharged and archived successfully.\n";
}
void HospitalSystem::viewSecurityLog() {
    ifstream f("security_log.txt"); char line[500]; int found = 0;
    while (f.getline(line, 500)) { if (Utils::len(line) > 0) { cout << line << "\n"; found++; } }
    if (!found) cout << "No security events logged.\n";
}
void HospitalSystem::generateDailyReport() {
    time_t now = time(0); tm* c = localtime(&now); char today[11]; strftime(today, 11, "%d-%m-%Y", c);
    int total=0, pending=0, completed=0, noshow=0, cancelled=0; float revenue=0;
    for (int i = 0; i < appointments.size(); i++) if (Utils::eq(appointments.getAt(i)->getDate(), today)) {
        total++;
        if (Utils::eq(appointments.getAt(i)->getStatus(), "pending")) pending++;
        else if (Utils::eq(appointments.getAt(i)->getStatus(), "completed")) completed++;
        else if (Utils::eq(appointments.getAt(i)->getStatus(), "no-show")) noshow++;
        else if (Utils::eq(appointments.getAt(i)->getStatus(), "cancelled")) cancelled++;
    }
    for (int i = 0; i < bills.size(); i++) if (Utils::eq(bills.getAt(i)->getDate(), today) && Utils::eq(bills.getAt(i)->getStatus(), "paid")) revenue += bills.getAt(i)->getAmount();
    cout << "Total appointments today: " << total << " (Pending: " << pending << " Completed: " << completed << " No-show: " << noshow << " Cancelled: " << cancelled << ")\n";
    cout << "Revenue collected today (paid bills): PKR " << revenue << "\n";
    cout << "Patients with outstanding unpaid bills:\n";
    for (int i = 0; i < patients.size(); i++) {
        float owed = 0;
        for (int j = 0; j < bills.size(); j++) if (bills.getAt(j)->getPatientID() == patients.getAt(i)->getID() && Utils::eq(bills.getAt(j)->getStatus(), "unpaid")) owed += bills.getAt(j)->getAmount();
        if (owed > 0) cout << patients.getAt(i)->getName() << " | " << owed << "\n";
    }
    cout << "Doctor-wise summary for today:\n";
    for (int i = 0; i < doctors.size(); i++) {
        int cc=0, pp=0, nn=0;
        for (int j = 0; j < appointments.size(); j++) if (appointments.getAt(j)->getDoctorID() == doctors.getAt(i)->getID() && Utils::eq(appointments.getAt(j)->getDate(), today)) {
            if (Utils::eq(appointments.getAt(j)->getStatus(), "completed")) cc++;
            else if (Utils::eq(appointments.getAt(j)->getStatus(), "pending")) pp++;
            else if (Utils::eq(appointments.getAt(j)->getStatus(), "no-show")) nn++;
        }
        cout << doctors.getAt(i)->getName() << " | " << cc << " | " << pp << " | " << nn << "\n";
    }
}
// ================= GUI SUPPORT FUNCTIONS =================

bool HospitalSystem::patientLoginGUI(int id, const char* pass)
{
    int x = findPatientIndexByID(id);
    if (x != -1 && Utils::eq(patients.getAt(x)->getPassword(), pass))
    {
        currentPatientIndex = x;
        return true;
    }
    FileHandler::appendSecurityLog("Patient", id, "FAILED");
    return false;
}

bool HospitalSystem::doctorLoginGUI(int id, const char* pass)
{
    int x = findDoctorIndexByID(id);
    if (x != -1 && Utils::eq(doctors.getAt(x)->getPassword(), pass))
    {
        currentDoctorIndex = x;
        return true;
    }
    FileHandler::appendSecurityLog("Doctor", id, "FAILED");
    return false;
}

bool HospitalSystem::adminLoginGUI(int id, const char* pass)
{
    int x = findAdminIndexByID(id);
    if (x != -1 && Utils::eq(admins.getAt(x)->getPassword(), pass))
    {
        currentAdminIndex = x;
        return true;
    }
    FileHandler::appendSecurityLog("Admin", id, "FAILED");
    return false;
}

Patient* HospitalSystem::getCurrentPatient()
{
    if (currentPatientIndex == -1) return 0;
    return patients.getAt(currentPatientIndex);
}

Doctor* HospitalSystem::getCurrentDoctor()
{
    if (currentDoctorIndex == -1) return 0;
    return doctors.getAt(currentDoctorIndex);
}

int HospitalSystem::getPatientsCount() const
{
    return patients.size();
}

int HospitalSystem::getDoctorsCount() const
{
    return doctors.size();
}

int HospitalSystem::getAppointmentsCount() const
{
    return appointments.size();
}

int HospitalSystem::getBillsCount() const
{
    return bills.size();
}

int HospitalSystem::getPrescriptionsCount() const
{
    return prescriptions.size();
}

Patient* HospitalSystem::getPatientAt(int index)
{
    return patients.getAt(index);
}

Doctor* HospitalSystem::getDoctorAt(int index)
{
    return doctors.getAt(index);
}

Appointment* HospitalSystem::getAppointmentAt(int index)
{
    return appointments.getAt(index);
}

Bill* HospitalSystem::getBillAt(int index)
{
    return bills.getAt(index);
}

Prescription* HospitalSystem::getPrescriptionAt(int index)
{
    return prescriptions.getAt(index);
}

bool HospitalSystem::topUpBalanceGUI(float amount, char* msg)
{
    if (currentPatientIndex == -1)
    {
        Utils::copyArr(msg, "No patient logged in.", 200);
        return false;
    }

    if (amount <= 0)
    {
        Utils::copyArr(msg, "Amount must be greater than 0.", 200);
        return false;
    }

    (*patients.getAt(currentPatientIndex)) += amount;
    saveAllData();
    Utils::copyArr(msg, "Balance updated successfully.", 200);
    return true;
}

bool HospitalSystem::payBillGUI(int billID, char* msg)
{
    if (currentPatientIndex == -1)
    {
        Utils::copyArr(msg, "No patient logged in.", 200);
        return false;
    }

    int pid = patients.getAt(currentPatientIndex)->getID();
    int bx = findBillIndexByID(billID);

    if (bx == -1)
    {
        Utils::copyArr(msg, "Bill not found.", 200);
        return false;
    }

    if (bills.getAt(bx)->getPatientID() != pid)
    {
        Utils::copyArr(msg, "This bill does not belong to current patient.", 200);
        return false;
    }

    if (!Utils::eq(bills.getAt(bx)->getStatus(), "unpaid"))
    {
        Utils::copyArr(msg, "Bill is not unpaid.", 200);
        return false;
    }

    if (patients.getAt(currentPatientIndex)->getBalance() < bills.getAt(bx)->getAmount())
    {
        Utils::copyArr(msg, "Insufficient balance.", 200);
        return false;
    }

    (*patients.getAt(currentPatientIndex)) -= bills.getAt(bx)->getAmount();
    bills.getAt(bx)->setStatus("paid");
    saveAllData();
    Utils::copyArr(msg, "Bill paid successfully.", 200);
    return true;
}

bool HospitalSystem::cancelAppointmentGUI(int appointmentID, char* msg)
{
    if (currentPatientIndex == -1)
    {
        Utils::copyArr(msg, "No patient logged in.", 200);
        return false;
    }

    int pid = patients.getAt(currentPatientIndex)->getID();
    int ix = findAppointmentIndexByID(appointmentID);

    if (ix == -1)
    {
        Utils::copyArr(msg, "Appointment not found.", 200);
        return false;
    }

    if (appointments.getAt(ix)->getPatientID() != pid)
    {
        Utils::copyArr(msg, "Appointment does not belong to current patient.", 200);
        return false;
    }

    if (!Utils::eq(appointments.getAt(ix)->getStatus(), "pending"))
    {
        Utils::copyArr(msg, "Only pending appointments can be cancelled.", 200);
        return false;
    }

    appointments.getAt(ix)->setStatus("cancelled");

    int dx = findDoctorIndexByID(appointments.getAt(ix)->getDoctorID());
    if (dx != -1)
        (*patients.getAt(currentPatientIndex)) += doctors.getAt(dx)->getFee();

    for (int i = 0; i < bills.size(); i++)
    {
        if (bills.getAt(i)->getAppointmentID() == appointmentID)
            bills.getAt(i)->setStatus("cancelled");
    }

    saveAllData();
    Utils::copyArr(msg, "Appointment cancelled successfully.", 200);
    return true;
}

bool HospitalSystem::bookAppointmentGUI(const char* specialization, int doctorID, const char* date, const char* slot, char* msg)
{
    if (currentPatientIndex == -1)
    {
        Utils::copyArr(msg, "No patient logged in.", 200);
        return false;
    }

    int dx = findDoctorIndexByID(doctorID);
    if (dx == -1)
    {
        Utils::copyArr(msg, "Doctor not found.", 200);
        return false;
    }

    if (!Utils::eqi(doctors.getAt(dx)->getSpecialization(), specialization))
    {
        Utils::copyArr(msg, "Doctor specialization does not match.", 200);
        return false;
    }

    if (!Validator::validateDate(date))
    {
        Utils::copyArr(msg, "Invalid date.", 200);
        return false;
    }

    if (!Validator::validateTimeSlot(slot))
    {
        Utils::copyArr(msg, "Invalid time slot.", 200);
        return false;
    }

    Appointment temp(0, 0, doctorID, date, slot, "pending");
    for (int j = 0; j < appointments.size(); j++)
    {
        if (*appointments.getAt(j) == temp)
        {
            Utils::copyArr(msg, "Selected slot is unavailable.", 200);
            return false;
        }
    }

    Patient* p = patients.getAt(currentPatientIndex);
    Doctor* d = doctors.getAt(dx);

    if (p->getBalance() < d->getFee())
    {
        Utils::copyArr(msg, "Insufficient balance.", 200);
        return false;
    }

    (*p) -= d->getFee();

    int aid = FileHandler::nextAppointmentID(appointments);
    appointments.add(Appointment(aid, p->getID(), doctorID, date, slot, "pending"));
    bills.add(Bill(FileHandler::nextBillID(bills), p->getID(), aid, d->getFee(), "unpaid", date));

    saveAllData();
    Utils::copyArr(msg, "Appointment booked successfully.", 200);
    return true;
    }
    bool HospitalSystem::addPatientGUI(const char* name, int age, const char* gender, const char* contact, const char* password, float balance, char* msg)
{
    if (age <= 0 || balance < 0)
    {
        strcpy(msg, "Invalid patient data.");
        return false;
    }

    int id = FileHandler::nextPatientID(patients);
    patients.add(Patient(id, name, age, gender, contact, password, balance));
    saveAllData();

    sprintf(msg, "Patient added successfully. ID: %d", id);
    return true;
}

bool HospitalSystem::addDoctorGUI(const char* name, const char* specialization, const char* contact, const char* password, float fee, char* msg)
{
    if (fee <= 0)
    {
        strcpy(msg, "Invalid doctor fee.");
        return false;
    }

    int id = FileHandler::nextDoctorID(doctors);
    doctors.add(Doctor(id, name, specialization, contact, password, fee));
    saveAllData();

    sprintf(msg, "Doctor added successfully. ID: %d", id);
    return true;
}



bool HospitalSystem::addAdminGUI(const char* name, const char* password, char* msg)
{
    int id = admins.size() + 1;
    admins.add(Admin(id, name, password));

    ofstream file("admin.txt");
    for (int i = 0; i < admins.size(); i++)
    {
        Admin* a = admins.getAt(i);
        file << a->getID() << "," << a->getName() << "," << a->getPassword() << "\n";
    }
    file.close();

    strcpy(msg, "Admin added successfully.");
    return true;
}
