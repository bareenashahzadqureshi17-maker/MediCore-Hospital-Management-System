MediCore Hospital Management System
Overview
MediCore Hospital Management System is a desktop-based Hospital Management application developed in C++ using Object-Oriented Programming concepts and SFML graphics library. The system provides separate functionalities for Patients, Doctors, and Admins through an interactive graphical user interface.
The project manages:
•	Patient records
•	Doctor records
•	Admin records
•	Appointments
•	Prescriptions
•	Bills and payments
•	Balance top-up system
•	File handling and persistent storage
________________________________________
Technologies Used
•	C++
•	SFML (Simple and Fast Multimedia Library)
•	Object-Oriented Programming
•	File Handling
•	Visual Studio
________________________________________
OOP Concepts Implemented
Encapsulation
Data members are kept private and accessed through public getter and setter functions.
Abstraction
Each class is divided into separate header (.h) and implementation (.cpp) files.
Composition
HospitalSystem class contains and manages objects like:
•	Patients
•	Doctors
•	Appointments
•	Bills
•	Prescriptions
Aggregation
Classes interact with one another through IDs and references. Example:
•	Appointment stores Patient ID and Doctor ID.
Inheritance
Base and derived class relationships are implemented where required.
Polymorphism
Virtual functions and runtime behavior are used in different modules.
Dynamic Memory Allocation
Dynamic arrays and object storage are used throughout the system.
File Handling
All data is stored permanently in text files.
________________________________________
Main Features
Patient Features
•	Patient Login
•	View Appointments
•	View Bills
•	Pay Bills
•	Top Up Balance
•	View Prescriptions
Doctor Features
•	Doctor Login
•	View Appointments
•	Write Prescriptions
•	Mark Appointments Complete
Admin Features
•	Admin Login
•	Add New Patient
•	Add New Doctor
•	Add New Admin
•	Manage Hospital Records
________________________________________
GUI Features
The project uses SFML to provide:
•	Interactive graphical interface
•	Rounded buttons
•	Multiple screens
•	Input boxes
•	Dashboard system
•	Modern hospital-themed UI
•	Click handling
•	Text rendering
•	Screen switching
________________________________________
File Handling
The following text files are used for permanent data storage:
•	patients.txt
•	doctors.txt
•	admin.txt
•	appointments.txt
•	bills.txt
•	prescriptions.txt
•	security_log.txt
•	discharged.txt
All records remain saved even after closing the application.
________________________________________
Project Structure
Important Files
Core Classes
•	Patient.h / Patient.cpp
•	Doctor.h / Doctor.cpp
•	Admin.h / Admin.cpp
•	Appointment.h / Appointment.cpp
•	Bill.h / Bill.cpp
•	Prescription.h / Prescription.cpp
Management Classes
•	HospitalSystem.h / HospitalSystem.cpp
•	FileHandler.h / FileHandler.cpp
•	Storage.h
•	Validator.h / Validator.cpp
•	Utils.h / Utils.cpp
GUI Files
•	SFML_UI.h
•	SFML_UI.cpp
________________________________________
How to Run the Project
1.	Open the project in Visual Studio.
2.	Make sure SFML is properly linked.
3.	Place all text files inside:
x64/Debug/
4.	Build and Run the project.

Sample Login Credentials
Patient
•	ID: 1
•	Password: patient123
Doctor
•	ID: 1
•	Password: doc456
Admin
•	ID: 1
•	Password: admin123

Future Improvements
•	Database integration
•	Online appointment booking
•	Search and filter system
•	Better animations
•	Report generation
•	Emergency patient management
•	AI-based hospital assistance

Developed By
Developed as an Object-Oriented Programming Semester 2 Student . Project using C++ and SFML.



