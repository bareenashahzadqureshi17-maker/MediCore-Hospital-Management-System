
#define _CRT_SECURE_NO_WARNINGS
#include "SFML_UI.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
class RoundedRectangleShape : public sf::Shape
{
private:
    sf::Vector2f size;
    float radius;
    unsigned int cornerPointCount;

public:
    RoundedRectangleShape(sf::Vector2f s, float r, unsigned int points = 12)
    {
        size = s;
        radius = r;
        cornerPointCount = points;
        update();
    }

    virtual std::size_t getPointCount() const
    {
        return cornerPointCount * 4;
    }

    virtual sf::Vector2f getPoint(std::size_t index) const
    {
        static const float pi = 3.141592654f;

        std::size_t corner = index / cornerPointCount;
        float angle = 0;

        if (corner == 0)
            angle = 180 + 90.f * (index % cornerPointCount) / (cornerPointCount - 1);
        else if (corner == 1)
            angle = 270 + 90.f * (index % cornerPointCount) / (cornerPointCount - 1);
        else if (corner == 2)
            angle = 0 + 90.f * (index % cornerPointCount) / (cornerPointCount - 1);
        else
            angle = 90 + 90.f * (index % cornerPointCount) / (cornerPointCount - 1);

        float x = 0, y = 0;

        if (corner == 0) { x = radius; y = radius; }
        else if (corner == 1) { x = size.x - radius; y = radius; }
        else if (corner == 2) { x = size.x - radius; y = size.y - radius; }
        else { x = radius; y = size.y - radius; }

        angle = angle * pi / 180.f;

        return sf::Vector2f(x + radius * cos(angle), y + radius * sin(angle));
    }
};
sf::RectangleShape makeRoundedRect(float x, float y, float w, float h, sf::Color color)
{
    sf::RectangleShape rect(sf::Vector2f(w, h));
    rect.setPosition(x, y);
    rect.setFillColor(color);
    return rect; 
}
SFML_UI::SFML_UI(HospitalSystem* sys)
{
    system = sys;
    screen = HOME;
    activeBox = 0;
    clearInputs();
    message[0] = '\0';
}

void SFML_UI::clearInputs()
{
    inputName[0] = '\0';
    inputAge[0] = '\0';
    inputGender[0] = '\0';
    inputContact[0] = '\0';
    inputPassword[0] = '\0';
    inputFee[0] = '\0';
    inputSpecialization[0] = '\0';
    inputID[0] = '\0';
    inputPass[0] = '\0';
    inputAmount[0] = '\0';
    inputSpec[0] = '\0';
    inputDoctorID[0] = '\0';
    inputDate[0] = '\0';
    inputSlot[0] = '\0';
}

void SFML_UI::drawText(sf::RenderWindow& window, sf::Font& font, const char* text, int size, float x, float y)
{
    sf::Text t(text, font, size);
    t.setFillColor(sf::Color(20, 35, 55));
    t.setPosition(x, y);
    window.draw(t);
}

void SFML_UI::drawHeader(sf::RenderWindow& window, sf::Font& font, const char* title)
{
    sf::RectangleShape header(sf::Vector2f(900, 95));
    header.setFillColor(sf::Color(35, 80, 140));
    header.setPosition(0, 0);
    window.draw(header);

    sf::CircleShape logo(28);
    logo.setFillColor(sf::Color(240, 250, 255));
    logo.setPosition(40, 20);
    window.draw(logo);

    sf::RectangleShape plus1(sf::Vector2f(32, 8));
    plus1.setFillColor(sf::Color(35, 80, 140));
    plus1.setPosition(52, 45);
    window.draw(plus1);

    sf::RectangleShape plus2(sf::Vector2f(8, 32));
    plus2.setFillColor(sf::Color(35, 80, 140));
    plus2.setPosition(64, 33);
    window.draw(plus2);

    sf::Text t(title, font, 28);
    t.setFillColor(sf::Color::White);
    t.setPosition(100, 28);
    window.draw(t);
}

