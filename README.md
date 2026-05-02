# MediCore Hospital Management System

This is a file-based Hospital Management System in C++ with a simple SFML front page.

## Included
- Abstract `Person` base class
- `Patient`, `Doctor`, `Admin`
- `Appointment`, `Bill`, `Prescription`
- `Storage<T>` template using `T data[100]`
- `FileHandler`
- `Validator`
- Custom exceptions
- Console menus for Patient / Doctor / Admin
- Simple SFML screen for bonus marks

## Default Login Data
Patient: `1 / pass123`
Doctor: `1 / doc456`
Admin: `1 / admin123`

## Build (Console)
```bash
g++ *.cpp -o MediCore
```

## Build (With SFML)
```bash
g++ *.cpp -o MediCore -lsfml-graphics -lsfml-window -lsfml-system
```

## Important
- Put your GitHub link in this README before submission.
- Rename the final zip according to your roll number.
- The program tries `arial.ttf` from project folder first, then Windows fonts path.
