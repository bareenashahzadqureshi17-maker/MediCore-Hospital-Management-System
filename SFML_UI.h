

#ifndef SFML_UI_H
#define SFML_UI_H

#include "HospitalSystem.h"
#include <SFML/Graphics.hpp>

class SFML_UI
{
private:
    HospitalSystem* system;

    enum Screen
    {
        HOME,
        ADD_MENU_SCREEN,
        PATIENT_LOGIN,
        DOCTOR_LOGIN,
        ADMIN_LOGIN,
        PATIENT_DASHBOARD,
        DOCTOR_DASHBOARD,
        ADMIN_DASHBOARD,
        ADD_PATIENT_SCREEN,
        ADD_DOCTOR_SCREEN,
        ADD_ADMIN_SCREEN,
        TOPUP_SCREEN,
        BOOK_SCREEN,
        BILLS_SCREEN
    };

    Screen screen;

    char inputID[50];
    char inputPass[50];
    char inputAmount[50];
    char inputSpec[50];
    char inputDoctorID[50];
    char inputDate[50];
    char inputSlot[50];
    char inputName[60];
    char inputAge[20];
    char inputGender[20];
    char inputContact[30];
    char inputPassword[60];
    char inputFee[30];
    char inputSpecialization[60];
    char message[200];

    int activeBox;

public:
    SFML_UI(HospitalSystem* sys);
    void run();

    void clearInputs();
    void drawAddMenu(sf::RenderWindow& window, sf::Font& font);
    void drawText(sf::RenderWindow& window, sf::Font& font, const char* text, int size, float x, float y);
    void drawButton(sf::RenderWindow& window, sf::Font& font, const char* text, float x, float y, float w, float h, bool hover = false);
    void drawInput(sf::RenderWindow& window, sf::Font& font, const char* label, const char* value, float x, float y);
    void drawHeader(sf::RenderWindow& window, sf::Font& font, const char* title);

    bool isClicked(float mx, float my, float x, float y, float w, float h);
    void addChar(char* arr, char ch, int max);
    void backspace(char* arr);

    void drawHome(sf::RenderWindow& window, sf::Font& font);
    void drawPatientLogin(sf::RenderWindow& window, sf::Font& font);
    void drawDoctorLogin(sf::RenderWindow& window, sf::Font& font);
    void drawAdminLogin(sf::RenderWindow& window, sf::Font& font);

    void drawPatientDashboard(sf::RenderWindow& window, sf::Font& font);
    void drawDoctorDashboard(sf::RenderWindow& window, sf::Font& font);
    void drawAdminDashboard(sf::RenderWindow& window, sf::Font& font);

    void drawTopUp(sf::RenderWindow& window, sf::Font& font);
    void drawBook(sf::RenderWindow& window, sf::Font& font);
    void drawBills(sf::RenderWindow& window, sf::Font& font);
    void drawAddPatient(sf::RenderWindow& window, sf::Font& font);
    void drawAddDoctor(sf::RenderWindow& window, sf::Font& font);
    void drawAddAdmin(sf::RenderWindow& window, sf::Font& font);

    void handleClick(float mx, float my);
    void handleTyping(char ch);
};

void runSFMLUI(HospitalSystem& system);

#endif