void SFML_UI::drawButton(sf::RenderWindow& window, sf::Font& font, const char* text, float x, float y, float w, float h, bool hover)
{
    RoundedRectangleShape shadow(sf::Vector2f(w, h), 14);
    shadow.setPosition(x + 6, y + 6);
    shadow.setFillColor(sf::Color(150, 165, 185));
    window.draw(shadow);

    RoundedRectangleShape box(sf::Vector2f(w, h), 14);
    box.setPosition(x, y);

    if (hover)
        box.setFillColor(sf::Color(25, 115, 185));
    else
        box.setFillColor(sf::Color(45, 145, 210));

    box.setOutlineColor(sf::Color(20, 80, 140));
    box.setOutlineThickness(2);
    window.draw(box);

    sf::Text t(text, font, 21);
    t.setFillColor(sf::Color::White);
    t.setStyle(sf::Text::Bold);
    t.setPosition(x + 22, y + 13);
    window.draw(t);
}

void SFML_UI::drawInput(sf::RenderWindow& window, sf::Font& font, const char* label, const char* value, float x, float y)
{
    drawText(window, font, label, 19, x, y);

    sf::RectangleShape box(sf::Vector2f(310, 42));
    box.setPosition(x + 170, y - 6);
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color(35, 80, 140));
    box.setOutlineThickness(2);
    window.draw(box);

    drawText(window, font, value, 18, x + 182, y + 1);
}

bool SFML_UI::isClicked(float mx, float my, float x, float y, float w, float h)
{
    return mx >= x && mx <= x + w && my >= y && my <= y + h;
}

void SFML_UI::addChar(char* arr, char ch, int max)
{
    int i = 0;
    while (arr[i] != '\0') i++;

    if (i < max - 1)
    {
        arr[i] = ch;
        arr[i + 1] = '\0';
    }
}

void SFML_UI::backspace(char* arr)
{
    int i = 0;
    while (arr[i] != '\0') i++;

    if (i > 0) arr[i - 1] = '\0';
}

void SFML_UI::drawHome(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "MediCore Hospital Management System");

    sf::CircleShape c1(90);
    c1.setFillColor(sf::Color(205, 230, 255));
    c1.setPosition(-45, 535);
    window.draw(c1);

    sf::CircleShape c2(70);
    c2.setFillColor(sf::Color(220, 245, 235));
    c2.setPosition(780, 220);
    window.draw(c2);

    RoundedRectangleShape card(sf::Vector2f(620, 490), 18);
    card.setPosition(140, 170);
    card.setFillColor(sf::Color::White);
    card.setOutlineColor(sf::Color(35, 80, 140));
    card.setOutlineThickness(2);
    window.draw(card);

    sf::Text title("Welcome to MediCore", font, 36);
    title.setFillColor(sf::Color(30, 50, 80));
    title.setStyle(sf::Text::Bold);
    title.setPosition(275, 240);
    window.draw(title);

    drawText(window, font, "Choose login type or add a new record", 18, 285, 295);

    drawButton(window, font, "Patient Login", 300, 350, 300, 50);
    drawButton(window, font, "Doctor Login", 300, 410, 300, 50);
    drawButton(window, font, "Admin Login", 300, 470, 300, 50);
    drawButton(window, font, "Add Record", 300, 530, 300, 50);
    drawButton(window, font, "Exit", 300, 590, 300, 50);

    drawText(window, font, message, 18, 260, 665);
}
void SFML_UI::drawAddMenu(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Add New Record");

    RoundedRectangleShape card(sf::Vector2f(620, 390), 18);
    card.setPosition(140, 190);
    card.setFillColor(sf::Color::White);
    card.setOutlineColor(sf::Color(35, 80, 140));
    card.setOutlineThickness(2);
    window.draw(card);

    sf::Text title("What do you want to add?", font, 30);
    title.setFillColor(sf::Color(30, 50, 80));
    title.setStyle(sf::Text::Bold);
    title.setPosition(250, 220);
    window.draw(title);

    drawButton(window, font, "Add Patient", 300, 295, 300, 50);
    drawButton(window, font, "Add Doctor", 300, 360, 300, 50);
    drawButton(window, font, "Add Admin", 300, 425, 300, 50);
    drawButton(window, font, "Back", 300, 490, 300, 50);
}
void SFML_UI::drawPatientLogin(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Patient Portal");
    drawText(window, font, "Login as Patient", 30, 330, 125);

    drawInput(window, font, "Patient ID:", inputID, 190, 210);
    drawInput(window, font, "Password:", inputPass, 190, 280);

    drawButton(window, font, "Login", 300, 365, 250, 55);
    drawButton(window, font, "Back", 300, 440, 250, 55);

    drawText(window, font, message, 18, 230, 525);
}

void SFML_UI::drawDoctorLogin(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Doctor Portal");
    drawText(window, font, "Login as Doctor", 30, 330, 125);

    drawInput(window, font, "Doctor ID:", inputID, 190, 210);
    drawInput(window, font, "Password:", inputPass, 190, 280);

    drawButton(window, font, "Login", 300, 365, 250, 55);
    drawButton(window, font, "Back", 300, 440, 250, 55);

    drawText(window, font, message, 18, 230, 525);
}

void SFML_UI::drawAdminLogin(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Admin Portal");
    drawText(window, font, "Login as Admin", 30, 330, 125);

    drawInput(window, font, "Admin ID:", inputID, 190, 210);
    drawInput(window, font, "Password:", inputPass, 190, 280);

    drawButton(window, font, "Login", 300, 365, 250, 55);
    drawButton(window, font, "Back", 300, 440, 250, 55);

    drawText(window, font, message, 18, 230, 525);
}

void SFML_UI::drawPatientDashboard(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Patient Dashboard");

    Patient* p = system->getCurrentPatient();

    char balanceText[120] = "Balance: PKR ";
    if (p != 0)
    {
        char temp[40];
        sprintf(temp, "%.2f", p->getBalance());
        strcat(balanceText, temp);
    }

    drawText(window, font, balanceText, 23, 330, 120);

    drawButton(window, font, "Book Appointment", 280, 185, 340, 55);
    drawButton(window, font, "View / Pay Bills", 280, 255, 340, 55);
    drawButton(window, font, "Top Up Balance", 280, 325, 340, 55);
    drawButton(window, font, "Logout", 280, 395, 340, 55);

    drawText(window, font, message, 18, 230, 500);
}

void SFML_UI::drawDoctorDashboard(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Doctor Dashboard");

    Doctor* d = system->getCurrentDoctor();

    if (d != 0)
    {
        drawText(window, font, "Welcome Doctor", 30, 330, 125);
        drawText(window, font, d->getName(), 23, 360, 175);
        drawText(window, font, d->getSpecialization(), 20, 350, 215);
    }

    drawButton(window, font, "View Appointments in Console", 250, 295, 400, 55);
    drawButton(window, font, "Logout", 250, 370, 400, 55);

}

void SFML_UI::drawAdminDashboard(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Admin Dashboard");

    RoundedRectangleShape card(sf::Vector2f(620, 360), 18);
    card.setPosition(140, 190);
    card.setFillColor(sf::Color::White);
    card.setOutlineColor(sf::Color(35, 80, 140));
    card.setOutlineThickness(2);
    window.draw(card);

    sf::Text title("Admin Panel", font, 32);
    title.setFillColor(sf::Color(30, 50, 80));
    title.setStyle(sf::Text::Bold);
    title.setPosition(350, 220);
    window.draw(title);

    char p[80], d[80], a[80], b[80];
    sprintf(p, "Total Patients: %d", system->getPatientsCount());
    sprintf(d, "Total Doctors: %d", system->getDoctorsCount());
    sprintf(a, "Total Appointments: %d", system->getAppointmentsCount());
    sprintf(b, "Total Bills: %d", system->getBillsCount());

    drawText(window, font, p, 20, 330, 280);
    drawText(window, font, d, 20, 330, 315);
    drawText(window, font, a, 20, 330, 350);
    drawText(window, font, b, 20, 330, 385);

    drawButton(window, font, "Add Doctor", 190, 450, 220, 50);
    drawButton(window, font, "Add Admin", 490, 450, 220, 50);
    drawButton(window, font, "Logout", 300, 515, 300, 50);
}

void SFML_UI::drawTopUp(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Top Up Balance");

    drawInput(window, font, "Amount:", inputAmount, 190, 180);

    drawButton(window, font, "Add Balance", 300, 275, 250, 55);
    drawButton(window, font, "Back", 300, 350, 250, 55);

    drawText(window, font, message, 18, 230, 460);
}

void SFML_UI::drawBook(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Book Appointment");

    drawInput(window, font, "Specialization:", inputSpec, 120, 130);
    drawInput(window, font, "Doctor ID:", inputDoctorID, 120, 190);
    drawInput(window, font, "Date:", inputDate, 120, 250);
    drawInput(window, font, "Time Slot:", inputSlot, 120, 310);

    drawText(window, font, "Example: Cardiology | Date: DD-MM-YYYY | Slot: 09:00", 16, 180, 365);

    drawButton(window, font, "Book", 250, 415, 180, 50);
    drawButton(window, font, "Back", 470, 415, 180, 50);

    drawText(window, font, message, 18, 170, 500);
}

void SFML_UI::drawBills(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Bills");

    int y = 130;
    int pid = -1;

    Patient* p = system->getCurrentPatient();
    if (p != 0) pid = p->getID();

    drawText(window, font, "Bill ID | Amount | Status", 20, 260, 105);

    for (int i = 0; i < system->getBillsCount(); i++)
    {
        Bill* b = system->getBillAt(i);

        if (b != 0 && b->getPatientID() == pid)
        {
            char line[200];
            sprintf(line, "%d | %.2f | %s", b->getBillID(), b->getAmount(), b->getStatus());
            drawText(window, font, line, 18, 280, (float)y);
            y += 32;
        }
    }

    drawInput(window, font, "Bill ID to Pay:", inputAmount, 170, 395);

    drawButton(window, font, "Pay Bill", 260, 470, 180, 50);
    drawButton(window, font, "Back", 470, 470, 180, 50);

    drawText(window, font, message, 18, 230, 540);
}

void SFML_UI::handleClick(float mx, float my)
{
    if (screen == HOME)
    {
        if (isClicked(mx, my, 300, 350, 300, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = PATIENT_LOGIN;
        }
        else if (isClicked(mx, my, 300, 410, 300, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = DOCTOR_LOGIN;
        }
        else if (isClicked(mx, my, 300, 470, 300, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = ADMIN_LOGIN;
        }
        else if (isClicked(mx, my, 300, 530, 300, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = ADD_MENU_SCREEN;
        }
        else if (isClicked(mx, my, 300, 590, 300, 50))
        {
            exit(0);
        }
    }
    else if (screen == ADD_MENU_SCREEN)
    {
        if (isClicked(mx, my, 300, 270, 300, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = ADD_PATIENT_SCREEN;
        }
        else if (isClicked(mx, my, 300, 335, 300, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = ADD_DOCTOR_SCREEN;
        }
        else if (isClicked(mx, my, 300, 400, 300, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = ADD_ADMIN_SCREEN;
        }
        else if (isClicked(mx, my, 300, 465, 300, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = HOME;
        }
    }

    else if (screen == PATIENT_LOGIN)
    {
        if (isClicked(mx, my, 360, 204, 310, 42)) activeBox = 1;
        else if (isClicked(mx, my, 360, 274, 310, 42)) activeBox = 2;
        else if (isClicked(mx, my, 300, 365, 250, 55))
        {
            int id = atoi(inputID);

            if (system->patientLoginGUI(id, inputPass))
            {
                clearInputs();
                strcpy(message, "Login successful.");
                screen = PATIENT_DASHBOARD;
            }
            else strcpy(message, "Invalid ID or password.");
        }
        else if (isClicked(mx, my, 300, 440, 250, 55))
        {
            clearInputs();
            screen = HOME;
        }
    }
    else if (screen == DOCTOR_LOGIN)
    {
        if (isClicked(mx, my, 360, 204, 310, 42)) activeBox = 1;
        else if (isClicked(mx, my, 360, 274, 310, 42)) activeBox = 2;
        else if (isClicked(mx, my, 300, 365, 250, 55))
        {
            int id = atoi(inputID);

            if (system->doctorLoginGUI(id, inputPass))
            {
                clearInputs();
                strcpy(message, "Doctor login successful.");
                screen = DOCTOR_DASHBOARD;
            }
            else strcpy(message, "Invalid doctor ID or password.");
        }
        else if (isClicked(mx, my, 300, 440, 250, 55))
        {
            clearInputs();
            screen = HOME;
        }
    }
    else if (screen == ADMIN_LOGIN)
    {
        if (isClicked(mx, my, 360, 204, 310, 42)) activeBox = 1;
        else if (isClicked(mx, my, 360, 274, 310, 42)) activeBox = 2;
        else if (isClicked(mx, my, 300, 365, 250, 55))
        {
            int id = atoi(inputID);

            if (system->adminLoginGUI(id, inputPass))
            {
                clearInputs();
                strcpy(message, "Admin login successful.");
                screen = ADMIN_DASHBOARD;
            }
            else strcpy(message, "Invalid admin ID or password.");
        }
        else if (isClicked(mx, my, 300, 440, 250, 55))
        {
            clearInputs();
            screen = HOME;
        }
    }
    else if (screen == PATIENT_DASHBOARD)
    {
        if (isClicked(mx, my, 280, 185, 340, 55))
        {
            clearInputs();
            message[0] = '\0';
            screen = BOOK_SCREEN;
        }
        else if (isClicked(mx, my, 280, 255, 340, 55))
        {
            clearInputs();
            message[0] = '\0';
            screen = BILLS_SCREEN;
        }
        else if (isClicked(mx, my, 280, 325, 340, 55))
        {
            clearInputs();
            message[0] = '\0';
            screen = TOPUP_SCREEN;
        }
        else if (isClicked(mx, my, 280, 395, 340, 55))
        {
            clearInputs();
            message[0] = '\0';
            screen = HOME;
        }
    }
    else if (screen == DOCTOR_DASHBOARD)
    {
        if (isClicked(mx, my, 250, 370, 400, 55))
        {
            clearInputs();
            message[0] = '\0';
            screen = HOME;
        }
    }
    else if (screen == ADMIN_DASHBOARD)
    {
        if (isClicked(mx, my, 190, 450, 220, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = ADD_DOCTOR_SCREEN;
        }
        else if (isClicked(mx, my, 490, 450, 220, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = ADD_ADMIN_SCREEN;
        }
        else if (isClicked(mx, my, 300, 515, 300, 50))
        {
            clearInputs();
            message[0] = '\0';
            screen = HOME;
        }
        }
    else if (screen == TOPUP_SCREEN)
    {
        if (isClicked(mx, my, 360, 174, 310, 42)) activeBox = 3;
        else if (isClicked(mx, my, 300, 275, 250, 55))
        {
            float amount = (float)atof(inputAmount);
            system->topUpBalanceGUI(amount, message);
            inputAmount[0] = '\0';
        }
        else if (isClicked(mx, my, 300, 350, 250, 55))
        {
            clearInputs();
            screen = PATIENT_DASHBOARD;
        }
    }
    else if (screen == BOOK_SCREEN)
    {
        if (isClicked(mx, my, 290, 124, 310, 42)) activeBox = 4;
        else if (isClicked(mx, my, 290, 184, 310, 42)) activeBox = 5;
        else if (isClicked(mx, my, 290, 244, 310, 42)) activeBox = 6;
        else if (isClicked(mx, my, 290, 304, 310, 42)) activeBox = 7;
        else if (isClicked(mx, my, 250, 415, 180, 50))
        {
            int did = atoi(inputDoctorID);
            system->bookAppointmentGUI(inputSpec, did, inputDate, inputSlot, message);
        }
        else if (isClicked(mx, my, 470, 415, 180, 50))
        {
            clearInputs();
            screen = PATIENT_DASHBOARD;
        }
    }
    else if (screen == BILLS_SCREEN)
    {
        if (isClicked(mx, my, 340, 389, 310, 42)) activeBox = 3;
        else if (isClicked(mx, my, 260, 470, 180, 50))
        {
            int billID = atoi(inputAmount);
            system->payBillGUI(billID, message);
            inputAmount[0] = '\0';
        }
        else if (isClicked(mx, my, 470, 470, 180, 50))
        {
            clearInputs();
            screen = PATIENT_DASHBOARD;
        }
    }
    else if (screen == ADD_PATIENT_SCREEN)
    {
        if (isClicked(mx, my, 300, 114, 310, 42)) activeBox = 8;
        else if (isClicked(mx, my, 300, 169, 310, 42)) activeBox = 9;
        else if (isClicked(mx, my, 300, 224, 310, 42)) activeBox = 10;
        else if (isClicked(mx, my, 300, 279, 310, 42)) activeBox = 11;
        else if (isClicked(mx, my, 300, 334, 310, 42)) activeBox = 12;
        else if (isClicked(mx, my, 300, 389, 310, 42)) activeBox = 3;
        else if (isClicked(mx, my, 240, 465, 210, 50))
        {
            int age = atoi(inputAge);
            float bal = (float)atof(inputAmount);
            system->addPatientGUI(inputName, age, inputGender, inputContact, inputPassword, bal, message);
            clearInputs();
        }
        else if (isClicked(mx, my, 480, 465, 180, 50))
        {
            clearInputs();
            screen = HOME;
        }
}
    else if (screen == ADD_DOCTOR_SCREEN)
    {
        if (isClicked(mx, my, 300, 114, 310, 42)) activeBox = 8;
        else if (isClicked(mx, my, 300, 169, 310, 42)) activeBox = 13;
        else if (isClicked(mx, my, 300, 224, 310, 42)) activeBox = 11;
        else if (isClicked(mx, my, 300, 279, 310, 42)) activeBox = 12;
        else if (isClicked(mx, my, 300, 334, 310, 42)) activeBox = 14;
        else if (isClicked(mx, my, 240, 425, 210, 50))
        {
            float fee = (float)atof(inputFee);
            system->addDoctorGUI(inputName, inputSpecialization, inputContact, inputPassword, fee, message);
            clearInputs();
        }
        else if (isClicked(mx, my, 480, 425, 180, 50))
        {
            clearInputs();
            screen = ADMIN_DASHBOARD;
        }
        }
    else if (screen == ADD_ADMIN_SCREEN)
    {
        if (isClicked(mx, my, 330, 164, 310, 42)) activeBox = 8;
        else if (isClicked(mx, my, 330, 229, 310, 42)) activeBox = 12;
        else if (isClicked(mx, my, 260, 330, 210, 50))
        {
            system->addAdminGUI(inputName, inputPassword, message);
            clearInputs();
        }
        else if (isClicked(mx, my, 500, 330, 180, 50))
        {
            clearInputs();
            screen = ADMIN_DASHBOARD;
        }
        }
}

void SFML_UI::handleTyping(char ch)
{
    if (ch == 8)
    {
        if (activeBox == 1)
        backspace(inputID);
        else if (activeBox == 2) 
        backspace(inputPass);
        else if (activeBox == 3)
        backspace(inputAmount);
        else if (activeBox == 4) 
        backspace(inputSpec);
        else if (activeBox == 5)
        backspace(inputDoctorID);
        else if (activeBox == 6)
        backspace(inputDate);
        else if (activeBox == 7)
        backspace(inputSlot);
        else if (activeBox == 8) backspace(inputName);
        else if (activeBox == 9) backspace(inputAge);
        else if (activeBox == 10) backspace(inputGender);
        else if (activeBox == 11) backspace(inputContact);
        else if (activeBox == 12) backspace(inputPassword);
        else if (activeBox == 13) backspace(inputSpecialization);
        else if (activeBox == 14) backspace(inputFee);
    }
    else if (ch >= 32 && ch <= 126)
    {
        if (activeBox == 1) addChar(inputID, ch, 50);
        else if (activeBox == 2) addChar(inputPass, ch, 50);
        else if (activeBox == 3) addChar(inputAmount, ch, 50);
        else if (activeBox == 4) addChar(inputSpec, ch, 50);
        else if (activeBox == 5) addChar(inputDoctorID, ch, 50);
        else if (activeBox == 6) addChar(inputDate, ch, 50);
        else if (activeBox == 7) addChar(inputSlot, ch, 50);
        else if (activeBox == 8) addChar(inputName, ch, 60);
        else if (activeBox == 9) addChar(inputAge, ch, 20);
        else if (activeBox == 10) addChar(inputGender, ch, 20);
        else if (activeBox == 11) addChar(inputContact, ch, 30);
        else if (activeBox == 12) addChar(inputPassword, ch, 60);
        else if (activeBox == 13) addChar(inputSpecialization, ch, 60);
        else if (activeBox == 14) addChar(inputFee, ch, 30);
    }
}

void SFML_UI::run()
{
    sf::RenderWindow window(sf::VideoMode(900, 700), "MediCore Hospital System");
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cout << "Font not found!\n";
        return;
    }

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
                handleClick((float)event.mouseButton.x, (float)event.mouseButton.y);

            if (event.type == sf::Event::TextEntered)
                handleTyping((char)event.text.unicode);
        }

        window.clear(sf::Color(238, 246, 252));

        if (screen == HOME) drawHome(window, font);
        else if (screen == PATIENT_LOGIN) drawPatientLogin(window, font);
        else if (screen == DOCTOR_LOGIN) drawDoctorLogin(window, font);
        else if (screen == ADMIN_LOGIN) drawAdminLogin(window, font);
        else if (screen == PATIENT_DASHBOARD) drawPatientDashboard(window, font);
        else if (screen == DOCTOR_DASHBOARD) drawDoctorDashboard(window, font);
        else if (screen == ADMIN_DASHBOARD) drawAdminDashboard(window, font);
        else if (screen == TOPUP_SCREEN) drawTopUp(window, font);
        else if (screen == BOOK_SCREEN) drawBook(window, font);
        else if (screen == BILLS_SCREEN) drawBills(window, font);
        else if (screen == ADD_PATIENT_SCREEN) drawAddPatient(window, font);
        else if (screen == ADD_DOCTOR_SCREEN) drawAddDoctor(window, font);
        else if (screen == ADD_ADMIN_SCREEN) drawAddAdmin(window, font);
        else if (screen == ADD_MENU_SCREEN) drawAddMenu(window, font);

        window.display();
    }
}

void runSFMLUI(HospitalSystem& system)
{
    SFML_UI ui(&system);
    ui.run();
}
void SFML_UI::drawAddPatient(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Add New Patient");

    drawInput(window, font, "Name:", inputName, 130, 120);
    drawInput(window, font, "Age:", inputAge, 130, 175);
    drawInput(window, font, "Gender:", inputGender, 130, 230);
    drawInput(window, font, "Contact:", inputContact, 130, 285);
    drawInput(window, font, "Password:", inputPassword, 130, 340);
    drawInput(window, font, "Balance:", inputAmount, 130, 395);

    drawButton(window, font, "Save Patient", 240, 465, 210, 50);
    drawButton(window, font, "Back", 480, 465, 180, 50);

    drawText(window, font, message, 18, 190, 535);
}

void SFML_UI::drawAddDoctor(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Add New Doctor");

    drawInput(window, font, "Name:", inputName, 130, 120);
    drawInput(window, font, "Specialization:", inputSpecialization, 130, 175);
    drawInput(window, font, "Contact:", inputContact, 130, 230);
    drawInput(window, font, "Password:", inputPassword, 130, 285);
    drawInput(window, font, "Fee:", inputFee, 130, 340);

    drawButton(window, font, "Save Doctor", 240, 425, 210, 50);
    drawButton(window, font, "Back", 480, 425, 180, 50);

    drawText(window, font, message, 18, 190, 500);
}

void SFML_UI::drawAddAdmin(sf::RenderWindow& window, sf::Font& font)
{
    drawHeader(window, font, "Add New Admin");

    drawInput(window, font, "Name:", inputName, 160, 170);
    drawInput(window, font, "Password:", inputPassword, 160, 235);

    drawButton(window, font, "Save Admin", 260, 330, 210, 50);
    drawButton(window, font, "Back", 500, 330, 180, 50);

    drawText(window, font, message, 18, 220, 430);
}